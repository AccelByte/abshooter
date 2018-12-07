#include "ShooterGame.h"
#include "SLobby.h"
#include "SHeaderRow.h"
#include "ShooterStyle.h"
#include "ShooterGameLoadingScreen.h"
#include "ShooterGameInstance.h"
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"


#define LOCTEXT_NAMESPACE "ShooterGame.HUD.Menu"

void SLobby::Construct(const FArguments& InArgs)
{
	const FLobbyStyle* LobbyStyle = &FShooterStyle::Get().GetWidgetStyle<FLobbyStyle>("DefaultLobbyStyle");

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
						.HeightOverride(800)
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
								.FixedWidth(500)
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
				.VAlign(VAlign_Top)
				.AutoHeight()
				[
					SNew(SBox)
					.HeightOverride(500)
					.HAlign(HAlign_Fill)
					[
						SNew(STextBlock)
						.Text(FText::FromString(TEXT("YOUR PARTY")))
						.TextStyle(FShooterStyle::Get(), "ShooterGame.UserIDTextStyle")
					]
				]
				
				+ SVerticalBox::Slot()		//CHAT Area
				.VAlign(VAlign_Fill)
				.FillHeight(1.0f)
				[
					SNew(SBox)
					.HeightOverride(300.0f)
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

void SLobby::InputReceived()
{
	GEngine->AddOnScreenDebugMessage(1, 15, FColor::White, TEXT("Input received"));
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

void SLobby::AddFriend(FString UserID, FString DisplayName, FString Avatar)
{
    TSharedPtr<FFriendEntry> FriendEntry1 = MakeShareable(new FFriendEntry());
    FriendEntry1->UserId = UserID;
    FriendEntry1->Name = DisplayName;
    FriendEntry1->AvatarSmallUrl = Avatar;
    FriendEntry1->Presence = "Online";
    CompleteFriendList.Add(FriendEntry1);

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
	// ^^^^^^ Get online user

//	// If user want to chat with the user, do this
//	AddChatTab(true, TEXT("PartyA"), TEXT("UserA"));
//	AddChatTab(true, TEXT("PartyA"), TEXT("UserB"));
//	AddChatTab(true, TEXT("PartyA"), TEXT("UserC"));
//
//	// If user want to send message to another user, do this
//	SendChat(TEXT("UserA"), TEXT("Hello, I am Okay."));
//	SendChat(TEXT("UserB"), TEXT("Hello okay, are you okay?"));
//	SendChat(TEXT("UserC"), TEXT("Is UserA==okay?"));
//	SendChat(TEXT("UserB"), TEXT("Hello, I am Okay."));
//	SendChat(TEXT("UserA"), TEXT("Hello okay, are you okay?"));
//	SendChat(TEXT("UserC"), TEXT("Is UserA==okay?\t\tsdfsadfsadfsadfsdaf"));
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
    //AddChatTab(true, SelectedItem->UserId, SelectedItem->UserId);
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
	GEngine->AddOnScreenDebugMessage(1, .4f, FColor::White, Text.ToString());
}

TSharedRef<ITableRow> SLobby::MakeListViewWidget(TSharedPtr<FFriendEntry> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	class SFriendEntryWidget : public SMultiColumnTableRow< TSharedPtr<FFriendEntry> >
	{
	public:
		TSharedPtr<FSlateDynamicImageBrush> ThumbnailBrush;
		const FLobbyStyle* LobbyStyle = &FShooterStyle::Get().GetWidgetStyle<FLobbyStyle>("DefaultLobbyStyle");

		SLATE_BEGIN_ARGS(SFriendEntryWidget) {}
		SLATE_END_ARGS()

		TSharedPtr<FFriendEntry> Item;
        TWeakPtr<SLobby, ESPMode::NotThreadSafe> ParentClass;
        

		void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TSharedPtr<FFriendEntry> InItem, SLobby* Parent)
		{
			Item = InItem;
            ParentClass = TWeakPtr<SLobby, ESPMode::NotThreadSafe>(StaticCastSharedRef<SLobby>(Parent->AsShared()));

			// start download avatar
			//TSharedRef<IHttpRequest> ThumbRequest = FHttpModule::Get().CreateRequest();
			//ThumbRequest->SetVerb("GET");
			//ThumbRequest->SetURL(Item->AvatarSmallUrl);
			//ThumbRequest->OnProcessRequestComplete().BindRaw(this, &SFriendEntryWidget::OnThumbImageReceived);
			//ThumbRequest->ProcessRequest();
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
				+ SHorizontalBox::Slot()	//3.INVITATION BUTTON
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
						.Text(FText::FromString(TEXT("PRIVATE CHAT")))
						.TextStyle(&LobbyStyle->InviteButtonTextStyle)
					]
				]
			;
		}

		FReply OnInviteClicked()
		{   
            if (ParentClass.IsValid())
            {
                ParentClass.Pin()->AddChatTab(true, Item->UserId, Item->UserId);
            }
            
            return FReply::Handled();
		}

		void OnThumbImageReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			//if (bWasSuccessful && Response.IsValid())
			//{
			//	TArray<uint8> ImageData = Response->GetContent();
			//	//ThumbnailBrush = CreateBrush(Response->GetContentType() ,FName(*Request->GetURL()), ImageData);
			//}
		}

		TSharedPtr<FSlateDynamicImageBrush> CreateBrush(FString ContentType, FName ResourceName, TArray<uint8> ImageData)
		{
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
			ERGBFormat RgbFormat = ERGBFormat::RGBA;
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

		const FSlateBrush* GetProfileAvatar() const {
			if (ThumbnailBrush.IsValid())
			{
				return ThumbnailBrush.Get();				
			}
			else
			{
                return FShooterStyle::Get().GetBrush("ShooterGame.Speaker");
			}
		}

		FText GetName() const { return FText::FromString(Item->Name); }
		FText GetPresence() const { return FText::FromString(Item->Presence); }

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

void SLobby::AddChatTab(bool IsParty, FString PartyId, FString UserId)
{
	//Create Conversation Widget
	LobbyChatPages.Add
	(
		SNew(SChatPage)
		.ChatStat(TEXT("127.0.0.1"))
		.LobbyStyle(&FShooterStyle::Get().GetWidgetStyle<FLobbyStyle>("DefaultLobbyStyle"))
		.ChatPageIndex(LobbyChatPages.Num())
		.UserId(UserId)
		.OnTextComitted(this, &SLobby::SendChat)
		.OnSendButtonPressed(this, &SLobby::SendChat)
	);

	//Create Tab Button
	LobbyChatTabButtons.Add
	(
		SNew(SChatTabButton)
		.TabIndex(LobbyChatTabButtons.Num())
		.OnClicked(this, &SLobby::SelectTab)
		.LobbyStyle(&FShooterStyle::Get().GetWidgetStyle<FLobbyStyle>("DefaultLobbyStyle"))
		.UserId(UserId)
	);
	
	ChatPageSwitcher->AddSlot().AttachWidget(LobbyChatPages[LobbyChatPages.Num() - 1].ToSharedRef());
	ScrollBoxChatTabs->AddSlot().AttachWidget(LobbyChatTabButtons[LobbyChatTabButtons.Num() - 1].ToSharedRef());
	SelectTab(LobbyChatTabButtons.Num() - 1);
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

	GEngine->AddOnScreenDebugMessage(1, 1, FColor::White, TEXT("SelectedTabIndex") + FString::FromInt(TabIndex));
	UE_LOG(LogTemp, Log, TEXT("Selected Tab: %d"), TabIndex);
}

void SLobby::SendChat(FString UserId, FString Message)
{

	// handle lobby chat here
	UE_LOG(LogTemp, Log, TEXT("SLobby::SendChat"));
	for (int32 i = 0; i < LobbyChatPages.Num(); i++)
	{
		if (LobbyChatPages[i]->UserId.Equals(UserId))
		{
			//Get user's name and append it with this function
			LobbyChatPages[i]->AppendConversation(TEXT("MyDisplayName"), Message);
			break;
		}
	}
}

void SLobby::ReceiveChat(FString UserId, FString Message)
{

}

#pragma endregion CHAT

#undef LOCTEXT_NAMESPACE