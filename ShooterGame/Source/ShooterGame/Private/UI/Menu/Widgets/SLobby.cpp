#include "ShooterGame.h"
#include "SLobby.h"
#include "SHeaderRow.h"
#include "ShooterStyle.h"
#include "ShooterGameLoadingScreen.h"
#include "ShooterGameInstance.h"
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"
#include "SShooterConfirmationDialog.h"
#include "ShooterGameUserSettings.h"

// AccelByte
#include "Api/AccelByteLobbyApi.h"
#include "Api/AccelByteOauth2Api.h"

#define LOCTEXT_NAMESPACE "ShooterGame.HUD.Menu"

void SLobby::Construct(const FArguments& InArgs)
{
	const FLobbyStyle* LobbyStyle = &FShooterStyle::Get().GetWidgetStyle<FLobbyStyle>("DefaultLobbyStyle");

    //grab the user settings
    UShooterGameUserSettings* UserSettings = CastChecked<UShooterGameUserSettings>(GEngine->GetGameUserSettings());
    ScreenRes = UserSettings->GetScreenResolution();


    //FriendListCache = MakeShared<FriendCache>();
    AvatarListCache = MakeShared<ProfileCache, ESPMode::ThreadSafe>();
    DiplayNameListCache = MakeShared<ProfileCache, ESPMode::ThreadSafe>();

	PlayerOwner = InArgs._PlayerOwner;
	OwnerWidget = InArgs._OwnerWidget;
	bSearchingForFriends = false;
	StatusText = FText::GetEmpty();
	LastSearchTime = 0.0f;

#if PLATFORM_SWITCH
	MinTimeBetweenSearches = 6.0;
#else
	MinTimeBetweenSearches = 0.0;
#endif

    AccelByte::Api::Lobby::Get().SetPrivateMessageNotifDelegate(AccelByte::Api::Lobby::FPersonalChatNotif::CreateSP(this, &SLobby::OnReceivePrivateChat));
    AccelByte::Api::Lobby::Get().SetPartyChatNotifDelegate(AccelByte::Api::Lobby::FPartyChatNotif::CreateSP(this, &SLobby::OnReceivePartyChat));
    AccelByte::Api::Lobby::Get().SetUserPresenceNotifDelegate(AccelByte::Api::Lobby::FFriendStatusNotif::CreateSP(this, &SLobby::OnUserPresenceNotification));
    AccelByte::Api::Lobby::Get().SetInfoPartyResponseDelegate(AccelByte::Api::Lobby::FPartyInfoResponse::CreateSP(this, &SLobby::OnGetPartyInfoResponse));
    AccelByte::Api::Lobby::Get().SetPartyGetInvitedNotifDelegate(AccelByte::Api::Lobby::FPartyGetInvitedNotif::CreateSP(this, &SLobby::OnInvitedToParty));
    AccelByte::Api::Lobby::Get().SetPartyJoinNotifDelegate(AccelByte::Api::Lobby::FPartyJoinNotif::CreateSP(this, &SLobby::OnInvitedFriendJoinParty));

	ChildSlot
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SHorizontalBox)

			+SHorizontalBox::Slot()		//FriendSearchBar
			.HAlign(HAlign_Fill)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()	//2.1 INPUT FIELD
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Center)
					.Padding(0.0f, 10.0f)
					[
						SNew(SBox)
						[
							SNew(SEditableTextBox) //2.1.1 SEDITABLETEXTBOX
							.HintText(FText::FromString(TEXT("Search your friend")))
							.MinDesiredWidth(300.0f)
							.SelectAllTextWhenFocused(true)
							.OnTextChanged(this, &SLobby::OnTextSearchChanged)
							.Style(&LobbyStyle->SearchBarStyle)
						]
					]

				]
				+ SVerticalBox::Slot()	//FriendListView
				.AutoHeight()
				[
					SNew(SHorizontalBox)	//NonScrollBar
					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Fill)
					[
						SNew(SBox)
						.HAlign(HAlign_Fill)
						.HeightOverride(this, &SLobby::GetLobbyHeight)
						[
							SAssignNew(FriendListWidget, SListView<TSharedPtr<FFriendEntry>>)
							.ListItemsSource(&FriendList)
							.SelectionMode(ESelectionMode::Single)
							.OnGenerateRow(this, &SLobby::MakeListViewWidget)
							.OnSelectionChanged(this, &SLobby::EntrySelectionChanged)
							.ExternalScrollbar(
								FriendScrollBar
							)
							.ScrollbarVisibility(EVisibility::Visible)
							.HeaderRow(
								SNew(SHeaderRow)
								.Style(&LobbyStyle->HeaderRowStyle)
								+ SHeaderRow::Column("Friend")
								.HAlignCell(HAlign_Fill)
								.VAlignCell(VAlign_Fill)
								.FillWidth(1.0)
								.DefaultLabel(NSLOCTEXT("FriendList", "FriendColumn", "Friends"))
								.HAlignHeader(HAlign_Center)
								.VAlignHeader(VAlign_Center)
							)
						]
					]

					+ SHorizontalBox::Slot()	//Scroll player list
                    
					.AutoWidth()
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

			+ SHorizontalBox::Slot()	//PARTY Member & CHAT Area
			.FillWidth(1.0f)
			.HAlign(HAlign_Fill)
			.Padding(30.0f, 0.0f)
			[
				SNew(SVerticalBox)
				
				+ SVerticalBox::Slot()		//PARTY Members those invited
				.VAlign(VAlign_Fill)
				.FillHeight(1.0f)
				[
					//SNew(SBox)
					//.HeightOverride(500)
					//.HAlign(HAlign_Fill)
					//[
					//	SNew(STextBlock)
					//	.Text(FText::FromString(TEXT("YOUR PARTY")))
					//	.TextStyle(FShooterStyle::Get(), "ShooterGame.UserIDTextStyle")
					//]
					SAssignNew(PartyWidget, SParty)
					.LobbyStyle(LobbyStyle)
				]
				
				+ SVerticalBox::Slot()		//CHAT Area
				.VAlign(VAlign_Fill)
				.FillHeight(1.0f)
				[
					SNew(SBox)
					.HeightOverride(250.0f)
					.WidthOverride(600.0f)
					.VAlign(VAlign_Fill)
					.HAlign(HAlign_Fill)
					[
						SNew(SVerticalBox)

						+ SVerticalBox::Slot()	//CHAT TABs Area
						.AutoHeight()
						.HAlign(HAlign_Fill)
						[
							SNew(SHorizontalBox)	
							+ SHorizontalBox::Slot()	//CHAT TAB Button Scroll LEFT
							.AutoWidth()
							[
								SAssignNew(ButtonChatTabScrollLeft, SButton)
								.VAlign(VAlign_Fill)
								.OnClicked(this, &SLobby::OnChatTabScrollLeftClicked)
								[
									SNew(SImage)
									.Image(&LobbyStyle->ChatTabLeftButtonStyle)
								]
							]

							+ SHorizontalBox::Slot()	//CHAT TAB ScrollBar<Button>
							.FillWidth(1.0f)
							.HAlign(HAlign_Fill)
							[
								SAssignNew(ScrollBoxChatTabs, SScrollBox)
								.IsEnabled(true)
								.AllowOverscroll(EAllowOverscroll::No)
								.ConsumeMouseWheel(EConsumeMouseWheel::Always)
								.ScrollBarAlwaysVisible(false)
								.ScrollBarVisibility(EVisibility::Collapsed)
								.Orientation(EOrientation::Orient_Horizontal)
							]

							+ SHorizontalBox::Slot()	//CHAT TAB Button Scroll RIGHT
							.AutoWidth()
							[
								SAssignNew(ButtonChatTabScrollRight, SButton)
								.VAlign(VAlign_Fill)
								.OnClicked(this, &SLobby::OnChatTabScrollRightClicked)
								[
									SNew(SImage)
									.Image(&LobbyStyle->ChatTabRightButtonStyle)
								]
							]
						]
						
						+ SVerticalBox::Slot()	//CHAT CONV Area
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.FillHeight(1.0f)
						[
							SAssignNew(ChatPageSwitcher, SWidgetSwitcher)
						]
					]
				]

			]

		]
	;
}

