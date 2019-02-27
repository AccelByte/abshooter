// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "ShooterGame.h"
#include "SLobby.h"
#include "SHeaderRow.h"
#include "ShooterStyle.h"
#include "ShooterGameLoadingScreen.h"
#include "ShooterGameInstance.h"
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"
#include "Runtime/Sockets/Public/SocketSubsystem.h"
#include "SShooterConfirmationDialog.h"
#include "ShooterGameUserSettings.h"
#include "SShooterNotificationPopup.h"
#include "Server/Models/AccelByteMatchmakingModels.h"
#include "SLobbyChat.h"

// AccelByte
#include "Api/AccelByteLobbyApi.h"
#include "Api/AccelByteUserApi.h"
#include "Core/AccelByteRegistry.h"

#define LOCTEXT_NAMESPACE "ShooterGame.HUD.Menu"
#define SIMULATE_SETUP_MATCHMAKING 1
#if SIMULATE_SETUP_MATCHMAKING
#include "Server/Models/AccelByteMatchmakingModels.h"
#endif

SLobby::SLobby()
    : OverlayBackgroundBrush(FLinearColor(0, 0, 0, 0.8f))
{

}

void SLobby::Construct(const FArguments& InArgs)
{
	const FLobbyStyle* LobbyStyle = &FShooterStyle::Get().GetWidgetStyle<FLobbyStyle>("DefaultLobbyStyle");
	OnStartMatch = InArgs._OnStartMatch;

	//grab the user settings
	UShooterGameUserSettings* UserSettings = CastChecked<UShooterGameUserSettings>(GEngine->GetGameUserSettings());
	ScreenRes = UserSettings->GetScreenResolution();

	AvatarListCache = MakeShared<ProfileCache, ESPMode::ThreadSafe>();
	DiplayNameListCache = MakeShared<ProfileCache, ESPMode::ThreadSafe>();

	PlayerOwner = InArgs._PlayerOwner;
	OwnerWidget = InArgs._OwnerWidget;
	bSearchingForFriends = false;
	LastSearchTime = 0.0f;

#pragma region LoadDedicatedServerUrl
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FString ConfigFile = FPaths::ProjectSavedDir() / "Config/Server.txt";
	if (PlatformFile.FileExists(*ConfigFile))
	{
		TArray<FString> Lines;
		if (FFileHelper::LoadFileToStringArray(Lines, *ConfigFile) && Lines.Num() > 0)
		{
			DedicatedServerBaseUrl = Lines[0];
		}
	}

	if (DedicatedServerBaseUrl.IsEmpty())
	{
		DedicatedServerBaseUrl = "http://127.0.0.1:8080";
	}

	int32 StartIndex = DedicatedServerBaseUrl.Find("://");
	if (StartIndex > 0)
	{
		StartIndex += 3;
	}
	else
	{
		StartIndex = 0;
	}
	int32 EndIndex = DedicatedServerBaseUrl.Find(":", ESearchCase::CaseSensitive, ESearchDir::FromStart, StartIndex + 3);
	if (EndIndex > 0)
	{
		DedicatedServerAddress = DedicatedServerBaseUrl.Mid(StartIndex, EndIndex - StartIndex);
	}
	else
	{
		DedicatedServerAddress = DedicatedServerBaseUrl.RightChop(StartIndex);
	}

	const FRegexPattern IPAddressPattern(TEXT("^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$"));
	if (!FRegexMatcher(IPAddressPattern, DedicatedServerAddress).FindNext())
	{
		ISocketSubsystem* const SocketSubSystem = ISocketSubsystem::Get();
		if (SocketSubSystem)
		{
			FResolveInfo* ResolveInfo = SocketSubSystem->GetHostByName(TCHAR_TO_ANSI(*DedicatedServerAddress));

			while (!ResolveInfo->IsComplete()) FPlatformProcess::Sleep(0.1f);

			if (ResolveInfo->GetErrorCode() == 0)
			{
				const FInternetAddr& Address = ResolveInfo->GetResolvedAddress();
				uint32 IP = 0;
				Address.GetIp(IP);
				DedicatedServerAddress = FString::Printf(TEXT("%d.%d.%d.%d"), 0xff & (IP >> 24), 0xff & (IP >> 16), 0xff & (IP >> 8), 0xff & IP);
			}
		}
	}

#pragma endregion LoadDedicatedServerUrl

#if PLATFORM_SWITCH
	MinTimeBetweenSearches = 6.0;
#else
	MinTimeBetweenSearches = 0.0;
#endif

    AccelByte::FRegistry::Lobby.SetUserPresenceNotifDelegate(AccelByte::Api::Lobby::FFriendStatusNotif::CreateSP(this, &SLobby::OnUserPresenceNotification));
    AccelByte::FRegistry::Lobby.SetInfoPartyResponseDelegate(AccelByte::Api::Lobby::FPartyInfoResponse::CreateSP(this, &SLobby::OnGetPartyInfoResponse));
    AccelByte::FRegistry::Lobby.SetCreatePartyResponseDelegate(AccelByte::Api::Lobby::FPartyCreateResponse::CreateSP(this, &SLobby::OnCreatePartyResponse));
    AccelByte::FRegistry::Lobby.SetPartyGetInvitedNotifDelegate(AccelByte::Api::Lobby::FPartyGetInvitedNotif::CreateSP(this, &SLobby::OnInvitedToParty));
    AccelByte::FRegistry::Lobby.SetPartyJoinNotifDelegate(AccelByte::Api::Lobby::FPartyJoinNotif::CreateSP(this, &SLobby::OnInvitedFriendJoinParty));
	AccelByte::FRegistry::Lobby.SetPartyKickNotifDelegate(AccelByte::Api::Lobby::FPartyKickNotif::CreateSP(this, &SLobby::OnKickedFromParty));
	AccelByte::FRegistry::Lobby.SetPartyLeaveNotifDelegate(AccelByte::Api::Lobby::FPartyLeaveNotif::CreateSP(this, &SLobby::OnLeavingParty));
	AccelByte::FRegistry::Lobby.SetLeavePartyResponseDelegate(AccelByte::Api::Lobby::FPartyLeaveResponse::CreateLambda([this](const FAccelByteModelsLeavePartyResponse& Response)
	{
		PartyWidget->ResetAll();
		LobbyChatWidget->RemovePartyChatTab(CurrentPartyID);
        CurrentPartyID = TEXT("");
	}));
	AccelByte::FRegistry::Lobby.SetMessageNotifDelegate(AccelByte::Api::Lobby::FMessageNotif::CreateSP(this, &SLobby::OnIncomingNotification));
	AccelByte::FRegistry::Lobby.SetRequestFriendsResponseDelegate(AccelByte::Api::Lobby::FRequestFriendsResponse::CreateSP(this, &SLobby::OnRequestFriendSent));
	AccelByte::FRegistry::Lobby.SetListIncomingFriendsResponseDelegate(AccelByte::Api::Lobby::FListIncomingFriendsResponse::CreateSP(this, &SLobby::OnIncomingListFriendRequest));
	AccelByte::FRegistry::Lobby.SetLoadFriendListResponseDelegate(AccelByte::Api::Lobby::FLoadFriendListResponse::CreateSP(this, &SLobby::OnFriendListLoaded));
	AccelByte::FRegistry::Lobby.SetCreatePartyResponseDelegate(AccelByte::Api::Lobby::FPartyCreateResponse::CreateLambda([&](const FAccelByteModelsCreatePartyResponse& Response)
	{
		AccelByte::FRegistry::Lobby.SendInfoPartyRequest();
	}));
	AccelByte::FRegistry::Lobby.SetOnFriendRequestAcceptedNotifDelegate(AccelByte::Api::Lobby::FAcceptFriendsNotif::CreateSP(this, &SLobby::OnFriendRequestAcceptedNotification));
	AccelByte::FRegistry::Lobby.SetOnIncomingRequestFriendsNotifDelegate(AccelByte::Api::Lobby::FRequestFriendsNotif::CreateSP(this, &SLobby::OnIncomingFriendRequestNotification));
	AccelByte::FRegistry::Lobby.SetGetAllUserPresenceResponseDelegate(AccelByte::Api::Lobby::FGetAllFriendsStatusResponse::CreateSP(this, &SLobby::OnGetOnlineUserResponse));
	AccelByte::FRegistry::Lobby.SetStartMatchmakingResponseDelegate(AccelByte::Api::Lobby::FMatchmakingResponse::CreateLambda([&](const FAccelByteModelsMatchmakingResponse& Response)
	{
		if (Response.Code != "0")
		{
			bMatchmakingStarted = false;
		}
	}));
	AccelByte::FRegistry::Lobby.SetMatchmakingNotifDelegate(AccelByte::Api::Lobby::FMatchmakingNotif::CreateLambda([&](const FAccelByteModelsMatchmakingNotice& Response)
	{
		if (Response.Status == EAccelByteMatchmakingStatus::Done)
		{
#if SIMULATE_SETUP_MATCHMAKING
			// for test only, may not work on the future
			FString MatchId = Response.MatchId;
			FString Url = FString::Printf(TEXT("%s/match"), *DedicatedServerBaseUrl);
			FString Verb = TEXT("POST");
			FString ContentType = TEXT("application/json");
			FString Accept = TEXT("application/json");

			FString Content;

			GameMode = FString::Printf(TEXT("%dvs%d"), PartyWidget->GetCurrentPartySize(), PartyWidget->GetCurrentPartySize());
			FAccelByteModelsMatchmakingInfo MatchmakingInfo;
			MatchmakingInfo.channel = GameMode;
			MatchmakingInfo.match_id = Response.MatchId;

			FAccelByteModelsMatchmakingParty Party;
			for (auto Member : Response.PartyMember)
			{
				FAccelByteModelsMatchmakingPartyMember PartyMember;
				PartyMember.user_id = Member;
				Party.party_members.Add(PartyMember);
			}

			Party.party_id = CurrentPartyID;
			MatchmakingInfo.matching_parties.Add(Party);

			FAccelByteModelsMatchmakingParty CounterParty;
			for (auto Member : Response.CounterPartyMember)
			{
				FAccelByteModelsMatchmakingPartyMember PartyMember;
				PartyMember.user_id = Member;
				CounterParty.party_members.Add(PartyMember);
			}
			MatchmakingInfo.matching_parties.Add(CounterParty);

			FJsonObjectConverter::UStructToJsonObjectString(MatchmakingInfo, Content, 0, 0);
			FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
			Request->SetURL(Url);
			Request->SetVerb(Verb);
			Request->SetHeader(TEXT("Content-Type"), ContentType);
			Request->SetHeader(TEXT("Accept"), Accept);
			Request->SetContentAsString(Content);
			Request->OnProcessRequestComplete().BindLambda([&, MatchId](FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful) {
				if (Successful && Request.IsValid())
				{
					UE_LOG(LogOnlineGame, Log, TEXT("SetupMatchmaking : [%d] %s"), Response->GetResponseCode(), *Response->GetContentAsString());
					StartMatch(MatchId, CurrentPartyID);
				}
				else
				{
					FString ErrorMessage = FString::Printf(TEXT("Can't setup matchmaking to %s"), *DedicatedServerBaseUrl);
					UE_LOG(LogOnlineGame, Log, TEXT("%s"), *ErrorMessage);
					if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, *ErrorMessage);
				}
				bMatchmakingStarted = false;
			});
			UE_LOG(LogOnlineGame, Log, TEXT("SetupMatchmaking..."));
			Request->ProcessRequest();
#else
			StartMatch(Response.MatchId, CurrentPartyID);
#endif
		}
		// show loading for non leader party member
		else if(Response.Status == EAccelByteMatchmakingStatus::Start)
		{
			bMatchmakingStarted = true;
		}
		else 
		{
			if (Response.Status == EAccelByteMatchmakingStatus::Cancel)
			{
				GEngine->AddOnScreenDebugMessage(0, 3, FColor::Cyan, TEXT("Matchmaking canceled by party leader"), true, FVector2D(2.0f, 2.0f));
			}
			else if (Response.Status == EAccelByteMatchmakingStatus::Timeout)
			{
				GEngine->AddOnScreenDebugMessage(0, 3, FColor::Cyan, TEXT("Matchmaking failed: Timeout"), true, FVector2D(2.0f, 2.0f));
			}
			else if (Response.Status == EAccelByteMatchmakingStatus::Unavailable)
			{
				GEngine->AddOnScreenDebugMessage(0, 3, FColor::Cyan, TEXT("Matchmaking failed: Dedicated server unavailable"), true, FVector2D(2.0f, 2.0f));
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(0, 3, FColor::Cyan, FString::Printf(TEXT("Matchmaking failed: %d"), (int32)Response.Status), true, FVector2D(2.0f, 2.0f));
			}

			bMatchmakingStarted = false;
		}
	}));
	AccelByte::FRegistry::Lobby.SetCancelMatchmakingResponseDelegate(AccelByte::Api::Lobby::FMatchmakingResponse::CreateLambda([&](const FAccelByteModelsMatchmakingResponse& Response)
	{
		bMatchmakingStarted = false;
	}));


	ChildSlot
	.VAlign(VAlign_Fill)
	.HAlign(HAlign_Fill)
	[
		SNew(SBox)
		.HeightOverride(TAttribute<FOptionalSize>::Create([&]() { return FOptionalSize(GetLobbyHeight(1.1)); }))
		.WidthOverride(TAttribute<FOptionalSize>::Create([&]() { return FOptionalSize(GetLobbyWidth(1.0)); }))
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		.Padding(FMargin(0, 40, 0, 0))
		[
			SNew(SHorizontalBox)

#pragma region FriendWidget_ChatWidget
			+SHorizontalBox::Slot()
			.MaxWidth(TAttribute<float>::Create([&]() { return GetLobbyWidth(2); }))
			.FillWidth(1.0f)
			.HAlign(HAlign_Fill)
			[

				SNew(SVerticalBox)
#pragma region SearchFriend
				+ SVerticalBox::Slot()	//FriendSearchBar
				.HAlign(HAlign_Fill)
				.MaxHeight(50.0f)
				.AutoHeight()
				[
					SNew(SOverlay)
						
					+SOverlay::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					[
						SNew(SImage)
						.Image(&LobbyStyle->SearchBarBackground)
					]
						
					+SOverlay::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					[
						SNew(SHorizontalBox)

						+ SHorizontalBox::Slot()	//2.1 INPUT FIELD
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.FillWidth(1.0f)
						.Padding(15, 20, 0, 5)
						[
							SNew(SBox)	//2.1.1 SEDITABLETEXTBOX
							[
								SAssignNew(FriendSearchBar, SEditableTextBox)
								.HintText(FText::FromString(TEXT("Type username here")))
								.MinDesiredWidth(300.0f)
								.SelectAllTextWhenFocused(true)
								.Style(&LobbyStyle->SearchBarStyle)
							]
						]

						+ SHorizontalBox::Slot()	//2.1.1 SBUTTON SEARCH FRIEND
						.AutoWidth()
						.Padding(6, 5, 5, 5)
						.MaxWidth(64.0f)
						[
							SNew(SButton)
							.OnClicked(this, &SLobby::OnRequestFriend)
							.ButtonStyle(&LobbyStyle->AddFriendButtonStyle)
							.VAlign(VAlign_Fill)
						]
					]
				]
#pragma endregion SearchFriend

#pragma region FriendList
				+ SVerticalBox::Slot()	//FriendListView
				.FillHeight(1.0f)
				.MaxHeight(TAttribute<float>::Create([&]() { return GetLobbyHeight(2.5); }))
				.HAlign(HAlign_Fill)
				[
					SNew(SOverlay)

					+SOverlay::Slot()
					[
						SNew(SImage)
						.Image(&LobbyStyle->FriendListBackground)
					]

					+SOverlay::Slot()
					[
					SNew(SHorizontalBox)

						+ SHorizontalBox::Slot()	//NonScrollBar
						.HAlign(HAlign_Fill)
						[
							SNew(SBox)
							.HAlign(HAlign_Fill)
							.HeightOverride(TAttribute<FOptionalSize>::Create([&](){ return FOptionalSize(GetLobbyHeight(2.0));}))
							.WidthOverride(TAttribute<FOptionalSize>::Create([&]() { return FOptionalSize(GetLobbyWidth(3.0)); }))
							[
								SAssignNew(LobbyWidget, SListView<TSharedPtr<FFriendEntry>>)
								.ListItemsSource(&FriendList)
								.SelectionMode(ESelectionMode::Single)
								.OnGenerateRow(this, &SLobby::MakeListViewWidget)
								.OnSelectionChanged(this, &SLobby::EntrySelectionChanged)
								.ExternalScrollbar(FriendScrollBar)
								.ScrollbarVisibility(EVisibility::Visible)
								.HeaderRow(
									SNew(SHeaderRow)
									.Style(&LobbyStyle->HeaderRowStyle)
									+ SHeaderRow::Column("Friend")
									.HAlignCell(HAlign_Fill)
									.VAlignCell(VAlign_Fill)
									.FillWidth(1.0)
									.DefaultLabel(this, &SLobby::GetFriendHeaderText)
									.HAlignHeader(HAlign_Left)
									.VAlignHeader(VAlign_Center)
									.HeaderContentPadding(FMargin(2))
								)
							]
						]

						+ SHorizontalBox::Slot()	//Scroll player list
						.AutoWidth()
						.Padding(TAttribute<FMargin>::Create([&](){
							return FMargin(0.f, LobbyWidget->GetHeaderRow()->GetDesiredSize().Y , 0.f, 0.f);
						}))
						[
							SNew(SBox)
							.HAlign(HAlign_Right)
							[
								SAssignNew(FriendScrollBar, SScrollBar)
								.IsEnabled(true)
								.AlwaysShowScrollbar(true)
								.Thickness(FVector2D(12.0f, 12.0f))
								.Orientation(EOrientation::Orient_Vertical)
								.Visibility(EVisibility::Visible)
								.Style(&LobbyStyle->ScrollBarStyle)
							]
						]

					]
				]
#pragma endregion FriendList
					
				+SVerticalBox::Slot()	//MARGIN FRIEND >=< CHAT
				.FillHeight(0.1f)
				[
					SNew(SBox)
				]

#pragma region ChatWidget
				+ SVerticalBox::Slot()		//CHAT Widget
				.VAlign(VAlign_Fill)
				.MaxHeight(TAttribute<float>::Create([&]() { return GetLobbyHeight(3.0);}))
				.FillHeight(.8f)
				.HAlign(HAlign_Fill)
				[
					SNew(SOverlay)

					+ SOverlay::Slot()
					[
						SNew(SImage)
						.Image(&LobbyStyle->ChatAreaBackground)
					]

					+SOverlay::Slot()
					[
						SAssignNew(LobbyChatWidget, SLobbyChat)
						.LobbyParent(SharedThis(this))
					]
				]
#pragma endregion ChatWidget

			]
#pragma endregion FriendWidget_ChatWidget

			+ SHorizontalBox::Slot()	//MARGIN FRIEND <||> PARTY
			.AutoWidth()
			[
				SNew(SBox)
				.WidthOverride(TAttribute<FOptionalSize>::Create([&]() { return FOptionalSize(GetLobbyWidth(12.0)); }))
			]

#pragma region PartyWidget_StartMatchWidget
			+ SHorizontalBox::Slot()	
			.MaxWidth(TAttribute<float>::Create([&]() { return GetLobbyWidth(2.5); }))
			.AutoWidth()
			[
				SNew(SVerticalBox)

#pragma region PartyWidget
				+ SVerticalBox::Slot()	//PARTY_WIDGET
				.FillHeight(1.0f)
				[
					SAssignNew(PartyWidget, SParty)
					.LobbyStyle(LobbyStyle)
				]
#pragma endregion PartyWidget

				//+SVerticalBox::Slot()	//MARGIN PARTY >=< STARTMATCH
				//.AutoHeight()
				//[
				//	SNew(SBox)
				//	.HeightOverride(TAttribute<FOptionalSize>::Create([&]() { return FOptionalSize(GetLobbyHeight(5.0)); }))
				//]

#pragma region StartMatch
				+ SVerticalBox::Slot()	//STARTMATCH_BUTTON
				.AutoHeight()
				.VAlign(VAlign_Bottom)
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
					[
						SNew(SButton)
						.VAlign(VAlign_Bottom)
						.HAlign(HAlign_Center)
						.ButtonStyle(&LobbyStyle->StartMatchButton)
						.Visibility(TAttribute<EVisibility>::Create([&]
						{
							if (bIsPartyLeader && !bMatchmakingStarted)
							{
								return EVisibility::Visible;
							}

							return EVisibility::Collapsed;
						}))
						.OnClicked(FOnClicked::CreateLambda([&] 
						{
							bMatchmakingStarted = true;
							GameMode = FString::Printf(TEXT("%dvs%d"), PartyWidget->GetCurrentPartySize(), PartyWidget->GetCurrentPartySize());
							AccelByte::FRegistry::Lobby.SendStartMatchmaking(GameMode);
							return FReply::Handled();
						}))
					]
					+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					[
						SNew(SHorizontalBox)
						.Visibility(TAttribute<EVisibility>::Create([&]
						{
							if (bMatchmakingStarted)
							{
								return EVisibility::Visible;
							}

							return EVisibility::Collapsed;
						}))
						+ SHorizontalBox::Slot()
						.AutoWidth()
						[
							SNew(STextBlock)
							.Text(FText::FromString("Finding Match"))
						]
						+ SHorizontalBox::Slot()
						.AutoWidth()
						[
							SNew(SThrobber)
						]
						+ SHorizontalBox::Slot()
						.AutoWidth()
						[
							SNew(SButton)
							.VAlign(VAlign_Center)
							.HAlign(HAlign_Center)
							.Visibility(TAttribute<EVisibility>::Create([&]
							{
								if (bIsPartyLeader && bMatchmakingStarted)
								{
									return EVisibility::Visible;
								}

								return EVisibility::Collapsed;
							}))
							[
								SNew(STextBlock)
								.Text(FText::FromString("Cancel"))
							]
							.OnClicked(FOnClicked::CreateLambda([&] 
							{
								AccelByte::FRegistry::Lobby.SendCancelMatchmaking(GameMode);
								return FReply::Handled();
							}))
						]
					]
				]
#pragma endregion StartMatch

			]
#pragma endregion PartyWidget_StartMatchWidget

		]
	];
}

