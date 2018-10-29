#include "ShooterGame.h"
#include "SLobbyFriendList.h"
#include "SHeaderRow.h"
#include "ShooterStyle.h"
#include "ShooterGameLoadingScreen.h"
#include "ShooterGameInstance.h"
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"


#define LOCTEXT_NAMESPACE "ShooterGame.HUD.Menu"

void SLobbyFriendList::Construct(const FArguments& InArgs)
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

	FriendScrollBar =
		SNew(SScrollBar)
		.IsEnabled(true)
		.AlwaysShowScrollbar(true)
		.Thickness(FVector2D(12.0f, 12.0f))
		.Orientation(EOrientation::Orient_Vertical)
		.Visibility(EVisibility::Visible)
		.Style(&LobbyStyle->ScrollBarStyle)
	;

	ChildSlot
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()	//PartyMember
			.AutoWidth()
			.Padding(30.0f, 0.0f)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("YOUR PARTY")))
				.TextStyle(FShooterStyle::Get(), "ShooterGame.UserIDTextStyle")
			]
			+SHorizontalBox::Slot()		//FriendBar
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
							.OnTextChanged(this, &SLobbyFriendList::OnTextSearchChanged)
							.Style(&LobbyStyle->SearchBarStyle)
						]
					]
				]
				+ SVerticalBox::Slot()	//Friend list
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
							.OnGenerateRow(this, &SLobbyFriendList::MakeListViewWidget)
							.OnSelectionChanged(this, &SLobbyFriendList::EntrySelectionChanged)
							.ExternalScrollbar(
								FriendScrollBar
							)
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
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SBox)
						.HAlign(HAlign_Right)
						[
							SAssignNew(FriendScrollBar, SScrollBar)
						]
					]
				]
			]

		]
	;
}

void SLobbyFriendList::InputReceived()
{
	GEngine->AddOnScreenDebugMessage(1, 15, FColor::White, TEXT("Input received"));
}

/** Updates current search status */
void SLobbyFriendList::UpdateSearchStatus()
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

FText SLobbyFriendList::GetBottomText() const
{
	return StatusText;
}

/**
 * Ticks this widget.  Override in derived classes, but always call the parent implementation.
 *
 * @param  InCurrentTime  Current absolute real time
 * @param  InDeltaTime  Real time passed since last tick
 */
void SLobbyFriendList::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if (bSearchingForFriends)
	{
		UpdateSearchStatus();
	}
}