FOptionalSize SLobby::GetLobbyHeight() const
{
    return FOptionalSize(ScreenRes.Y * 0.7);
}
int32 SLobby::GetLobbyWidth() const
{
    return ScreenRes.X * 0.8;
}


void SLobby::InputReceived()
{

}

void SLobby::OnGetPartyInfoResponse(const FAccelByteModelsInfoPartyResponse& PartyInfo)
{
    PartyWidget->ResetAll();

    FString LeaderDisplayName = CheckDisplayName(PartyInfo.LeaderId) ? GetDisplayName(PartyInfo.LeaderId) : PartyInfo.LeaderId;
    FSlateBrush* LeaderAvatar = CheckAvatar(PartyInfo.LeaderId) ? GetAvatar(PartyInfo.LeaderId).Get() : (FSlateBrush*)FShooterStyle::Get().GetBrush("ShooterGame.Speaker");

    PartyWidget->InsertLeader(PartyInfo.LeaderId, LeaderDisplayName, LeaderAvatar);
    for (FString MemberId : PartyInfo.Members)
    {
        if (MemberId != PartyInfo.LeaderId)
        {
            FString MemberDisplayName = CheckDisplayName(MemberId) ? GetDisplayName(MemberId) : MemberId;
            FSlateBrush* MemberAvatar = CheckAvatar(MemberId) ? GetAvatar(MemberId).Get() : (FSlateBrush*)FShooterStyle::Get().GetBrush("ShooterGame.Speaker");
            PartyWidget->InsertMember(MemberId, MemberDisplayName, MemberAvatar);
        }
    }
    PartyWidget->ButtonCreateParty->SetVisibility(EVisibility::Collapsed);
    // add chat tab
    CurrentPartyID = PartyInfo.PartyId;
    AddChatTab(TEXT(""), TEXT("My Party"), PartyInfo.PartyId);
}