float SLobby::GetLobbyHeight(float Divider) const
{
	FVector2D ViewPortSize = FVector2D(1, 1);
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewPortSize);
	}

    return (ViewPortSize.Y/Divider);
}

float SLobby::GetLobbyWidth(float Divider) const
{
	FVector2D ViewPortSize = FVector2D(1, 1);
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewPortSize);
	}

	return float(ViewPortSize.X/Divider);
}

void SLobby::StartMatch(const FString& MatchId, const FString& PartyId)
{
	OnStartMatch.ExecuteIfBound();
	UE_LOG(LogOnlineGame, Log, TEXT("OpenLevel: %s"), *DedicatedServerAddress);
	UGameplayStatics::OpenLevel(GEngine->GameViewport->GetWorld(), FName(*DedicatedServerAddress), true, FString::Printf(TEXT("PartyId=%s?MatchId=%s?UserId=%s"), *PartyId, *MatchId, *GetCurrentUserID()));
}

void SLobby::OnCreatePartyResponse(const FAccelByteModelsCreatePartyResponse& PartyInfo)
{
	AccelByte::FRegistry::Lobby.SendInfoPartyRequest();
}

void SLobby::OnGetPartyInfoResponse(const FAccelByteModelsInfoPartyResponse& PartyInfo)
{
    PartyWidget->ResetAll();
	bIsPartyLeader = (PartyInfo.LeaderId == GetCurrentUserID());

    FString LeaderDisplayName = CheckDisplayName(PartyInfo.LeaderId) ? GetDisplayName(PartyInfo.LeaderId) : PartyInfo.LeaderId;
    FSlateBrush* LeaderAvatar = CheckAvatar(PartyInfo.LeaderId) ? GetAvatar(PartyInfo.LeaderId).Get() : (FSlateBrush*)FShooterStyle::Get().GetBrush("ShooterGame.Speaker");

    PartyWidget->InsertLeader(PartyInfo.LeaderId, LeaderDisplayName, LeaderAvatar);
    for (FString MemberId : PartyInfo.Members)
    {
        if (MemberId != PartyInfo.LeaderId)
        {
            FString MemberDisplayName = CheckDisplayName(MemberId) ? GetDisplayName(MemberId) : MemberId;
            FSlateBrush* MemberAvatar = CheckAvatar(MemberId) ? GetAvatar(MemberId).Get() : (FSlateBrush*)FShooterStyle::Get().GetBrush("ShooterGame.Speaker");
            PartyWidget->InsertMember(MemberId, MemberDisplayName, MemberAvatar, (MemberId == GetCurrentUserID()));
        }
    }
    PartyWidget->ButtonCreateParty->SetVisibility(EVisibility::Collapsed);
    // add chat tab
    CurrentPartyID = PartyInfo.PartyId;
	LobbyChatWidget->AddParty(PartyInfo.PartyId);
}

