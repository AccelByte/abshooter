// Copyright (c) 2019 - 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "Utils/ImageUtils.h"

// TODO: Migrate into UMG
#include "ShooterGame.h"
#include "SLobby.h"
#include "SHeaderRow.h"
#include "ShooterStyle.h"
#include "ShooterMenuWidgetStyle.h"
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
#include "ShooterGameConfig.h"
#include "Engine/World.h"
#include "ShooterGameTelemetry.h"

// AccelByte
#include "Api/AccelByteLobbyApi.h"
#include "Api/AccelByteUserApi.h"
#include "Core/AccelByteRegistry.h"

#define LOCTEXT_NAMESPACE "ShooterGame.HUD.Menu"
#define SIMULATE_SETUP_MATCHMAKING 0
#include "Server/Models/AccelByteMatchmakingModels.h"

SLobby::SLobby()
	: OverlayBackgroundBrush(FLinearColor(0, 0, 0, 0.8f))
	, ConfirmationBackgroundBrush(FLinearColor(0, 0, 0, 0.8f))
{

}

void SLobby::Construct(const FArguments& InArgs)
{
	const FLobbyStyle* LobbyStyle = &FShooterStyle::Get().GetWidgetStyle<FLobbyStyle>("DefaultLobbyStyle");
	const FShooterMenuStyle* MenuStyle = &FShooterStyle::Get().GetWidgetStyle<FShooterMenuStyle>("DefaultShooterMenuStyle");
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

	AccelByte::FRegistry::Lobby.SetLeavePartyResponseDelegate(AccelByte::Api::Lobby::FPartyLeaveResponse::CreateLambda([this](const FAccelByteModelsLeavePartyResponse& Response)
	{
		PartyWidget->ResetAll();
		LobbyChatWidget->RemovePartyChatTab(CurrentPartyID);
		CurrentPartyID = TEXT("");
	}));
	AccelByte::FRegistry::Lobby.SetMessageNotifDelegate(AccelByte::Api::Lobby::FMessageNotif::CreateSP(this, &SLobby::OnIncomingNotification));
	AccelByte::FRegistry::Lobby.SetStartMatchmakingResponseDelegate(AccelByte::Api::Lobby::FMatchmakingResponse::CreateLambda([&](const FAccelByteModelsMatchmakingResponse& Response)
	{
		if (Response.Code != "0")
		{
			bMatchmakingStarted = false;
			PartyWidget->UpdateMatchmakingStatus(bMatchmakingStarted);
		}
	}));
	AccelByte::FRegistry::Lobby.SetMatchmakingNotifDelegate(AccelByte::Api::Lobby::FMatchmakingNotif::CreateLambda([&](const FAccelByteModelsMatchmakingNotice& Response)
	{
		if (Response.Status == EAccelByteMatchmakingStatus::Done)
		{
			ShooterGameTelemetry::Get().StartMatch(Response.MatchId, this->GameMode);

			FString MatchId = Response.MatchId;

			CloseMessageDialog();
			ShowMessageDialog("Ready?", FOnClicked::CreateLambda([MatchId, this]()
			{
				AccelByte::FRegistry::Lobby.SendReadyConsentRequest(MatchId);
				bReadyConsent = true;
				CloseMessageDialog();

				return FReply::Handled();
			}));
		}
		// show loading for non leader party member
		else if (Response.Status == EAccelByteMatchmakingStatus::Start)
		{
			bMatchmakingStarted = true;
			PartyWidget->UpdateMatchmakingStatus(bMatchmakingStarted);
		}
		else
		{
			FString FailMatchmakingReason = "UNKNOWN";
			switch (Response.Status)
			{
			case EAccelByteMatchmakingStatus::Cancel:
				FailMatchmakingReason = "Matchmaking canceled by party leader";
				break;
			case EAccelByteMatchmakingStatus::Timeout:
				FailMatchmakingReason = "Timeout";
				break;
			case EAccelByteMatchmakingStatus::Unavailable :
				FailMatchmakingReason = "Dedicated server unavailable";
				break;
			default:
				FailMatchmakingReason = FString::Printf(TEXT("Code: %d"), (int32)Response.Status);
				break;
			}

			ShowMessageDialog(FString::Printf(TEXT("Failed to do matchmaking\nReason: %s"), *FailMatchmakingReason), FOnClicked::CreateLambda([&]()
			{
				CloseMessageDialog();
				return FReply::Handled();
			}));

			bMatchmakingStarted = false;
			PartyWidget->UpdateMatchmakingStatus(bMatchmakingStarted);
		}
	}));
	AccelByte::FRegistry::Lobby.SetCancelMatchmakingResponseDelegate(AccelByte::Api::Lobby::FMatchmakingResponse::CreateLambda([&](const FAccelByteModelsMatchmakingResponse& Response)
	{
		bMatchmakingStarted = false;
		PartyWidget->UpdateMatchmakingStatus(bMatchmakingStarted);
	}));
	AccelByte::FRegistry::Lobby.SetDsNotifDelegate(AccelByte::Api::Lobby::FDsNotif::CreateLambda([&](const FAccelByteModelsDsNotice& Notice)
	{
		UE_LOG(LogOnlineGame, Log, TEXT("DS Notif Status: %s"), *Notice.Status);

		if (Notice.Status.Compare(TEXT("READY")) == 0 || Notice.Status.Compare(TEXT("BUSY")) == 0)
		{
			FString ServerAddress;
			if (ShooterGameConfig::Get().IsLocalMode_)
			{
				ServerAddress = FString::Printf(TEXT("%s:%i"), *ShooterGameConfig::Get().LocalServerIP_, ShooterGameConfig::Get().ServerPort_);
			}
			else
			{
				ServerAddress = FString::Printf(TEXT("%s:%i"), *Notice.Ip, Notice.Port);
			}
			UE_LOG(LogOnlineGame, Log, TEXT("StartMatch: %s"), *ServerAddress);
			StartMatch(Notice.MatchId, this->CurrentPartyID, ServerAddress);
		}
		else if (Notice.Status.Compare(TEXT("CREATING")) == 0)
		{
			bAlreadyEnteringLevel = false;
		}
	}));
	AccelByte::FRegistry::Lobby.SetRematchmakingNotifDelegate(AccelByte::Api::Lobby::FRematchmakingNotif::CreateLambda([&](const FAccelByteModelsRematchmakingNotice& Notice)
	{
		bReadyConsent = false;
		if (Notice.BanDuration == 0)
		{
			ShowMessageDialog("Your Opponent's Party Have been Banned Because of Long Term Inactivity. We'll Rematch You with Another Party.", FOnClicked::CreateLambda([this]()
			{
				bMatchmakingStarted = true;
				PartyWidget->UpdateMatchmakingStatus(bMatchmakingStarted);
				CloseMessageDialog();
				return FReply::Handled();
			}));
		}
		else
		{
			CloseMessageDialog();
			ShowMessageDialog(FString::Printf(TEXT("You're Banned for %d sec Because of Long Term Inactivity. You Can Search for A Match Again After the Ban is Lifted."), Notice.BanDuration), FOnClicked::CreateLambda([this]()
			{
				bMatchmakingStarted = false;
				PartyWidget->UpdateMatchmakingStatus(bMatchmakingStarted);
				CloseMessageDialog();
				return FReply::Handled();
			}));
		}
	}));

	ChildSlot
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SNew(SBox)
				.HeightOverride(TAttribute<FOptionalSize>::Create([&]()
				{
					return FOptionalSize(GetLobbyHeight(1.0));
				}))
				.WidthOverride(TAttribute<FOptionalSize>::Create([&]()
				{
					return FOptionalSize(GetLobbyWidth(1.0));
				}))
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Center)
				.Padding(FMargin(0, 40, 0, 0))
				[
					SNew(SHorizontalBox)

	#pragma region FriendWidget_ChatWidget
					+ SHorizontalBox::Slot()
					.MaxWidth(TAttribute<float>::Create([&]()
					{
						return GetLobbyWidth(2);
					}))
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

							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							[
								SNew(SImage)
								.Image(&LobbyStyle->SearchBarBackground)
							]

							+ SOverlay::Slot()
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
										.HintText(FText::FromString(TEXT("Type email here")))
										.MinDesiredWidth(300.0f)
										.SelectAllTextWhenFocused(true)
										.Style(&LobbyStyle->SearchBarStyle)
									]
								]
							]
						]
	#pragma endregion SearchFriend

	#pragma region FriendList
						+ SVerticalBox::Slot()	//FriendListView
						.FillHeight(1.0f)
						.MaxHeight(TAttribute<float>::Create([&]()
						{
							return GetLobbyHeight(2.5);
						}))
						.HAlign(HAlign_Fill)
						[
							SNew(SOverlay)

							+ SOverlay::Slot()
							[
								SNew(SImage)
								.Image(&LobbyStyle->FriendListBackground)
							]

							+ SOverlay::Slot()
							[
								SNew(SHorizontalBox)

								+ SHorizontalBox::Slot()	//NonScrollBar
								.HAlign(HAlign_Fill)
								[
									SNew(SBox)
									.HAlign(HAlign_Fill)
									.HeightOverride(TAttribute<FOptionalSize>::Create([&]()
									{
										return FOptionalSize(GetLobbyHeight(2.0));
									}))
									.WidthOverride(TAttribute<FOptionalSize>::Create([&]()
									{
										return FOptionalSize(GetLobbyWidth(3.0));
									}))
									[
										SAssignNew(LobbyWidget, SListView<TSharedPtr<FFriendEntryDeprecated>>)
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
								.Padding(TAttribute<FMargin>::Create([&]()
								{
									return FMargin(0.f, LobbyWidget->GetHeaderRow()->GetDesiredSize().Y, 0.f, 0.f);
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

						+ SVerticalBox::Slot()	//MARGIN FRIEND >=< CHAT
						.FillHeight(0.1f)
						[
							SNew(SBox)
						]

#pragma region ChatWidget
						+ SVerticalBox::Slot()		//CHAT Widget
						.VAlign(VAlign_Fill)
						.MaxHeight(TAttribute<float>::Create([&]()
						{
							return GetLobbyHeight(3.0);
						}))
						.FillHeight(.8f)
						.HAlign(HAlign_Fill)
						[
							SNew(SOverlay)

							+ SOverlay::Slot()
							[
								SNew(SImage)
								.Image(&LobbyStyle->ChatAreaBackground)
							]

							+ SOverlay::Slot()
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
						.WidthOverride(TAttribute<FOptionalSize>::Create([&]()
						{
							return FOptionalSize(GetLobbyWidth(12.0));
						}))
					]

#pragma region PartyWidget_StartMatchWidget
					+ SHorizontalBox::Slot()
					.MaxWidth(TAttribute<float>::Create([&]()
					{
						return GetLobbyWidth(2.5);
					}))
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
									if (CurrentPartyID != "")
									{
										if (bIsPartyLeader && !bMatchmakingStarted)
										{
											return EVisibility::Visible;
										}
									}

									return EVisibility::Collapsed;
								}))
								.OnClicked(FOnClicked::CreateLambda([&]
								{
									bMatchmakingStarted = true;
									PartyWidget->UpdateMatchmakingStatus(bMatchmakingStarted);
									bReadyConsent = false;
									GameMode = FString::Printf(TEXT("%dvs%d"), PartyWidget->GetCurrentPartySize(), PartyWidget->GetCurrentPartySize());

									TSharedPtr<FTimerHandle> DummyHandle = MakeShared<FTimerHandle>();
									GEngine->GameViewport->GetWorld()->GetTimerManager().SetTimer(*DummyHandle, TFunction<void(void)>([&, DummyHandle]()
									{
										if (!FRegistry::Lobby.IsConnected())
										{
											bMatchmakingStarted = false;
											GEngine->GameViewport->GetWorld()->GetTimerManager().ClearTimer(*DummyHandle);
											ShowMessageDialog("Connection lost when finding match!", FOnClicked::CreateLambda([&]()
											{
												CloseMessageDialog();
												return FReply::Handled();
											}));
										}
										else
										{
											if (bAlreadyEnteringLevel)
											{
												GEngine->GameViewport->GetWorld()->GetTimerManager().ClearTimer(*DummyHandle);
											}
										}
									}), 1.0f, true, 0.f);

									if (ShooterGameConfig::Get().IsLocalMode_)
									{
										AccelByte::FRegistry::Lobby.SendStartMatchmaking(
											GameMode,
											ShooterGameConfig::Get().LocalServerName_
										);
									}
									else
									{
										AccelByte::FRegistry::Lobby.SendStartMatchmaking(
											GameMode,
											TEXT(""),
											ShooterGameConfig::Get().ServerImageVersion_,
											ShooterGameConfig::Get().SelectedRegion_
										);
									}
		
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
								.VAlign(VAlign_Center)
								.AutoWidth()
								[
									SNew(SOverlay)
									+ SOverlay::Slot()
									[
										SNew(STextBlock)
										.Text(FText::FromString("Finding Match"))
										.TextStyle(&LobbyStyle->FindingMatchTextStyle)
										.Visibility(TAttribute<EVisibility>::Create([&]
										{
											return !bReadyConsent ? EVisibility::Visible : EVisibility::Collapsed;
										}))
									]
									+ SOverlay::Slot()
									[
										SNew(STextBlock)
										.Text(FText::FromString("Waiting for the Other Party"))
										.TextStyle(&LobbyStyle->FindingMatchTextStyle)
										.Visibility(TAttribute<EVisibility>::Create([&]
										{
											return bReadyConsent ? EVisibility::Visible : EVisibility::Collapsed;
										}))
									]
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
									.ButtonStyle(&LobbyStyle->CancelMatchButton)
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
			]

			+ SOverlay::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Right)
			.Padding(0, 0, 200, 17)
			[
				SNew(SBox)
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Right)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SButton)
						.ButtonStyle(&MenuStyle->EscapeButton)
						.VAlign(VAlign_Bottom)
						.OnClicked(FOnClicked::CreateLambda([&]()
						{
							static_cast<SShooterMenuWidget*>(OwnerWidget.Get())->MenuGoBack();
							return FReply::Handled();
						}))
					]
					+ SHorizontalBox::Slot()
					.Padding(10, 0, 0, 0)
					.AutoWidth()
					[
						SNew(SImage)
						.Image(&MenuStyle->EscapeMainMenuInfo)
					]
				]
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

	return (ViewPortSize.Y / Divider);
}

float SLobby::GetLobbyWidth(float Divider) const
{
	FVector2D ViewPortSize = FVector2D(1, 1);
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewPortSize);
	}

	return float(ViewPortSize.X / Divider);
}