/** Starts searching for servers */
void SLobbyFriendList::BeginFriendSearch()
{
	bSearchingForFriends = true;

	CompleteFriendList.Reset();
	// SOCIAL SERVICE API
	TSharedPtr<FFriendEntry> FriendEntry1 = MakeShareable(new FFriendEntry());
	FriendEntry1->UserId = "001";
	FriendEntry1->Name = "Jonathan Eka Sulistya Putra a.k.a. Alloynathan 01234567890123456789";
	FriendEntry1->Presence = "Online";
	FriendEntry1->AvatarSmallUrl = "https://s3-us-west-2.amazonaws.com/justice-platform-service/avatar.jpg";
	TSharedPtr<FFriendEntry> FriendEntry2 = MakeShareable(new FFriendEntry());
	FriendEntry2->UserId = "002";
	FriendEntry2->Name = "Windio a.k.a. Winfroz";
	FriendEntry2->Presence = "Offline";
	FriendEntry2->AvatarSmallUrl = "https://emoji.slack-edge.com/T3WDKH0L8/p0/27ea357ecaf8ff9f.png";
	TSharedPtr<FFriendEntry> FriendEntry3 = MakeShareable(new FFriendEntry());
	FriendEntry3->UserId = "003";
	FriendEntry3->Name = "Luthfan Nur Ubai a.k.a. DHashSlingingSlicer";
	FriendEntry3->Presence = "In-game";
	FriendEntry3->AvatarSmallUrl = "https://vignette.wikia.nocookie.net/spongebob/images/4/47/Hash.png";
	TSharedPtr<FFriendEntry> FriendEntry4 = MakeShareable(new FFriendEntry());
	FriendEntry4->UserId = "004";
	FriendEntry4->Name = "Alan a.k.a. Kelerchian";
	FriendEntry4->Presence = "Online";
	FriendEntry4->AvatarSmallUrl = "https://www.w3.org/People/mimasa/test/imgformat/img/w3c_home.bmp";
	TSharedPtr<FFriendEntry> FriendEntry5 = MakeShareable(new FFriendEntry());
	FriendEntry5->UserId = "005";
	FriendEntry5->Name = "Hendra a.k.a. Sapidol2002";
	FriendEntry5->Presence = "Idle";
	FriendEntry5->AvatarSmallUrl = "https://rimworldwiki.com/images/8/84/Cow.png";
	TSharedPtr<FFriendEntry> FriendEntry6 = MakeShareable(new FFriendEntry());
	FriendEntry6->UserId = "005";
	FriendEntry6->Name = "Hendra a.k.a. Sapidol2002";
	FriendEntry6->Presence = "Idle";
	FriendEntry6->AvatarSmallUrl = "https://rimworldwiki.com/images/8/84/Cow.png";
	TSharedPtr<FFriendEntry> FriendEntry7 = MakeShareable(new FFriendEntry());
	FriendEntry7->UserId = "005";
	FriendEntry7->Name = "Hendra a.k.a. Sapidol2002";
	FriendEntry7->Presence = "Idle";
	FriendEntry7->AvatarSmallUrl = "https://rimworldwiki.com/images/8/84/Cow.png";
	TSharedPtr<FFriendEntry> FriendEntry8 = MakeShareable(new FFriendEntry());
	FriendEntry8->UserId = "005";
	FriendEntry8->Name = "Hendra a.k.a. Sapidol2002";
	FriendEntry8->Presence = "Idle";
	FriendEntry8->AvatarSmallUrl = "https://rimworldwiki.com/images/8/84/Cow.png";
	TSharedPtr<FFriendEntry> FriendEntry9 = MakeShareable(new FFriendEntry());
	FriendEntry9->UserId = "005";
	FriendEntry9->Name = "Hendra a.k.a. Sapidol2002";
	FriendEntry9->Presence = "Idle";
	FriendEntry9->AvatarSmallUrl = "https://rimworldwiki.com/images/8/84/Cow.png";
	TSharedPtr<FFriendEntry> FriendEntry10 = MakeShareable(new FFriendEntry());
	FriendEntry10->UserId = "005";
	FriendEntry10->Name = "Hendra a.k.a. Sapidol2002";
	FriendEntry10->Presence = "Idle";
	FriendEntry10->AvatarSmallUrl = "https://rimworldwiki.com/images/8/84/Cow.png";
	TSharedPtr<FFriendEntry> FriendEntry11 = MakeShareable(new FFriendEntry());
	FriendEntry11->UserId = "005";
	FriendEntry11->Name = "Hendra a.k.a. Sapidol2002";
	FriendEntry11->Presence = "Idle";
	FriendEntry11->AvatarSmallUrl = "https://rimworldwiki.com/images/8/84/Cow.png";
	TSharedPtr<FFriendEntry> FriendEntry12 = MakeShareable(new FFriendEntry());
	FriendEntry12->UserId = "005";
	FriendEntry12->Name = "Hendra a.k.a. Sapidol2002";
	FriendEntry12->Presence = "Idle";
	FriendEntry12->AvatarSmallUrl = "https://rimworldwiki.com/images/8/84/Cow.png";
	CompleteFriendList.Add(FriendEntry1);
	CompleteFriendList.Add(FriendEntry2);
	CompleteFriendList.Add(FriendEntry3);
	CompleteFriendList.Add(FriendEntry4);
	CompleteFriendList.Add(FriendEntry5);
	CompleteFriendList.Add(FriendEntry6);
	CompleteFriendList.Add(FriendEntry7);
	CompleteFriendList.Add(FriendEntry8);
	CompleteFriendList.Add(FriendEntry9);
	CompleteFriendList.Add(FriendEntry10);
	CompleteFriendList.Add(FriendEntry11);
	CompleteFriendList.Add(FriendEntry12);
	FriendList = CompleteFriendList;
		bSearchingForFriends = false;

	OnFriendSearchFinished();
}