void SLobby::OnInvitedFriendJoinParty(const FAccelByteModelsPartyJoinNotice& Notification)
{   
    // show popup
    FString DisplayName = CheckDisplayName(Notification.UserId) ? GetDisplayName(Notification.UserId) : Notification.UserId;
    FSlateBrush* MemberAvatar = CheckAvatar(Notification.UserId) ? GetAvatar(Notification.UserId).Get() : (FSlateBrush*)FShooterStyle::Get().GetBrush("ShooterGame.Speaker");
    FString NotificationMessage = FString::Printf(TEXT("%s has join the party"), *DisplayName);
    TSharedPtr<SShooterNotificationPopup> Popup = SNew(SShooterNotificationPopup)
        .NotificationMessage(NotificationMessage)
        .AvatarImage(MemberAvatar)
        .OnPopupClosed_Lambda([]() //Hold Brush until popup closed
    {
    });
    Popup->Show();

    // update using OnGetPartyInfoResponse, so we have to trigger SendInfoPartyRequest
    // TODO optimize this
    AccelByte::FRegistry::Lobby.SendInfoPartyRequest();
}

void SLobby::OnInvitedToParty(const FAccelByteModelsPartyGetInvitedNotice& Notification)
{
    FString DisplayName = CheckDisplayName(Notification.From) ? GetDisplayName(Notification.From) : Notification.From;
    SAssignNew(InvitationOverlay, SOverlay)
        + SOverlay::Slot()
        [
            SNew(SBox)
            .HAlign(HAlign_Fill)
            .VAlign(VAlign_Fill)
            [
            	SNew(SImage)
            	.Image(&OverlayBackgroundBrush)
            ]
        ]
        + SOverlay::Slot()
        [
            SNew(SShooterConfirmationDialog).PlayerOwner(PlayerOwner)
            .MessageText(FText::FromString(FString::Printf(TEXT("You're invited by %s to join a party."), *DisplayName)))
            .ConfirmText(FText::FromString("Accept"))
            .CancelText(FText::FromString("Reject"))
            .OnConfirmClicked(FOnClicked::CreateLambda([&, Notification]()
            {
				//Leave old party & reset CurrentPartyId
                if (!CurrentPartyID.IsEmpty())
                {
					LobbyChatWidget->RemovePartyChatTab(CurrentPartyID);
                    CurrentPartyID = TEXT("");
                    AccelByte::FRegistry::Lobby.SendLeavePartyRequest();
                }

				//Join new party (set CurrentPartyId, accept invitation, set widgets after there's join response)
                CurrentPartyID = Notification.PartyId;
                AccelByte::FRegistry::Lobby.SendAcceptInvitationRequest(Notification.PartyId, Notification.InvitationToken);
                AccelByte::FRegistry::Lobby.SetInvitePartyJoinResponseDelegate(AccelByte::Api::Lobby::FPartyJoinResponse::CreateLambda([&](const FAccelByteModelsPartyJoinReponse& Response)
                {
                    PartyWidget->ResetAll();
                
                    FString LeaderDisplayName = CheckDisplayName(Response.LeaderId) ? GetDisplayName(Response.LeaderId) : Response.LeaderId;
                    FSlateBrush* LeaderAvatar = CheckAvatar(Response.LeaderId) ? GetAvatar(Response.LeaderId).Get() : (FSlateBrush*)FShooterStyle::Get().GetBrush("ShooterGame.Speaker");

                    PartyWidget->InsertLeader(Response.LeaderId, LeaderDisplayName, LeaderAvatar);
                    for (FString MemberId : Response.Members)
                    {
                        if (MemberId != Response.LeaderId)
                        {
                            FString MemberDisplayName = CheckDisplayName(MemberId) ? GetDisplayName(MemberId) : MemberId;
                            FSlateBrush* MemberAvatar = CheckAvatar(MemberId) ? GetAvatar(MemberId).Get() : (FSlateBrush*)FShooterStyle::Get().GetBrush("ShooterGame.Speaker");

                            PartyWidget->InsertMember(MemberId, MemberDisplayName, MemberAvatar, (MemberId == GetCurrentUserID()));
                        }
                    }
                    PartyWidget->ButtonCreateParty->SetVisibility(EVisibility::Collapsed);
                }));
                if (InvitationOverlay.IsValid())
                {
                    GEngine->GameViewport->RemoveViewportWidgetContent(InvitationOverlay.ToSharedRef());
                    InvitationOverlay.Reset();
                }
                // add chat tab
				LobbyChatWidget->AddParty(Notification.PartyId);
                return FReply::Handled();
            }))
            .OnCancelClicked(FOnClicked::CreateLambda([&]()
            {
                if (InvitationOverlay.IsValid())
                {
                    GEngine->GameViewport->RemoveViewportWidgetContent(InvitationOverlay.ToSharedRef());
                    InvitationOverlay.Reset();
                }
                return FReply::Handled();
            }))
        ];

    GEngine->GameViewport->AddViewportWidgetContent(InvitationOverlay.ToSharedRef());
    FSlateApplication::Get().SetKeyboardFocus(InvitationOverlay);
}