void SLobby::StartMatch(const FString& MatchId, const FString& PartyId, const FString& DedicatedServerAddress)
{
	if (this->bAlreadyEnteringLevel == false)
	{
		this->bAlreadyEnteringLevel = true;
		OnStartMatch.ExecuteIfBound();
		UE_LOG(LogOnlineGame, Log, TEXT("OpenLevel: %s"), *DedicatedServerAddress);

		// Add delay to ensure the server has received a heartbeat response contains matchmaking result
		// Player only entering level once
		FTimerHandle dummyHandle;
		GEngine->GameViewport->GetWorld()->GetTimerManager().SetTimer(dummyHandle, TFunction<void(void)>([this, DedicatedServerAddress, PartyId, MatchId, CurrentUserId = GetCurrentUserID()]()
		{
				UGameplayStatics::OpenLevel(GEngine->GameViewport->GetWorld(), FName(*DedicatedServerAddress), true, FString::Printf(TEXT("PartyId=%s?MatchId=%s?UserId=%s"), *PartyId, *MatchId, *CurrentUserId));
		}), 1.0f, false, ShooterGameConfig::Get().PlayerEnteringServerDelay_);
	}

}

void SLobby::ShowMessageDialog(FString Message, FOnClicked OnClicked)
{
	TSharedPtr<SShooterConfirmationDialog> Dialog;
	SAssignNew(MessageDialogWidget, SOverlay)
		+ SOverlay::Slot()
		[
			SNew(SImage)
			.Image(&ConfirmationBackgroundBrush)
		]
	+ SOverlay::Slot()
		[
			SAssignNew(Dialog, SShooterConfirmationDialog).PlayerOwner(PlayerOwner)
			.MessageText(FText::FromString(Message))
		.ConfirmText(FText::FromString("OK"))
		.OnConfirmClicked(OnClicked)
		];

	GEngine->GameViewport->AddViewportWidgetContent(MessageDialogWidget.ToSharedRef());
	FSlateApplication::Get().SetKeyboardFocus(Dialog);
}