void SLobby::OnInvitedFriendJoinParty(const FAccelByteModelsPartyJoinNotice& Notification)
{
    // update using OnGetPartyInfoResponse, so we have to trigger SendInfoPartyRequest
    // TODO optimize this
    AccelByte::Api::Lobby::Get().SendInfoPartyRequest();
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
            //[
            //	SNew(SImage)
            //	.Image(&LobbyStyle->PartyInvitationBackground)
            //]
        ]
        + SOverlay::Slot()
        [
            SNew(SShooterConfirmationDialog).PlayerOwner(PlayerOwner)
            .MessageText(FText::FromString(FString::Printf(TEXT("You're invited by %s to join a party."), *DisplayName)))
            .ConfirmText(FText::FromString("Accept"))
            .CancelText(FText::FromString("Reject"))
            .OnConfirmClicked(FOnClicked::CreateLambda([&, Notification]()
            {
            AccelByte::Api::Lobby::Get().SendLeavePartyRequest();
            CurrentPartyID = Notification.PartyId;
            AccelByte::Api::Lobby::Get().SendAcceptInvitationRequest(Notification.PartyId, Notification.InvitationToken);
            AccelByte::Api::Lobby::Get().SetInvitePartyJoinResponseDelegate(AccelByte::Api::Lobby::FPartyJoinResponse::CreateLambda([&](const FAccelByteModelsPartyJoinReponse& Response)
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

                        PartyWidget->InsertMember(MemberId, MemberDisplayName, MemberAvatar);
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
            AddChatTab(TEXT(""), TEXT("My Party"), Notification.PartyId);

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

void SLobby::OnUserPresenceNotification(const FAccelByteModelsUsersPresenceNotice& Response)
{
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
                    CompleteFriendList[i]->Presence = "Online";
                    break;
                }
            }
            RefreshFriendList();
            UpdateSearchStatus();
        }
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
                CompleteFriendList[i]->Presence = "Offline";
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
	bool bFinishSearch = false;

	// SOCIAL SERVICE API

	// foreach friends from social
	// finish obtain friends
	bFinishSearch = true;

	if (bFinishSearch)
	{
		OnFriendSearchFinished();
	}
}

void SLobby::InitializeFriends()
{
    bSearchingForFriends = true;
    CompleteFriendList.Reset();
    //LobbyChatTabButtons.Reset();
}

void SLobby::OnPartyCreated(const FAccelByteModelsCreatePartyResponse& Response)
{
    
}

void SLobby::SetCurrentUser(FString UserID, FString DisplayName, FString AvatarURL)
{
    CurrentUserID = UserID;
    CurrentUserDisplayName = DisplayName; 
    CurrentAvatarURL = AvatarURL;
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


};
void SLobby::AddFriend(FString UserID, FString DisplayName, FString Avatar)
{
    TSharedPtr<FFriendEntry> FriendEntry1 = MakeShareable(new FFriendEntry());
    FriendEntry1->UserId = UserID;
    FriendEntry1->Name = DisplayName;
    FriendEntry1->AvatarSmallUrl = Avatar;
    FriendEntry1->Presence = "Online";
    CompleteFriendList.Add(FriendEntry1);


    if (!AvatarListCache->Contains(UserID))
    {
        //get avatar from platform service (User profile)
        UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Start getting public user profile from platform service..."));
        AccelByte::Api::UserProfile::GetPublicUserProfileInfo(UserID, AccelByte::Api::UserProfile::FGetPublicUserProfileInfoSuccess::CreateLambda([this](const FAccelByteModelsPublicUserProfileInfo& UserProfileInfo) {
            UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Get User Public Profile: %s - > %s"), *UserProfileInfo.UserId, *UserProfileInfo.AvatarSmallUrl);
            AvatarListCache->Add(UserProfileInfo.UserId, UserProfileInfo.AvatarSmallUrl);

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

    if (!DiplayNameListCache->Contains(UserID))
    {
        UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Start getting public user profile from IAM service..."));
        AccelByte::Api::Oauth2::GetPublicUserInfo(UserID, AccelByte::Api::Oauth2::FGetPublicUserInfoDelegate::CreateLambda([this](const FAccelByteModelsOauth2UserInfo& UserInfo) {
            UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Get User Public Profile: %s - > %s"), *UserInfo.UserId, *UserInfo.DisplayName);
            DiplayNameListCache->Add(UserInfo.UserId, UserInfo.DisplayName);
        }),
            AccelByte::FErrorHandler::CreateLambda([&](int32 Code, FString Message) {
            UE_LOG(LogTemp, Log, TEXT("[Accelbyte SDK] Get IAM User Public Profile Error"));
        }));
    }



}

void SLobby::RefreshFriendList()
{
    FriendList = CompleteFriendList;
    bSearchingForFriends = false;
    OnFriendSearchFinished();
}

FText SLobby::GetBottomText() const
{
	return StatusText;
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

/** Starts searching for servers */
void SLobby::BeginFriendSearch()
{
	bSearchingForFriends = true;
	CompleteFriendList.Reset();
	LobbyChatTabButtons.Reset();
}

/** Called when server search is finished */
void SLobby::OnFriendSearchFinished()
{
	bSearchingForFriends = false;

	UpdateFriendList();
}

void SLobby::UpdateFriendList()
{
	int32 SelectedItemIndex = FriendList.IndexOfByKey(SelectedItem);

	FriendListWidget->RequestListRefresh();
	if (FriendList.Num() > 0)
	{
		FriendListWidget->UpdateSelectionSet();
		FriendListWidget->SetSelection(FriendList[SelectedItemIndex > -1 ? SelectedItemIndex : 0], ESelectInfo::OnNavigation);
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
	return FReply::Handled().SetUserFocus(FriendListWidget.ToSharedRef(), EFocusCause::SetDirectly);
}

void SLobby::EntrySelectionChanged(TSharedPtr<FFriendEntry> InItem, ESelectInfo::Type SelectInfo)
{
    if (InItem.IsValid())
    {
        SelectedItem = InItem;
    }
}

void SLobby::OnListItemDoubleClicked()
{    

}

void SLobby::MoveSelection(int32 MoveBy)
{
	int32 SelectedItemIndex = FriendList.IndexOfByKey(SelectedItem);

	if (SelectedItemIndex + MoveBy > -1 && SelectedItemIndex + MoveBy < FriendList.Num())
	{
		FriendListWidget->SetSelection(FriendList[SelectedItemIndex + MoveBy]);
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
	//hit space bar to search for servers again / refresh the list, only when not searching already
	else if (Key == EKeys::SpaceBar || Key == EKeys::Gamepad_FaceButton_Left)
	{
		BeginFriendSearch();
	}
	return Result;
}

void SLobby::OnTextSearchChanged(const FText& Text)
{
	FriendList.Reset();
	if (Text.ToString()==TEXT(""))
	{
		FriendList = CompleteFriendList;
	}
	else
	{
		for (int i = 0;  i < CompleteFriendList.Num(); i ++)
		{
			if (CompleteFriendList[i]->Name.Contains(Text.ToString(), ESearchCase::IgnoreCase))
			{
				FriendList.Add(CompleteFriendList[i]);
			}
		}
	}
	FriendListWidget->RequestListRefresh();	
}

void SLobby::OnThumbImageReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FString UserID)
{
    if (bWasSuccessful && Response.IsValid())
    {
        TArray<uint8> ImageData = Response->GetContent();
        ThumbnailBrushCache.Add(UserID, CreateBrush(Response->GetContentType(), FName(*Request->GetURL()), ImageData));        
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
				.Padding(20.0, 0, 20.0, 0)
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
				+ SHorizontalBox::Slot()	//3.Private Chat
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(0, 0, 25, 0)
				[
					SNew(SButton)
					.Visibility(this, &SFriendEntryWidget::PrivateChatButtonVisible)
					.OnClicked(this, &SFriendEntryWidget::OnPrivateChatClicked)
					.ButtonStyle(&LobbyStyle->InviteButtonStyle)
					.Content()
					[
						SNew(STextBlock)
						.Text(FText::FromString(TEXT("CHAT")))
						.TextStyle(&LobbyStyle->InviteButtonTextStyle)
					]
				]
                + SHorizontalBox::Slot()	//3.Invite Party TODO
                    .AutoWidth()
                    .VAlign(VAlign_Center)
                    .Padding(0, 0, 25, 0)
                    [
                        SNew(SButton)
                        .Visibility(this, &SFriendEntryWidget::InviteButtonVisible)
                        .OnClicked(this, &SFriendEntryWidget::OnInviteClicked)
                        .ButtonStyle(&LobbyStyle->InviteButtonStyle)
                        .Content()
                        [
                            SNew(STextBlock)
                            .Text(FText::FromString(TEXT("INVITE PARTY")))
                            .TextStyle(&LobbyStyle->InviteButtonTextStyle)
                        ]
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

                ParentClass.Pin()->AddChatTab(Item->UserId, DisplayName, TEXT(""));
            }
            
            return FReply::Handled();
		}

        FReply OnInviteClicked()
        {
            if (ParentClass.IsValid())
            {
                ParentClass.Pin()->InviteToParty(Item->UserId);
            }
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
            if (Item->Presence == TEXT("Online"))
            {
                return EVisibility::Visible;
            }
            else
            {
                return EVisibility::Hidden;
            }
        }

		EVisibility InviteButtonVisible() const
		{
			if (Item->Presence == TEXT("Online"))
			{
				return EVisibility::Visible;
			}
			else
			{
				return EVisibility::Hidden;
			}
		}
	};
	return SNew(SFriendEntryWidget, OwnerTable, Item, this);
}

#pragma region CHAT

void SLobby::AddChatTab(FString UserId, FString DisplayName, FString PartyId)
{
    // find existing
    for (int i = 0; i < LobbyChatPages.Num(); i++)
    {
        if (LobbyChatPages[i]->UserId == UserId || LobbyChatPages[i]->PartyId == PartyId)
        {
            // chat tab already existed;
            return;
        }
    }

    if (!UserId.IsEmpty())
    {
        // personal chat        
        LobbyChatPages.Add
        (
            SNew(SChatPage)
            .DisplayName(DisplayName)
            .LobbyStyle(&FShooterStyle::Get().GetWidgetStyle<FLobbyStyle>("DefaultLobbyStyle"))
            .ChatPageIndex(LobbyChatPages.Num())
            .UserId(UserId)
            .PartyId(PartyId)
            .OnTextComitted(this, &SLobby::SendPrivateChat)
            .OnSendButtonPressed(this, &SLobby::SendPrivateChat)
        );

        //Create Tab Button
        LobbyChatTabButtons.Add
        (
            SNew(SChatTabButton)
            .TabIndex(LobbyChatTabButtons.Num())
            .OnClicked(this, &SLobby::SelectTab)
            .LobbyStyle(&FShooterStyle::Get().GetWidgetStyle<FLobbyStyle>("DefaultLobbyStyle"))
            .UserId(UserId)
            .PartyId(PartyId)
            .DisplayName(DisplayName)
        );
    }
    else if (!PartyId.IsEmpty())
    {
        // party chat        
        LobbyChatPages.Add
        (
            SNew(SChatPage)
            .DisplayName(DisplayName)
            .LobbyStyle(&FShooterStyle::Get().GetWidgetStyle<FLobbyStyle>("DefaultLobbyStyle"))
            .ChatPageIndex(LobbyChatPages.Num())
            .UserId(UserId)
            .PartyId(PartyId)
            .OnTextComitted(this, &SLobby::SendPartyChat)
            .OnSendButtonPressed(this, &SLobby::SendPartyChat)
        );

        //Create Tab Button
        LobbyChatTabButtons.Add
        (
            SNew(SChatTabButton)
            .TabIndex(LobbyChatTabButtons.Num())
            .OnClicked(this, &SLobby::SelectTab)
            .LobbyStyle(&FShooterStyle::Get().GetWidgetStyle<FLobbyStyle>("DefaultLobbyStyle"))
            .UserId(UserId)
            .PartyId(PartyId)
            .DisplayName(DisplayName)
        );
    }

	
	ChatPageSwitcher->AddSlot().AttachWidget(LobbyChatPages[LobbyChatPages.Num() - 1].ToSharedRef());
	ScrollBoxChatTabs->AddSlot().AttachWidget(LobbyChatTabButtons[LobbyChatTabButtons.Num() - 1].ToSharedRef());
	SelectTab(LobbyChatTabButtons.Num() - 1);
}

void SLobby::InviteToParty(FString UserId)
{
	AccelByte::Api::Lobby::Get().SendInviteToPartyRequest(UserId);
}

TSharedPtr<SWidget> SLobby::GetActiveChatTabWidget()
{
	return ScrollBoxChatTabs->GetChildren()->GetChildAt(ActiveTabIndex);
}

FReply SLobby::OnChatTabScrollLeftClicked()
{
	if (ActiveTabIndex > 0)
	{
		SelectTab(ActiveTabIndex - 1);
		ScrollBoxChatTabs->ScrollDescendantIntoView(LobbyChatTabButtons[ActiveTabIndex], true);
	}
	return FReply::Handled();
}

FReply SLobby::OnChatTabScrollRightClicked()
{
	if (ActiveTabIndex < LobbyChatTabButtons.Num() - 1)
	{
		SelectTab(ActiveTabIndex + 1);
		ScrollBoxChatTabs->ScrollDescendantIntoView(LobbyChatTabButtons[ActiveTabIndex], true);
	}
	return FReply::Handled();
}

void SLobby::SelectTab(int32 TabIndex)
{
	ActiveTabIndex = TabIndex;

	for (auto a: LobbyChatTabButtons)
	{
		if (a->TabIndex == TabIndex)
		{
			a->Selected();
		}
		else
		{
			a->NotSelected();
		}
	}

	ChatPageSwitcher->SetActiveWidgetIndex(TabIndex);

	if (TabIndex == 0)
	{
		ButtonChatTabScrollLeft->SetEnabled(false);
	}
	else
	{
		ButtonChatTabScrollLeft->SetEnabled(true);
	}
	if (TabIndex == LobbyChatTabButtons.Num() - 1)
	{
		ButtonChatTabScrollRight->SetEnabled(false);
	}
	else
	{
		ButtonChatTabScrollRight->SetEnabled(true);
	}
	if (LobbyChatTabButtons.Num() == 1)
	{
		ButtonChatTabScrollLeft->SetEnabled(false);
		ButtonChatTabScrollRight->SetEnabled(false);
	}
	UE_LOG(LogTemp, Log, TEXT("Selected Tab: %d"), TabIndex);
}

void SLobby::SendPrivateChat(FString UserId, FString Message)
{
	// send from this user to target user ( UserId)
    AccelByte::Api::Lobby::Get().SendPrivateMessage(UserId, Message);

    // append to chat box UI
	for (int32 i = 0; i < LobbyChatPages.Num(); i++)
	{
		if (LobbyChatPages[i]->UserId.Equals(UserId))
		{
			//My Dislpay Name
			LobbyChatPages[i]->AppendConversation(CurrentUserDisplayName, Message);
			return;
		}
	}
}
void SLobby::SendPartyChat(FString PartyId, FString Message)
{
    // send from this user to target user ( UserId)
    AccelByte::Api::Lobby::Get().SendPartyMessage(Message);

    // append to chat box UI
    for (int32 i = 0; i < LobbyChatPages.Num(); i++)
    {
        if (LobbyChatPages[i]->PartyId.Equals(PartyId))
        {
            //My Dislpay Name
            LobbyChatPages[i]->AppendConversation(CurrentUserDisplayName, Message);
            return;
        }
    }
}

void SLobby::OnReceivePrivateChat(const FAccelByteModelsPersonalMessageNotice& Response)
{
    // append to chat box UI
    for (int32 i = 0; i < LobbyChatPages.Num(); i++)
    {
        if (LobbyChatPages[i]->UserId.Equals(Response.From))
        {
            //Get user's name and append it with this function

            // partner display name
            LobbyChatPages[i]->AppendConversation(LobbyChatPages[i]->DisplayName, Response.Payload);
            return;
        }
    }
    int32 iLastNum = LobbyChatPages.Num();

    //no chat tab, create new chat
    FString DisplayName = CheckDisplayName(Response.From) ? GetDisplayName(Response.From) : Response.From;
    AddChatTab(Response.From, DisplayName, TEXT(""));
    LobbyChatPages[iLastNum]->AppendConversation(DisplayName, Response.Payload);
    

}

void SLobby::OnReceivePartyChat(const FAccelByteModelsPartyMessageNotice& Response)
{
    // append to chat box UI
    FString DisplayName = CheckDisplayName(Response.From) ? GetDisplayName(Response.From) : Response.From;
    for (int32 i = 0; i < LobbyChatPages.Num(); i++)
    {
        if (LobbyChatPages[i]->PartyId.Equals(CurrentPartyID))
        {
            //Get user's name and append it with this function

            // partner display name
            LobbyChatPages[i]->AppendConversation(DisplayName, Response.Payload);
            return;
        }
    }
    int32 iLastNum = LobbyChatPages.Num();

    //no chat tab, create new chat
    
    AddChatTab(TEXT(""), TEXT("My Party"), CurrentPartyID);
    LobbyChatPages[iLastNum]->AppendConversation(DisplayName, Response.Payload);
}

#pragma endregion CHAT

#undef LOCTEXT_NAMESPACE