void SLobby::OnKickedFromParty(const FAccelByteModelsGotKickedFromPartyNotice& KickInfo)
{
	if (KickInfo.UserId == CurrentUserID)
	{
		PartyWidget->ResetAll();
		LobbyChatWidget->RemovePartyChatTab(CurrentPartyID);
        CurrentPartyID = TEXT("");

        FSlateBrush* MemberAvatar = CheckAvatar(CurrentUserID) ? GetAvatar(CurrentUserID).Get() : (FSlateBrush*)FShooterStyle::Get().GetBrush("ShooterGame.Speaker");
        // show popup
        FString NotificationMessage = FString::Printf(TEXT("You has been kicked from party"));
        TSharedPtr<SShooterNotificationPopup> Popup = SNew(SShooterNotificationPopup)
            .NotificationMessage(NotificationMessage)
            .AvatarImage(MemberAvatar)
            .OnPopupClosed_Lambda([]() //Hold Brush until popup closed
        {
        });
        Popup->Show();


	}
	else
	{
		for (auto Member : PartyWidget->PartyMembers)
		{
			if (Member->UserId == KickInfo.UserId)
			{
				Member->Release();
			}
		};

        // show popup
        FString DisplayName = CheckDisplayName(KickInfo.UserId) ? GetDisplayName(KickInfo.UserId) : KickInfo.UserId;
        FSlateBrush* MemberAvatar = CheckAvatar(KickInfo.UserId) ? GetAvatar(KickInfo.UserId).Get() : (FSlateBrush*)FShooterStyle::Get().GetBrush("ShooterGame.Speaker");

        FString NotificationMessage = FString::Printf(TEXT("%s has been kicked from party"), *DisplayName);
        TSharedPtr<SShooterNotificationPopup> Popup = SNew(SShooterNotificationPopup)
            .NotificationMessage(NotificationMessage)
            .AvatarImage(MemberAvatar)
            .OnPopupClosed_Lambda([]() 
        {
        });
        Popup->Show();
	}
}

void SLobby::OnLeavingParty(const FAccelByteModelsLeavePartyNotice& LeaveInfo)
{
	for (auto Member : SLobby::PartyWidget->PartyMembers)
	{
		if (Member->UserId == LeaveInfo.UserID)
		{
			Member->Release();
		}
	};

    if (LeaveInfo.UserID == CurrentUserID)
    {
		LobbyChatWidget->RemovePartyChatTab(CurrentPartyID);
        CurrentPartyID = TEXT("");
    }


    // show popup
    FString DisplayName = CheckDisplayName(LeaveInfo.UserID) ? GetDisplayName(LeaveInfo.UserID) : LeaveInfo.UserID;
    FSlateBrush* MemberAvatar = CheckAvatar(LeaveInfo.UserID) ? GetAvatar(LeaveInfo.UserID).Get() : (FSlateBrush*)FShooterStyle::Get().GetBrush("ShooterGame.Speaker");
    FString NotificationMessage = FString::Printf(TEXT("%s has left party"), *DisplayName);
    TSharedPtr<SShooterNotificationPopup> Popup = SNew(SShooterNotificationPopup)
        .NotificationMessage(NotificationMessage)
        .AvatarImage(MemberAvatar)
        .OnPopupClosed_Lambda([]() //Hold Brush until popup closed
    {
    });
    Popup->Show();

}