void SLobby::CloseMessageDialog()
{
	if (MessageDialogWidget.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(MessageDialogWidget.ToSharedRef());
		MessageDialogWidget.Reset();
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
					ThumbnailBrushCache.Add(UserID, FShooterImageUtils::CreateBrush(FPaths::GetExtension(ImagePath), FName(*ImagePath), ImageData));
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
		ThumbnailBrushCache.Add(UserID, FShooterImageUtils::CreateBrush(FPaths::GetExtension(AvatarPath), FName(*AvatarPath), ImageData));
	}
}

FString SLobby::GetCurrentUserID()
{
	return CurrentUserID;
}

void SLobby::AddFriend(FString UserID, FString DisplayName, FString Avatar, FriendEntryTypeDeprecated Type)
{
	for (auto entry : CompleteFriendList)
	{
		if (entry->UserId == UserID)
		{
			return;
		}
	}

	TSharedPtr<FFriendEntryDeprecated> FriendEntry1 = MakeShareable(new FFriendEntryDeprecated());
	FriendEntry1->UserId = UserID;
	FriendEntry1->Name = DisplayName;
	FriendEntry1->AvatarSmallUrl = Avatar;
	FriendEntry1->Presence = "OFFLINE";
	FriendEntry1->Type = Type;
	CompleteFriendList.Insert(FriendEntry1, 0);

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
					ThumbnailBrushCache.Add(UserID, FShooterImageUtils::CreateBrush(FPaths::GetExtension(ImagePath), FName(*ImagePath), ImageData));
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
			FRegistry::UserProfile.GetPublicUserProfileInfo(UserID, AccelByte::THandler<FAccelByteModelsPublicUserProfileInfo>::CreateLambda([this, UserID](const FAccelByteModelsPublicUserProfileInfo& UserProfileInfo)
			{
				UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Get User Public Profile: %s - > %s"), *UserProfileInfo.UserId, *UserProfileInfo.AvatarSmallUrl);
				AvatarListCache->Add(UserProfileInfo.UserId, UserProfileInfo.AvatarSmallUrl);

				// next get display name
				if (!DiplayNameListCache->Contains(UserID))
				{
					UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Start getting public user profile from IAM service..."));
					FRegistry::User.GetUserByUserId(UserID, THandler<FUserData>::CreateLambda([this, UserID, UserProfileInfo](const FUserData& UserData)
					{
						UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Get User Public Profile: %s - > %s"), *UserData.UserId, *UserData.DisplayName);
						DiplayNameListCache->Add(UserData.UserId, UserData.DisplayName);

						// save to our cache
						FString CacheTextDir = FString::Printf(TEXT("%s\\Cache\\%s.txt"), *FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()), *UserID);

						// userid.txt -> file name fisik \n display name

						TArray<FString> Raw;
						UserProfileInfo.AvatarSmallUrl.ParseIntoArray(Raw, TEXT("/"), true);
						FString FileName = Raw.Last();
						FString Cache = FString::Printf(TEXT("%s_%s\n%s"), *UserID, *FileName, *UserData.DisplayName);

						if (FFileHelper::SaveStringToFile(Cache, *CacheTextDir))
						{
							UE_LOG(LogTemp, Log, TEXT("cache meta saved locally"));
						}
					}),
						AccelByte::FErrorHandler::CreateLambda([&](int32 Code, FString Message)
					{
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
				AccelByte::FErrorHandler::CreateLambda([&](int32 Code, FString Message)
			{
				UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Get User Public Profile Error: "));
			}));
		}
	}
}

void SLobby::RemoveFriend(FString UserId)
{
	for (int i = 0; i < CompleteFriendList.Num(); i++)
	{
		if (CompleteFriendList[i]->UserId == UserId)
		{
			CompleteFriendList.RemoveAt(i);
			RefreshFriendList();
			break;
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
	int32 AllFriendsCount = 0;

	for (int i = 0; i < FriendList.Num(); i++)
	{
		OnlineFriendsCount += ((FriendList[i]->Presence == TEXT("ONLINE")) && FriendList[i]->Type == FriendEntryTypeDeprecated::FRIEND);
		AllFriendsCount += (FriendList[i]->Type == FriendEntryTypeDeprecated::FRIEND);
	}

	return FText::FromString(FString::Printf(TEXT("    %d/%d ONLINE FRIENDS"), OnlineFriendsCount, AllFriendsCount));
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

void SLobby::EntrySelectionChanged(TSharedPtr<FFriendEntryDeprecated> InItem, ESelectInfo::Type SelectInfo)
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

FSlateBrush* SLobby::GetAvatarOrDefault(const FString& UserId) const
{
	//if (CheckAvatar(UserId))
	//{
	//	return GetAvatar(UserId).Get();
	//}
	//else
	//{
	return (FSlateBrush*)FShooterStyle::Get().GetBrush("ShooterGame.Avatar");
	//}
}

void SLobby::OnThumbImageReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FString UserID)
{
	if (bWasSuccessful && Response.IsValid())
	{
		TArray<uint8> ImageData = Response->GetContent();
		ThumbnailBrushCache.Add(UserID, FShooterImageUtils::CreateBrush(Response->GetContentType(), FName(*Request->GetURL()), ImageData));


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

TSharedRef<ITableRow> SLobby::MakeListViewWidget(TSharedPtr<FFriendEntryDeprecated> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	class SFriendEntryWidget : public SMultiColumnTableRow< TSharedPtr<FFriendEntryDeprecated> >
	{
	public:

		const FLobbyStyle* LobbyStyle = &FShooterStyle::Get().GetWidgetStyle<FLobbyStyle>("DefaultLobbyStyle");

		SLATE_BEGIN_ARGS(SFriendEntryWidget)
		{}
		SLATE_END_ARGS()

			TSharedPtr<FFriendEntryDeprecated> Item;
		TWeakPtr<SLobby, ESPMode::NotThreadSafe> ParentClass;


		void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TSharedPtr<FFriendEntryDeprecated> InItem, SLobby* Parent)
		{
			Item = InItem;
			ParentClass = TWeakPtr<SLobby, ESPMode::NotThreadSafe>(StaticCastSharedRef<SLobby>(Parent->AsShared()));


			SMultiColumnTableRow< TSharedPtr<FFriendEntryDeprecated> >::Construct(FTableRowArgs().Style(&LobbyStyle->FriendRowStyle), InOwnerTable);
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

			+ SHorizontalBox::Slot()	//3.CHAT BUTTON FriendEntryType::FRIEND
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(0, 0, 0, 0)
				[
					SNew(SButton)
					.Visibility(this, &SFriendEntryWidget::PrivateChatButtonVisible)
				.OnClicked(this, &SFriendEntryWidget::OnPrivateChatClicked)
				.ButtonStyle(&LobbyStyle->ChatButtonStyle)
				]

			+ SHorizontalBox::Slot()	//3.INVITE BUTTON FriendEntryType::FRIEND
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(0, 0, 0, 0)
				[
					SNew(SButton)
					.Visibility(this, &SFriendEntryWidget::InviteButtonVisible)
				.OnClicked(this, &SFriendEntryWidget::OnInviteClicked)
				.ButtonStyle(&LobbyStyle->InviteButtonStyle)
				]
			;
		}

		FReply OnPrivateChatClicked()
		{
			if (ParentClass.IsValid())
			{
				FString DisplayName = Item->UserId;
				if (ParentClass.Pin()->CheckDisplayName(Item->UserId))
				{
					DisplayName = ParentClass.Pin()->GetDisplayName(Item->UserId);
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

		const FSlateBrush* GetProfileAvatar() const
		{
			return ParentClass.Pin()->GetAvatarOrDefault(Item->Name);
		}

		FText GetName() const
		{
			if (ParentClass.Pin()->CheckDisplayName(Item->Name))
			{
				return FText::FromString(ParentClass.Pin()->GetDisplayName(Item->Name));
			}
			return FText::FromString(Item->Name);
		}
		FText GetPresence() const
		{
			if (Item->Type == FRIEND)
			{
				return FText::FromString(Item->Presence);
			}
			else if (Item->Type == INCOMING)
			{
				return FText::FromString("Added you as a friend");
			}
			else if (Item->Type == OUTGOING)
			{
				return FText::FromString("Pending friend request");
			}
			else return FText::FromString("");
		}
		FriendEntryTypeDeprecated GetType() const
		{
			return Item->Type;
		}

		EVisibility PrivateChatButtonVisible() const
		{
			if (Item->Presence == TEXT("ONLINE") && Item->Type == FRIEND)
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
			if (Item->Presence == TEXT("ONLINE") && Item->Type == FRIEND)
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

#pragma endregion FRIENDS_SERVICE

void SLobby::OnIncomingNotification(const FAccelByteModelsNotificationMessage& MessageNotification)
{
	if (MessageNotification.Topic != TEXT("SHOOTER_GAME"))
	{
		return;
	}

	CloseOverlay(NotificationOverlay);
	TSharedPtr<SShooterConfirmationDialog> Dialog;
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
			SAssignNew(Dialog, SShooterConfirmationDialog).PlayerOwner(PlayerOwner)
			.MessageText(FText::FromString(FString::Printf(TEXT("Notification!\nFrom: %s\nMessage: %s"), *MessageNotification.From, *MessageNotification.Payload)))
			.ConfirmText(FText::FromString("CLOSE"))
			.OnConfirmClicked(FOnClicked::CreateLambda([&]()
			{
				CloseOverlay(NotificationOverlay);
				return FReply::Handled();
			}))
		];

	GEngine->GameViewport->AddViewportWidgetContent(NotificationOverlay.ToSharedRef());
	FSlateApplication::Get().SetKeyboardFocus(Dialog);
}

void SLobby::CloseOverlay(TSharedPtr<SOverlay> Overlay)
{
	if (Overlay.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(Overlay.ToSharedRef());
		Overlay.Reset();
	}
}

#undef LOCTEXT_NAMESPACE