/** Called when server search is finished */
void SLobbyFriendList::OnFriendSearchFinished()
{
	bSearchingForFriends = false;

	UpdateFriendList();
}

void SLobbyFriendList::UpdateFriendList()
{
	int32 SelectedItemIndex = FriendList.IndexOfByKey(SelectedItem);

	FriendListWidget->RequestListRefresh();
	if (FriendList.Num() > 0)
	{
		FriendListWidget->UpdateSelectionSet();
		FriendListWidget->SetSelection(FriendList[SelectedItemIndex > -1 ? SelectedItemIndex : 0], ESelectInfo::OnNavigation);
	}

}

void SLobbyFriendList::OnFocusLost(const FFocusEvent& InFocusEvent)
{
	if (InFocusEvent.GetCause() != EFocusCause::SetDirectly)
	{
		FSlateApplication::Get().SetKeyboardFocus(SharedThis(this));
	}
}

FReply SLobbyFriendList::OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent)
{
	return FReply::Handled().SetUserFocus(FriendListWidget.ToSharedRef(), EFocusCause::SetDirectly);
}

void SLobbyFriendList::EntrySelectionChanged(TSharedPtr<FFriendEntry> InItem, ESelectInfo::Type SelectInfo)
{
	SelectedItem = InItem;
}

void SLobbyFriendList::MoveSelection(int32 MoveBy)
{
	int32 SelectedItemIndex = FriendList.IndexOfByKey(SelectedItem);

	if (SelectedItemIndex + MoveBy > -1 && SelectedItemIndex + MoveBy < FriendList.Num())
	{
		FriendListWidget->SetSelection(FriendList[SelectedItemIndex + MoveBy]);
	}
}

FReply SLobbyFriendList::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
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

void SLobbyFriendList::OnTextSearchChanged(const FText& Text)
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

TSharedRef<ITableRow> SLobbyFriendList::MakeListViewWidget(TSharedPtr<FFriendEntry> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	class SFriendEntryWidget : public SMultiColumnTableRow< TSharedPtr<FFriendEntry> >
	{
	public:
		TSharedPtr<FSlateDynamicImageBrush> ThumbnailBrush;
		const FLobbyStyle* LobbyStyle = &FShooterStyle::Get().GetWidgetStyle<FLobbyStyle>("DefaultLobbyStyle");

		SLATE_BEGIN_ARGS(SFriendEntryWidget) {}
		SLATE_END_ARGS()

		TSharedPtr<FFriendEntry> Item;

		void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TSharedPtr<FFriendEntry> InItem)
		{
			Item = InItem;

			// start download avatar
			TSharedRef<IHttpRequest> ThumbRequest = FHttpModule::Get().CreateRequest();
			ThumbRequest->SetVerb("GET");
			ThumbRequest->SetURL(Item->AvatarSmallUrl);
			ThumbRequest->OnProcessRequestComplete().BindRaw(this, &SFriendEntryWidget::OnThumbImageReceived);
			ThumbRequest->ProcessRequest();
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
						.Text(FText::FromString(TEXT("INVITE")))
						.TextStyle(&LobbyStyle->InviteButtonTextStyle)
					]
				]
			;
		}

		FReply OnInviteClicked()
		{
			GEngine->AddOnScreenDebugMessage(1, .4f, FColor::White, TEXT("Invited!"));
			return FReply::Handled();
		}

		void OnThumbImageReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			if (bWasSuccessful && Response.IsValid())
			{
				TArray<uint8> ImageData = Response->GetContent();
				ThumbnailBrush = CreateBrush(Response->GetContentType() ,FName(*Request->GetURL()), ImageData);
			}
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
				GEngine->AddOnScreenDebugMessage(1, 15, FColor::White, TEXT("Thumbnail: valid"));
			}
			else
			{
				return new FSlateImageBrush(FPaths::ProjectContentDir() / "Slate/Images/SoundCue_SpeakerIcon.png", FVector2D(144, 144));
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
	return SNew(SFriendEntryWidget, OwnerTable, Item);
}

#undef LOCTEXT_NAMESPACE