void SLobby::OnUserPresenceNotification(const FAccelByteModelsUsersPresenceNotice& Response)
{
	//IF Response.UserID is in the Friendlist, THEN PROCEED
	bool UserPresenceIsFriend = false;
	for (int i = 0; i < CompleteFriendList.Num() ; i++)
	{
		if (Response.UserID == CompleteFriendList[i]->UserId)
		{
			UserPresenceIsFriend = true;
		}
	}
	if (!UserPresenceIsFriend) 
	{
		return;
	}

    UE_LOG(LogTemp, Log, TEXT("OnUserPresenceNotification: %s Activity: %s"), *Response.UserID, *Response.Activity);

    // add to friend list, download the avatar
    if (Response.Activity == "Shooter Game" && Response.Availability == "1")
    {
        // user online
        // check if exist
        bool found = false;
        for (int i = 0; i < CompleteFriendList.Num(); i++)
        {
            if (CompleteFriendList[i]->UserId == Response.UserID)
            {
                found = true;
                break;
            }
        }
        
        if (!found)
        {
            AddFriend(Response.UserID, Response.UserID, TEXT("https://s3-us-west-2.amazonaws.com/justice-platform-service/avatar.jpg"));
            RefreshFriendList();
            UpdateSearchStatus();
        }
        else
        {
            // update his status
            for (int i = 0; i < CompleteFriendList.Num(); i++)
            {
                if (CompleteFriendList[i]->UserId == Response.UserID)
                {
                    CompleteFriendList[i]->Presence = "ONLINE";
                    break;
                }
            }
            RefreshFriendList();
            UpdateSearchStatus();
        }

        FString DisplayName = CheckDisplayName(Response.UserID) ? GetDisplayName(Response.UserID) : Response.UserID;
        FSlateBrush* MemberAvatar = CheckAvatar(Response.UserID) ? GetAvatar(Response.UserID).Get() : (FSlateBrush*)FShooterStyle::Get().GetBrush("ShooterGame.Speaker");

		// show popup
		FString NotificationMessage = FString::Printf(TEXT("%s has been online"), *DisplayName);
		TSharedPtr<SShooterNotificationPopup> Popup = SNew(SShooterNotificationPopup)
			.NotificationMessage(NotificationMessage)
            .AvatarImage(MemberAvatar)
			.OnPopupClosed_Lambda([]() //Hold Brush until popup closed
		{
		});
		Popup->Show();		


    }
    else if (Response.Availability == "0")
    {
        UE_LOG(LogTemp, Log, TEXT("There is user going offline : %s"), *Response.UserID);
        // user is offline, update his status
        // update UI
        for (int i = 0; i < CompleteFriendList.Num(); i++)
        {
            if (CompleteFriendList[i]->UserId == Response.UserID)
            {
                UE_LOG(LogTemp, Log, TEXT("Set the user to offline : %s"), *Response.UserID);
                CompleteFriendList[i]->Presence = "OFFLINE";
				LobbyChatWidget->Remove(Response.UserID);
                break;
            }
        }
        RefreshFriendList();
        UpdateSearchStatus();
    }
}

/** Updates current search status */
void SLobby::UpdateSearchStatus()
{
	bSearchingForFriends = false;
	UpdateFriendList();
}

void SLobby::InitializeFriends()
{
    bSearchingForFriends = true;
    CompleteFriendList.Reset();
}

void SLobby::SetCurrentUser(FString UserID, FString DisplayName, FString AvatarURL)
{
    CurrentUserID = UserID;
    CurrentUserDisplayName = DisplayName; 
    CurrentAvatarURL = AvatarURL;

    // save to our cache
    FString CacheTextDir = FString::Printf(TEXT("%s\\Cache\\%s.txt"), *FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()), *UserID);

    IFileManager& FileManager = IFileManager::Get();

    // save to our cache
    if (FileManager.FileExists(*CacheTextDir)) // meta found
    {
        UE_LOG(LogTemp, Log, TEXT("cache meta found"));
        FString FileToLoad;
        if (FFileHelper::LoadFileToString(FileToLoad, *CacheTextDir))
        {
            TArray<FString> Raw;
            FileToLoad.ParseIntoArray(Raw, TEXT("\n"), true);
            if (Raw.Num() > 0)
            {
                FString ImagePath = Raw[0];
                FString CachedDisplayName = Raw.Last();
                DiplayNameListCache->Add(UserID, CachedDisplayName);

                TArray<uint8> ImageData;
                FString CacheImagePath = FString::Printf(TEXT("%s\\Cache\\%s"), *FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()), *ImagePath);

                if (FFileHelper::LoadFileToArray(ImageData, *CacheImagePath))
                {
                    ThumbnailBrushCache.Add(UserID, CreateBrush(FPaths::GetExtension(ImagePath), FName(*ImagePath), ImageData));
                }
            }
            UE_LOG(LogTemp, Log, TEXT("File to load:%s"), *FileToLoad);
        }
    }
    else
    {
        // userid.txt -> file name fisik 
        TArray<FString> Raw;
        AvatarURL.ParseIntoArray(Raw, TEXT("/"), true);
        FString FileName = Raw.Last();
        FString Cache = FString::Printf(TEXT("%s_%s\n%s"), *UserID, *FileName, *DisplayName);

        if (FFileHelper::SaveStringToFile(Cache, *CacheTextDir))
        {
            UE_LOG(LogTemp, Log, TEXT("cache meta saved locally"));
        }
        if (!AvatarListCache->Contains(UserID))
        {
            AvatarListCache->Add(UserID, AvatarURL);
            // start download avatar
            TSharedRef<IHttpRequest> ThumbRequest = FHttpModule::Get().CreateRequest();
            ThumbRequest->SetVerb("GET");
            ThumbRequest->SetURL(AvatarURL);
            ThumbRequest->OnProcessRequestComplete().BindRaw(this, &SLobby::OnThumbImageReceived, UserID);
            ThumbRequest->ProcessRequest();
        }


        if (!DiplayNameListCache->Contains(UserID))
        {
            DiplayNameListCache->Add(UserID, DisplayName);
        }


    }
};

void SLobby::SetCurrentUserFromCache(FString UserID, FString DisplayName, FString AvatarPath)
{
    CurrentUserID = UserID;
    CurrentUserDisplayName = DisplayName;
    CurrentAvatarURL = AvatarPath;

    DiplayNameListCache->Add(UserID, DisplayName);
    TArray<uint8> ImageData;
    if (FFileHelper::LoadFileToArray(ImageData, *AvatarPath))
    {
        ThumbnailBrushCache.Add(UserID, CreateBrush(FPaths::GetExtension(AvatarPath), FName(*AvatarPath), ImageData));
    }
}

FString SLobby::GetCurrentUserID()
{
	return CurrentUserID;
}

void SLobby::AddFriend(FString UserID, FString DisplayName, FString Avatar)
{
    TSharedPtr<FFriendEntry> FriendEntry1 = MakeShareable(new FFriendEntry());
    FriendEntry1->UserId = UserID;
    FriendEntry1->Name = DisplayName;
    FriendEntry1->AvatarSmallUrl = Avatar;
    FriendEntry1->Presence = "OFFLINE";
    CompleteFriendList.Add(FriendEntry1);

    // find file
    IFileManager& FileManager = IFileManager::Get();
    FString CacheTextDir = FString::Printf(TEXT("%s\\Cache\\%s.txt"), *FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()), *UserID);
    if (FileManager.FileExists(*CacheTextDir))
    {
        UE_LOG(LogTemp, Log, TEXT("cache meta found"));
        FString FileToLoad;
        if (FFileHelper::LoadFileToString(FileToLoad, *CacheTextDir))
        {
            TArray<FString> Raw;
            FileToLoad.ParseIntoArray(Raw, TEXT("\n"), true);
            if (Raw.Num() > 0)
            {
                FString ImagePath = Raw[0];
                FString CachedDisplayName = Raw.Last();
                DiplayNameListCache->Add(UserID, CachedDisplayName);

                TArray<uint8> ImageData;
                FString CacheImagePath = FString::Printf(TEXT("%s\\Cache\\%s"), *FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()), *ImagePath);

                if (FFileHelper::LoadFileToArray(ImageData, *CacheImagePath))
                {
                    ThumbnailBrushCache.Add(UserID, CreateBrush(FPaths::GetExtension(ImagePath), FName(*ImagePath), ImageData));
                }
            }
            UE_LOG(LogTemp, Log, TEXT("File to load:%s"), *FileToLoad);
        }
    }
    else
    {
        if (!AvatarListCache->Contains(UserID))
        {
            //get avatar from platform service (User profile)
            UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Start getting public user profile from platform service..."));
            AccelByte::Api::UserProfile::GetPublicUserProfileInfo(UserID, AccelByte::THandler<FAccelByteModelsPublicUserProfileInfo>::CreateLambda([this, UserID](const FAccelByteModelsPublicUserProfileInfo& UserProfileInfo) {
                UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Get User Public Profile: %s - > %s"), *UserProfileInfo.UserId, *UserProfileInfo.AvatarSmallUrl);
                AvatarListCache->Add(UserProfileInfo.UserId, UserProfileInfo.AvatarSmallUrl);

                // next get display name
                if (!DiplayNameListCache->Contains(UserID))
                {
                    UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Start getting public user profile from IAM service..."));
                    AccelByte::Api::User::GetPublicUserInfo(UserID, THandler<FPublicUserInfo>::CreateLambda([this, UserID, UserProfileInfo](const FPublicUserInfo& UserInfo) {
                        UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Get User Public Profile: %s - > %s"), *UserInfo.UserId, *UserInfo.DisplayName);
                        DiplayNameListCache->Add(UserInfo.UserId, UserInfo.DisplayName);

                        // save to our cache
                        FString CacheTextDir = FString::Printf(TEXT("%s\\Cache\\%s.txt"), *FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()), *UserID);

                        // userid.txt -> file name fisik \n display name

                        TArray<FString> Raw;
                        UserProfileInfo.AvatarSmallUrl.ParseIntoArray(Raw, TEXT("/"), true);
                        FString FileName = Raw.Last();
                        FString Cache = FString::Printf(TEXT("%s_%s\n%s"), *UserID, *FileName, *UserInfo.DisplayName);

                        if (FFileHelper::SaveStringToFile(Cache, *CacheTextDir))
                        {
                            UE_LOG(LogTemp, Log, TEXT("cache meta saved locally"));
                        }
                    }),
                        AccelByte::FErrorHandler::CreateLambda([&](int32 Code, FString Message) {
                        UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Get IAM User Public Profile Error"));
                    }));
                }

                // start download avatar
                TSharedRef<IHttpRequest> ThumbRequest = FHttpModule::Get().CreateRequest();
                ThumbRequest->SetVerb("GET");
                ThumbRequest->SetURL(UserProfileInfo.AvatarSmallUrl);
                ThumbRequest->OnProcessRequestComplete().BindRaw(this, &SLobby::OnThumbImageReceived, UserProfileInfo.UserId);
                ThumbRequest->ProcessRequest();

            }),
                AccelByte::FErrorHandler::CreateLambda([&](int32 Code, FString Message) {
                UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Get User Public Profile Error: "));
            }));
        }
    }
}

void SLobby::RefreshFriendList()
{
    FriendList = CompleteFriendList;
	UpdateSearchStatus();
}

FText SLobby::GetFriendHeaderText() const
{
	int32 OnlineFriendsCount = 0;
	int32 AllFriendsCount = FriendList.Num();

	for (int i = 0 ; i < AllFriendsCount; i++)
	{
		OnlineFriendsCount += (FriendList[i]->Presence == TEXT("ONLINE"));
	}

	return FText::FromString(FString::Printf(TEXT("    %d/%d IS ONLINE"), OnlineFriendsCount, AllFriendsCount));
}

/**
 * Ticks this widget.  Override in derived classes, but always call the parent implementation.
 *
 * @param  InCurrentTime  Current absolute real time
 * @param  InDeltaTime  Real time passed since last tick
 */
void SLobby::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if (bSearchingForFriends)
	{
		UpdateSearchStatus();
	}
}

void SLobby::UpdateFriendList()
{
	int32 SelectedItemIndex = FriendList.IndexOfByKey(SelectedItem);
	LobbyWidget->GetHeaderRow()->Column("Friend").DefaultLabel(GetFriendHeaderText());
	LobbyWidget->RequestListRefresh();
	if (FriendList.Num() > 0)
	{
		LobbyWidget->UpdateSelectionSet();
		LobbyWidget->SetSelection(FriendList[SelectedItemIndex > -1 ? SelectedItemIndex : 0], ESelectInfo::OnNavigation);
	}

}

void SLobby::OnFocusLost(const FFocusEvent& InFocusEvent)
{
	if (InFocusEvent.GetCause() != EFocusCause::SetDirectly)
	{
		FSlateApplication::Get().SetKeyboardFocus(SharedThis(this));
	}
}

FReply SLobby::OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent)
{
	return FReply::Handled().SetUserFocus(LobbyWidget.ToSharedRef(), EFocusCause::SetDirectly);
}

void SLobby::EntrySelectionChanged(TSharedPtr<FFriendEntry> InItem, ESelectInfo::Type SelectInfo)
{
    if (InItem.IsValid())
    {
        SelectedItem = InItem;
    }
}

void SLobby::MoveSelection(int32 MoveBy)
{
	int32 SelectedItemIndex = FriendList.IndexOfByKey(SelectedItem);

	if (SelectedItemIndex + MoveBy > -1 && SelectedItemIndex + MoveBy < FriendList.Num())
	{
		LobbyWidget->SetSelection(FriendList[SelectedItemIndex + MoveBy]);
	}
}

FReply SLobby::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (bSearchingForFriends) // lock input
	{
		return FReply::Handled();
	}

	FReply Result = FReply::Unhandled();
	const FKey Key = InKeyEvent.GetKey();

	if (Key == EKeys::Up || Key == EKeys::Gamepad_DPad_Up || Key == EKeys::Gamepad_LeftStick_Up)
	{
		MoveSelection(-1);
		Result = FReply::Handled();
	}
	else if (Key == EKeys::Down || Key == EKeys::Gamepad_DPad_Down || Key == EKeys::Gamepad_LeftStick_Down)
	{
		MoveSelection(1);
		Result = FReply::Handled();
	}
	else if (Key == EKeys::Enter || Key == EKeys::Virtual_Accept)
	{
		//ConnectToServer();
		// SOCIAL INVITE 
		Result = FReply::Handled();
		FSlateApplication::Get().SetKeyboardFocus(SharedThis(this));
	}

	return Result;
}

FReply SLobby::OnRequestFriend()
{
	AccelByte::Api::User::GetUserByLoginId(FriendSearchBar->GetText().ToString(), 
		THandler<FUserData>::CreateLambda([&](const FUserData& User)
		{
			AccelByte::FRegistry::Lobby.RequestFriend(User.UserId);
		}), 
		AccelByte::FErrorHandler::CreateLambda([&](int32 Code, FString Message) 
		{
			if (Code == 404)
			{
				FriendSearchBar->SetText(FText::FromString("NOT FOUND!!"));
			}
		}));
	return FReply::Handled();
}

void SLobby::OnThumbImageReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FString UserID)
{
    if (bWasSuccessful && Response.IsValid())
    {
        TArray<uint8> ImageData = Response->GetContent();
        ThumbnailBrushCache.Add(UserID, CreateBrush(Response->GetContentType(), FName(*Request->GetURL()), ImageData));        


        TArray<FString> Raw;
        Request->GetURL().ParseIntoArray(Raw, TEXT("/"), true);
        FString FileName = Raw.Last();

        // save to our cache
        FString CacheDir = FString::Printf(TEXT("%s\\Cache\\%s_%s"), *FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()), *UserID, *FileName);
        if (FFileHelper::SaveArrayToFile(ImageData, *CacheDir))
        {
            UE_LOG(LogTemp, Log, TEXT("cache saved locally"));
        }

    }
}

TSharedPtr<FSlateDynamicImageBrush> SLobby::CreateBrush(FString ContentType, FName ResourceName, TArray<uint8> ImageData)
{
    UE_LOG(LogTemp, Log, TEXT("SShooterUserProfileWidget::CreateBrush : %s, Content Type: %s"), *ResourceName.ToString(), *ContentType);
    TSharedPtr<FSlateDynamicImageBrush> Brush;

    uint32 BytesPerPixel = 4;
    int32 Width = 0;
    int32 Height = 0;

    bool bSucceeded = false;
    TArray<uint8> DecodedImage;
    IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));

    int BitDepth = 8;
    //jpg
    EImageFormat ImageFormat = EImageFormat::JPEG;
    ERGBFormat RgbFormat = ERGBFormat::BGRA;
    //png
    if (ContentType.Contains(TEXT("png")))
    {
        ImageFormat = EImageFormat::PNG;
        RgbFormat = ERGBFormat::BGRA;
    }
    //bmp
    else if (ContentType.Contains(TEXT("bmp")))
    {
        ImageFormat = EImageFormat::BMP;
        RgbFormat = ERGBFormat::BGRA;
    }

    TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(ImageFormat);
    if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(ImageData.GetData(), ImageData.Num()))
    {
        Width = ImageWrapper->GetWidth();
        Height = ImageWrapper->GetHeight();

        const TArray<uint8>* RawData = NULL;

        if (ImageWrapper->GetRaw(RgbFormat, BitDepth, RawData))
        {
            DecodedImage = *RawData;
            bSucceeded = true;
        }
    }

    if (bSucceeded && FSlateApplication::Get().GetRenderer()->GenerateDynamicImageResource(ResourceName, ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), DecodedImage))
    {
        Brush = MakeShareable(new FSlateDynamicImageBrush(ResourceName, FVector2D(ImageWrapper->GetWidth(), ImageWrapper->GetHeight())));
    }

    return Brush;
}


TSharedRef<ITableRow> SLobby::MakeListViewWidget(TSharedPtr<FFriendEntry> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	class SFriendEntryWidget : public SMultiColumnTableRow< TSharedPtr<FFriendEntry> >
	{
	public:
		
		const FLobbyStyle* LobbyStyle = &FShooterStyle::Get().GetWidgetStyle<FLobbyStyle>("DefaultLobbyStyle");

		SLATE_BEGIN_ARGS(SFriendEntryWidget) {}
		SLATE_END_ARGS()

		TSharedPtr<FFriendEntry> Item;
        TWeakPtr<SLobby, ESPMode::NotThreadSafe> ParentClass;
        

		void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TSharedPtr<FFriendEntry> InItem, SLobby* Parent)
		{
			Item = InItem;
            ParentClass = TWeakPtr<SLobby, ESPMode::NotThreadSafe>(StaticCastSharedRef<SLobby>(Parent->AsShared()));


			SMultiColumnTableRow< TSharedPtr<FFriendEntry> >::Construct(FTableRowArgs().Style(&LobbyStyle->FriendRowStyle), InOwnerTable);
		}

		TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName)
		{
			FText ItemText = FText::GetEmpty();
			return
				SNew(SHorizontalBox)

				+ SHorizontalBox::Slot()	//1.PROFILE PICTURE
				.AutoWidth()
				[
					SNew(SOverlay)

					+ SOverlay::Slot()		//1.1.BORDER
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					[
						SNew(SBox)
						.WidthOverride(84.0f)
						.HeightOverride(84.0f)
						[
							SNew(SImage)			
							.Image(&LobbyStyle->FriendAvatarBorderBrush)
						]
					]

					+ SOverlay::Slot()		//1.1.1.AVATAR
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						SNew(SBox)
						.WidthOverride(56.0f)
						.HeightOverride(56.0f)
						[
							SNew(SImage)				
							.Image(this, &SFriendEntryWidget::GetProfileAvatar)
						]
					]
				]

				+ SHorizontalBox::Slot()	//2.NAME + PRESENCE
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Fill)
				.FillWidth(1.0f)
				.Padding(8, 0, 8, 0)
				[
					SNew(SVerticalBox)

					+ SVerticalBox::Slot()
					.VAlign(VAlign_Bottom)
					.AutoHeight()
					[
						SNew(STextBlock)
						.Text(this, &SFriendEntryWidget::GetName)
						.TextStyle(&LobbyStyle->UserNameTextStyle)
						.AutoWrapText(true)
					]

					+ SVerticalBox::Slot()
					.VAlign(VAlign_Top)
					.AutoHeight()
					[
						SNew(STextBlock)
						.Text(this, &SFriendEntryWidget::GetPresence)
						.TextStyle(&LobbyStyle->PresenceTextStyle)
						.AutoWrapText(true)
					]
				]

				+ SHorizontalBox::Slot()	//3.CHAT BUTTON
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(0, 0, 0, 0)
				[
					SNew(SButton)
					.Visibility(this, &SFriendEntryWidget::PrivateChatButtonVisible)
					.OnClicked(this, &SFriendEntryWidget::OnPrivateChatClicked)
					.ButtonStyle(&LobbyStyle->ChatButtonStyle)
				]

                + SHorizontalBox::Slot()	//3.INVITE BUTTON
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(0, 0, 0, 0)
				[
					SNew(SButton)
					.Visibility(this, &SFriendEntryWidget::InviteButtonVisible)
					.OnClicked(this, &SFriendEntryWidget::OnInviteClicked)
					.ButtonStyle(&LobbyStyle->InviteButtonStyle)
				]

				+ SHorizontalBox::Slot()	//3.UNFRIEND BUTTON
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(0, 0, 0, 0)
				[
					SNew(SButton)
					.OnClicked(this, &SFriendEntryWidget::OnUnfriendClicked)
					.ButtonStyle(&LobbyStyle->UnfriendButtonStyle)
				]
			;
		}

		FReply OnPrivateChatClicked()
		{   
            if (ParentClass.IsValid())
            {
                FString DisplayName = Item->UserId;
                if (ParentClass.Pin()->CheckDisplayName(Item->Name))
                {
                    DisplayName = ParentClass.Pin()->GetDisplayName(Item->Name);
                }

                ParentClass.Pin()->LobbyChatWidget->AddPrivate(Item->UserId, DisplayName);
            }
            
            return FReply::Handled();
		}

        FReply OnInviteClicked()
        {
            if (ParentClass.IsValid())
            {
				AccelByte::FRegistry::Lobby.SendInviteToPartyRequest(Item->UserId);
            }
            return FReply::Handled();
        }

		FReply OnUnfriendClicked()
		{
			AccelByte::FRegistry::Lobby.Unfriend(Item->UserId);
			AccelByte::FRegistry::Lobby.LoadFriendsList();
			ParentClass.Pin()->LobbyChatWidget->Remove(Item->UserId);
			return FReply::Handled();
		}

		const FSlateBrush* GetProfileAvatar() const {
			if (ParentClass.Pin()->CheckAvatar(Item->Name))
			{
				return ParentClass.Pin()->GetAvatar(Item->Name).Get();
			}
			else
			{
                return FShooterStyle::Get().GetBrush("ShooterGame.Speaker");
			}
		}

		FText GetName() const 
        {
            if (ParentClass.Pin()->CheckDisplayName(Item->Name))
            {
                return FText::FromString(ParentClass.Pin()->GetDisplayName(Item->Name));
            }
            return FText::FromString(Item->Name); 
        }
		FText GetPresence() const { return FText::FromString(Item->Presence); }


        EVisibility PrivateChatButtonVisible() const
        {
            if (Item->Presence == TEXT("ONLINE"))
            {
                return EVisibility::Visible;
            }
            else
            {
                return EVisibility::Collapsed;
            }
        }

		EVisibility InviteButtonVisible() const
		{
			if (Item->Presence == TEXT("ONLINE"))
			{
				return EVisibility::Visible;
			}
			else
			{
				return EVisibility::Collapsed;
			}
		}
	};
	return SNew(SFriendEntryWidget, OwnerTable, Item, this);
}

#pragma region FRIENDS_SERVICE

	void SLobby::OnRequestFriendSent(const FAccelByteModelsRequestFriendsResponse& Response)
	{
		FString Message;
		if (Response.Code == TEXT("11703"))
		{
			Message = TEXT("You already sent a request!");
		} else
		if (Response.Code == TEXT("0"))
		{
			Message = TEXT("Successfully sent a friend request!");
		}
		else
		{
			Message = FString::Printf(TEXT("Failed. Error code= %s"), *Response.Code);
		}

		SAssignNew(NotificationOverlay, SOverlay)
		+ SOverlay::Slot()
			[
				SNew(SBox)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
					.Image(&OverlayBackgroundBrush)
				]
			]
		+ SOverlay::Slot()
			[
				SNew(SShooterConfirmationDialog).PlayerOwner(PlayerOwner)
				.MessageText(FText::FromString(Message))
				.ConfirmText(FText::FromString("CLOSE"))
				.OnConfirmClicked(FOnClicked::CreateLambda([&]()
				{
					if (NotificationOverlay.IsValid())
					{
						GEngine->GameViewport->RemoveViewportWidgetContent(NotificationOverlay.ToSharedRef());
						NotificationOverlay.Reset();
					}
					return FReply::Handled();
				}))
			];

		GEngine->GameViewport->AddViewportWidgetContent(NotificationOverlay.ToSharedRef());
		FSlateApplication::Get().SetKeyboardFocus(NotificationOverlay);
	}

	void SLobby::OnIncomingListFriendRequest(const FAccelByteModelsListIncomingFriendsResponse& Response)
	{
		if (Response.friendsId.Num() == 0) 
		{
			return;
		} 

		AccelByte::Api::User::GetPublicUserInfo(Response.friendsId[0], THandler<FPublicUserInfo>::CreateLambda([&, Response](const FPublicUserInfo& User)
		{

		FString DisplayedRequestName = (User.EmailAddress != TEXT("")) ? User.EmailAddress : User.DisplayName;

		SAssignNew(NotificationOverlay, SOverlay)
		+ SOverlay::Slot()
			[
				SNew(SBox)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
					.Image(&OverlayBackgroundBrush)
				]
			]
		+ SOverlay::Slot()
			[
				SNew(SShooterConfirmationDialog).PlayerOwner(PlayerOwner)
				.MessageText(FText::FromString(FString::Printf(TEXT("You have an incoming friend request from %s"), *DisplayedRequestName)))
				.ConfirmText(FText::FromString("ACCEPT"))
				.OnConfirmClicked(FOnClicked::CreateLambda([&, Response]()
				{
					AccelByte::FRegistry::Lobby.AcceptFriend(Response.friendsId[0]);
					AccelByte::FRegistry::Lobby.LoadFriendsList();
					if (NotificationOverlay.IsValid())
					{
						GEngine->GameViewport->RemoveViewportWidgetContent(NotificationOverlay.ToSharedRef());
						NotificationOverlay.Reset();
					}
					if (Response.friendsId.Num() > 1)
					{
						AccelByte::FRegistry::Lobby.ListIncomingFriends();
					}
					return FReply::Handled();
				}))
				.CancelText(FText::FromString("REJECT"))
				.OnCancelClicked(FOnClicked::CreateLambda([&, Response]()
				{
					AccelByte::FRegistry::Lobby.RejectFriend(Response.friendsId[0]);
					if (NotificationOverlay.IsValid())
					{
						GEngine->GameViewport->RemoveViewportWidgetContent(NotificationOverlay.ToSharedRef());
						NotificationOverlay.Reset();
					}
					if (Response.friendsId.Num() > 1)
					{
						AccelByte::FRegistry::Lobby.ListIncomingFriends();
					}
					return FReply::Handled();
				}))
			];

		GEngine->GameViewport->AddViewportWidgetContent(NotificationOverlay.ToSharedRef());
		FSlateApplication::Get().SetKeyboardFocus(NotificationOverlay);

		}),
		FErrorHandler::CreateLambda([&](int32 Code, FString Message){}));

	}

	void SLobby::OnFriendListLoaded(const FAccelByteModelsLoadFriendListResponse& Response)
	{
		InitializeFriends();

		if (Response.Code != TEXT("0"))
		{
			return;
		}

		FriendList.Reset();
		CompleteFriendList.Reset();
		
		for (int i = 0; i < Response.friendsId.Num(); i++)
		{
			AddFriend(Response.friendsId[i], Response.friendsId[i], TEXT("https://s3-us-west-2.amazonaws.com/justice-platform-service/avatar.jpg"));
		}
		AccelByte::FRegistry::Lobby.SendGetOnlineUsersRequest();

		RefreshFriendList();
	}

	void SLobby::OnFriendRequestAcceptedNotification(const FAccelByteModelsAcceptFriendsNotif& Response)
	{
		AccelByte::Api::User::GetPublicUserInfo(Response.friendId, THandler<FPublicUserInfo>::CreateLambda([&, Response](const FPublicUserInfo& User)
		{
			RefreshFriendList();
			FSlateBrush* FriendAvatar = CheckAvatar(Response.friendId) ? GetAvatar(Response.friendId).Get() : (FSlateBrush*)FShooterStyle::Get().GetBrush("ShooterGame.Speaker");

			FString NotificationMessage = FString::Printf(TEXT("%s accept your friend request!"), (User.EmailAddress == TEXT(""))? *User.EmailAddress : *User.DisplayName);
			TSharedPtr<SShooterNotificationPopup> Popup = SNew(SShooterNotificationPopup)
				.NotificationMessage(NotificationMessage)
				.AvatarImage(FriendAvatar)
				.OnPopupClosed_Lambda([]()
			{
			});
			Popup->Show();

			AccelByte::FRegistry::Lobby.LoadFriendsList();
		}), FErrorHandler::CreateLambda([&](int32 Code, FString Message) {}));

	}

	void SLobby::OnIncomingFriendRequestNotification(const FAccelByteModelsRequestFriendsNotif& Response)
	{
		FString DisplayName = CheckDisplayName(Response.friendId) ? GetDisplayName(Response.friendId) : Response.friendId;

		AccelByte::Api::User::GetPublicUserInfo(Response.friendId, THandler<FPublicUserInfo>::CreateLambda([&, Response](const FPublicUserInfo& User)
		{

		SAssignNew(NotificationOverlay, SOverlay)
		+ SOverlay::Slot()
			[
				SNew(SBox)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
					.Image(&OverlayBackgroundBrush)
				]
			]
		+ SOverlay::Slot()
			[
				SNew(SShooterConfirmationDialog).PlayerOwner(PlayerOwner)
				.MessageText(FText::FromString(FString::Printf(TEXT("You have an incoming friend request from %s"), (User.EmailAddress == TEXT(""))? *User.EmailAddress : *User.DisplayName)))
				.ConfirmText(FText::FromString("ACCEPT"))
				.OnConfirmClicked(FOnClicked::CreateLambda([&, Response]()
				{
					AccelByte::FRegistry::Lobby.AcceptFriend(Response.friendId);
					if (NotificationOverlay.IsValid())
					{
						GEngine->GameViewport->RemoveViewportWidgetContent(NotificationOverlay.ToSharedRef());
						NotificationOverlay.Reset();
					}
					AccelByte::FRegistry::Lobby.LoadFriendsList();
					return FReply::Handled();
				}))
				.CancelText(FText::FromString("REJECT"))
				.OnCancelClicked(FOnClicked::CreateLambda([&, Response]()
				{
					AccelByte::FRegistry::Lobby.RejectFriend(Response.friendId);
					if (NotificationOverlay.IsValid())
					{
						GEngine->GameViewport->RemoveViewportWidgetContent(NotificationOverlay.ToSharedRef());
						NotificationOverlay.Reset();
					}
					return FReply::Handled();
				}))
			];

		GEngine->GameViewport->AddViewportWidgetContent(NotificationOverlay.ToSharedRef());
		FSlateApplication::Get().SetKeyboardFocus(NotificationOverlay);

		}), FErrorHandler::CreateLambda([&](int32 Code, FString Message) {}));
	}

#pragma endregion FRIENDS_SERVICE

void SLobby::OnIncomingNotification(const FAccelByteModelsNotificationMessage& MessageNotification)
{
	if (MessageNotification.Topic != TEXT("0004"))
	{
		return;
	}

	SAssignNew(NotificationOverlay, SOverlay)
		+ SOverlay::Slot()
		[
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(&OverlayBackgroundBrush)
			]
		]
		+ SOverlay::Slot()
		[
			SNew(SShooterConfirmationDialog).PlayerOwner(PlayerOwner)
			.MessageText(FText::FromString(FString::Printf(TEXT("Notification!\nFrom: %s\nMessage: %s"), *MessageNotification.From, *MessageNotification.Payload)))
			.ConfirmText(FText::FromString("CLOSE"))
			.OnConfirmClicked(FOnClicked::CreateLambda([&]()
			{
				if (NotificationOverlay.IsValid())
				{
					GEngine->GameViewport->RemoveViewportWidgetContent(NotificationOverlay.ToSharedRef());
					NotificationOverlay.Reset();
				}
				return FReply::Handled();
			}))
		];

	GEngine->GameViewport->AddViewportWidgetContent(NotificationOverlay.ToSharedRef());
	FSlateApplication::Get().SetKeyboardFocus(NotificationOverlay);
}

void SLobby::OnGetOnlineUserResponse(const FAccelByteModelsGetOnlineUsersResponse& Response)
{
	for (int i = 0; i < Response.friendsId.Num(); i++)
	{
		if (Response.activity[i] == "Shooter Game")
		{
			for (int j = 0; j < CompleteFriendList.Num(); j++)
			{
				if (CompleteFriendList[j]->UserId == Response.friendsId[i])
				{
					if (Response.availability[i] == "0") { CompleteFriendList[j]->Presence = "OFFLINE"; }
					else if (Response.availability[i] == "1") { CompleteFriendList[j]->Presence = "ONLINE"; }
				}
			}
		}
	}
	RefreshFriendList();
	UpdateSearchStatus();
}

#undef LOCTEXT_NAMESPACE