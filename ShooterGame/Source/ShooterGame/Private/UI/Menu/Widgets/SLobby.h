#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "ShooterGame.h"
#include "SShooterMenuWidget.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Framework/Text/RichTextLayoutMarshaller.h"
#include "Framework/Text/RichTextMarkupProcessing.h"
#include "Framework/Text/IRichTextMarkupParser.h"
#include "Framework/Text/IRichTextMarkupWriter.h"
#include "LobbyStyle.h"
#include "Models/AccelByteLobbyModels.h"
#include "Api/AccelByteUserAuthenticationApi.h"
#include "Api/AccelByteUserManagementApi.h"
#include "Api/AccelByteUserProfileApi.h"
#include "Api/AccelByteOauth2Api.h"
#include "Api/AccelByteLobbyApi.h"

struct FFriendEntry
{
	FString UserId;
	FString Name;
	FString Presence; //ONLINE, INGAME, IDLE, OFFLINE
	FString AvatarSmallUrl;
};

DECLARE_DELEGATE_OneParam(FOnClickedChatTabButton, int32);

class SChatTabButton : public SButton
{
public:
	SLATE_BEGIN_ARGS(SChatTabButton)
	{}
	SLATE_DEFAULT_SLOT(FArguments, Content)
		SLATE_ARGUMENT(int32, TabIndex)
		SLATE_ARGUMENT(FString, UserId)
        SLATE_ARGUMENT(FString, PartyId)
        SLATE_ARGUMENT(FString, DisplayName)
		SLATE_STYLE_ARGUMENT(FLobbyStyle, LobbyStyle)
		SLATE_EVENT(FOnClickedChatTabButton, OnClicked)

		SLATE_END_ARGS()

	int32 TabIndex = 0;
	FString UserId = TEXT("");
    FString PartyId = TEXT("");
    FString DisplayName = TEXT("");
	FOnClickedChatTabButton OnChatTabClicked;
	FTextBlockStyle ActiveTextStyle;
	FTextBlockStyle PassiveTextStyle;
	TSharedPtr<FTextBlockStyle> CurrentTextStyle = MakeShareable(new FTextBlockStyle());
	TSharedPtr<STextBlock> TextWidget;

	void Construct(const FArguments& InArgs)
	{		
		OnChatTabClicked = InArgs._OnClicked;
		TabIndex = InArgs._TabIndex;
		ActiveTextStyle = (InArgs._LobbyStyle)->ChatTabTextStyle;
		PassiveTextStyle = (InArgs._LobbyStyle)->ChatTabTextDisabledStyle;
		UserId = InArgs._UserId;
        PartyId = InArgs._PartyId;
        DisplayName = InArgs._DisplayName;

		SButton::Construct(
			SButton::FArguments()
			.ButtonStyle(&(InArgs._LobbyStyle)->ChatTabButtonStyle)
			.OnClicked(this, &SChatTabButton::InternalOnClicked)
			.IsEnabled(true)
			[
				SAssignNew(TextWidget, STextBlock)
				.TextStyle(&ActiveTextStyle)
				.Text(FText::FromString(DisplayName))
			]
		);
	}

	void Selected() 
	{
		UE_LOG(LogTemp, Log, TEXT("Button %s is selected"), *UserId);
		this->SetEnabled(false);
		TextWidget->SetTextStyle(&PassiveTextStyle);
	};

	void NotSelected()
	{
		UE_LOG(LogTemp, Log, TEXT("Button %s is deselected"), *UserId);
		this->SetEnabled(true);
		TextWidget->SetTextStyle(&ActiveTextStyle);
	};

	FReply InternalOnClicked()
	{
		OnChatTabClicked.ExecuteIfBound(TabIndex);
		return FReply::Handled();
	}
	
};

DECLARE_DELEGATE_TwoParams(FOnTextCommited, FString, FString);
DECLARE_DELEGATE_TwoParams(FOnSendButtonPressed, FString, FString);

class SChatPage : public SVerticalBox 
{
public:
	SLATE_BEGIN_ARGS(SChatPage)
	{}
	SLATE_DEFAULT_SLOT(FArguments, Content)
		SLATE_ARGUMENT(FString, UserId)
        SLATE_ARGUMENT(FString, PartyId)
        SLATE_ARGUMENT(FString, DisplayName)
		SLATE_ARGUMENT(int32, ChatPageIndex)
		SLATE_EVENT(FOnTextCommited, OnTextComitted)
		SLATE_EVENT(FOnSendButtonPressed, OnSendButtonPressed)
		SLATE_STYLE_ARGUMENT(FLobbyStyle, LobbyStyle)
	SLATE_END_ARGS()

	TSharedPtr<SScrollBox> ConversationScrollBox;
	FTextBlockStyle ConversationTextStyle;
	int32 ChatPageIndex;
	FString UserId;
    FString PartyId;
    FString DisplayName;
	FOnTextCommited OnTextCommited;
	FOnSendButtonPressed OnSendButtonPressed;
	TSharedPtr<SEditableTextBox> InputTextBox;

	void Construct(const FArguments& InArgs)
	{
		ChatPageIndex = InArgs._ChatPageIndex;
		UserId = InArgs._UserId;
        PartyId = InArgs._PartyId;
        DisplayName = InArgs._DisplayName;
		ConversationTextStyle = InArgs._LobbyStyle->ConversationTextStyle;
		OnTextCommited = InArgs._OnTextComitted;
		OnSendButtonPressed = InArgs._OnSendButtonPressed;

		SVerticalBox::Construct(
			SVerticalBox::FArguments()		
			+ SVerticalBox::Slot()	//ChatScrollBox conversation
			.FillHeight(1.0f)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(ConversationScrollBox, SScrollBox)
				.Style(&(InArgs._LobbyStyle)->ConversationScrollBoxStyle)
				.Orientation(EOrientation::Orient_Vertical)
				.ScrollBarAlwaysVisible(true)
				.ScrollBarStyle(&(InArgs._LobbyStyle)->ConversationScrollBarStyle)
			]

			+ SVerticalBox::Slot()	//ChatInputArea
			.AutoHeight()
			[
				SNew(SHorizontalBox)

				+ SHorizontalBox::Slot()	//ChatInput
				.FillWidth(1.0f)
				[
					SNew(SOverlay)

					+ SOverlay::Slot()		//ChatInput TypeBackGround
					[
						SNew(SImage)
						.Image(&InArgs._LobbyStyle->ConversationInputBackgroundBrush)
					]

					+ SOverlay::Slot()		//ChatInput Input
					.VAlign(VAlign_Center)
					[
						SAssignNew(InputTextBox, SEditableTextBox)
						.Style(&InArgs._LobbyStyle->ConversationInputTextStyle)
						.OnTextCommitted(this, &SChatPage::OnEditableTextBoxCommit)
						.ClearKeyboardFocusOnCommit(false)
					]
				]

				+ SHorizontalBox::Slot()	//SendButton
				.AutoWidth()
				[
					SNew(SButton)
					.ButtonStyle(&InArgs._LobbyStyle->ConversationInputSendButtonStyle)
					.OnClicked(this, &SChatPage::OnButtonPressed)
				]

			]
		);
	}

	void AppendConversation(FString UserName, FString Message)
	{
		TSharedPtr<SMultiLineEditableText> Text;
		FString FormatText = FString::Printf(TEXT("[%s] : %s"), *UserName, *Message);
		ConversationScrollBox->AddSlot()
			.VAlign(VAlign_Top)
			.AttachWidget
			(
				SAssignNew (Text, SMultiLineEditableText)
				.Justification(ETextJustify::Left)
				.TextStyle(&ConversationTextStyle)
				.Text(FText::FromString(FormatText))
				.AutoWrapText(true)
			);
		ConversationScrollBox->ScrollDescendantIntoView(Text);
	}

	void ResetConversation()
	{

	}

	void OnEditableTextBoxCommit(const FText& Text, ETextCommit::Type Type)
	{
		if (Type == ETextCommit::Type::OnEnter)
		{
			OnTextCommited.ExecuteIfBound(!this->UserId.IsEmpty() ? this->UserId : this->PartyId, Text.ToString());
			this->InputTextBox->SetText(FText::FromString(TEXT("")));
		}
	}

	FReply OnButtonPressed()
	{
		this->OnSendButtonPressed.ExecuteIfBound(!this->UserId.IsEmpty() ? this->UserId : this->PartyId, InputTextBox->GetText().ToString());
		this->InputTextBox->SetText(FText::FromString(TEXT("")));
		return FReply::Handled();
	}
};

class SPartyMember : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SPartyMember)
	{}
	SLATE_DEFAULT_SLOT(FArguments, Content)
	SLATE_STYLE_ARGUMENT(FLobbyStyle, LobbyStyle)
	SLATE_END_ARGS()

	TSharedPtr<SImage> LeaderBadge;
    TSharedPtr<SImage> ProfilePicture;
	TSharedPtr<STextBlock> Name;
	TSharedPtr<SButton> KickButton;
	TSharedPtr<STextBlock> KickText;
	TSharedPtr<SImage> NoMemberImage;
	FString UserId;
	bool bMySelf = false;
	bool bIsOccupied = false;

	void Construct(const FArguments& InArgs)
	{
		ChildSlot
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[

				SNew(SOverlay)

				+ SOverlay::Slot()			//MainInfo
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SHorizontalBox)

					+ SHorizontalBox::Slot()			//LeaderBadge
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Top)
					.AutoWidth()
					[
						SAssignNew(LeaderBadge, SImage)
						.Image(&InArgs._LobbyStyle->PartyLeaderIcon)
						
					]

					+ SHorizontalBox::Slot()			//Profile
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Center)
					.FillWidth(1.0f)
					[
						SNew(SHorizontalBox)

						+ SHorizontalBox::Slot()			//Picture
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)                        
						.AutoWidth()
						[
                            SNew(SBox)
                            .HeightOverride(56)
                            .WidthOverride(56)
                            [
                                SAssignNew(ProfilePicture, SImage)
                            ]                            
						]

						+ SHorizontalBox::Slot()			//Name
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Center)
						.FillWidth(1.0f)
						[
							SAssignNew(Name, STextBlock)
						]
					]

					+ SHorizontalBox::Slot()			//Kick
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Top)
					.AutoWidth()
					[
						SAssignNew(KickButton, SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.OnClicked(this, &SPartyMember::OnKickButtonClicked)
						[
							SAssignNew(KickText, STextBlock)
							.Text(FText::FromString( bMySelf ? TEXT("LEAVE") : TEXT("KICK")))
						]
					]
				]

				+ SOverlay::Slot()			//NoMemberYet
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SAssignNew(NoMemberImage, SImage)
					.Image(&InArgs._LobbyStyle->UnoccupiedPartySlot)
				]
			
			];
	}

	void Set(FString ID, bool IsPartyLeader, FString DisplayName, FSlateBrush* AvatarBrush)
	{
		UserId = ID;
		Name->SetText(FText::FromString(DisplayName));
        ProfilePicture->SetImage(AvatarBrush);

		LeaderBadge->SetVisibility(IsPartyLeader ? EVisibility::Visible : EVisibility::Hidden);
		KickButton->SetVisibility(!IsPartyLeader ? EVisibility::Visible : EVisibility::Hidden);
		NoMemberImage->SetVisibility(EVisibility::Collapsed);
		bIsOccupied = true;
	}

	void Release()
	{
		bIsOccupied = false;
		Name->SetText(FString::Printf(TEXT("")));
		NoMemberImage->SetVisibility(EVisibility::Visible);
	}

	FReply OnKickButtonClicked()
	{
		if (bMySelf)
		{
			AccelByte::Api::Lobby::Get().SendLeavePartyRequest();
		}
		else
		{
			AccelByte::Api::Lobby::Get().SendKickPartyMemberRequest(UserId);
			AccelByte::Api::Lobby::Get().SendInfoPartyRequest();
		}
		return FReply::Handled();
	}
};

class SParty: public SOverlay
{
public:
	SLATE_BEGIN_ARGS(SParty)
	{}
	SLATE_DEFAULT_SLOT(FArguments, Content)
		SLATE_STYLE_ARGUMENT(FLobbyStyle, LobbyStyle)
		SLATE_END_ARGS()

	TSharedPtr<SPartyMember> Leader;
	TSharedPtr<SPartyMember> Member1;
	TSharedPtr<SPartyMember> Member2;
	TSharedPtr<SPartyMember> Member3;
	TSharedPtr<SButton> ButtonCreateParty;
	TArray<TSharedPtr<SPartyMember>> PartyMembers;

	void Construct(const FArguments& InArgs)
	{
		SOverlay::Construct(
			SOverlay::FArguments()
			+SOverlay::Slot()	//hold party members
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()		
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.0f)
				[
					SNew(SHorizontalBox)		//member 0 (lead) + member 1

					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.FillWidth(1.0f)
					[
						SAssignNew(Leader, SPartyMember)
						.LobbyStyle(InArgs._LobbyStyle)
					]

					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.FillWidth(1.0f)
					[
						SAssignNew(Member1, SPartyMember)
						.LobbyStyle(InArgs._LobbyStyle)
					]
				]

				+ SVerticalBox::Slot()		
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.0f)
				[
					SNew(SHorizontalBox)		//member 2 + member 3

					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.FillWidth(1.0f)
					[
						SAssignNew(Member2, SPartyMember)
						.LobbyStyle(InArgs._LobbyStyle)
					]

					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.FillWidth(1.0f)
					[
						SAssignNew(Member3, SPartyMember)
						.LobbyStyle(InArgs._LobbyStyle)
					]
				]
			]

			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(ButtonCreateParty, SButton)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Text(FText::FromString(TEXT("CreateParty")))
					.Justification(ETextJustify::Center)
				]
			]
		);
		PartyMembers.Add(Leader);
		PartyMembers.Add(Member1);
		PartyMembers.Add(Member2);
		PartyMembers.Add(Member3);
		ButtonCreateParty->SetOnClicked(FOnClicked::CreateLambda([&]()
		{
			AccelByte::Api::Lobby::Get().SendCreatePartyRequest();
			ButtonCreateParty->SetVisibility(EVisibility::Collapsed);
			return FReply::Handled();
		}));
	}

	void InsertMember(FString ID, FString DisplayName, FSlateBrush* AvatarBrush, bool bMyself)
	{
		for(int i = 1; i < 4; i++)
		{
			if (!PartyMembers[i]->bIsOccupied)
			{
				PartyMembers[i]->Set(ID, false, DisplayName, AvatarBrush);
				PartyMembers[i]->KickText->SetText(bMyself ? FString::Printf(TEXT("LEAVE")) : FString::Printf(TEXT("KICK")));
				PartyMembers[i]->bMySelf = bMyself;
				break;
			}
		}
	}

	void InsertLeader(FString ID, FString DisplayName, FSlateBrush* AvatarBrush)
	{
		PartyMembers[0]->Set(ID, true, DisplayName, AvatarBrush);
	}

	void ResetAll()
	{
		for (auto a : PartyMembers)
		{
			a->Release();
		}
		ButtonCreateParty->SetVisibility(EVisibility::Visible);

	}
};

//class declare
class SLobby : public SCompoundWidget
{
public:
    SLobby();

	SLATE_BEGIN_ARGS(SLobby)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<ULocalPlayer>, PlayerOwner)
	SLATE_ARGUMENT(TSharedPtr<SWidget>, OwnerWidget)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	virtual bool SupportsKeyboardFocus() const override { return true; }

	virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;

	virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;

	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

	void OnTextSearchChanged(const FText& Text);

	TSharedRef<ITableRow> MakeListViewWidget(TSharedPtr<FFriendEntry> Item, const TSharedRef<STableViewBase>& OwnerTable);

	void EntrySelectionChanged(TSharedPtr<FFriendEntry> InItem, ESelectInfo::Type SelectInfo);
    void OnListItemDoubleClicked();

	void InputReceived();

	void UpdateSearchStatus();
    void InitializeFriends();
    void SetCurrentUser(FString UserID, FString DisplayName, FString AvatarURL);
    FString GetCurrentUserID();
    void AddFriend(FString UserID, FString DisplayName, FString Avatar);
    void RefreshFriendList();

    void OnPartyCreated(const FAccelByteModelsCreatePartyResponse& Response);

	void BeginFriendSearch();
	void OnFriendSearchFinished();
	void UpdateFriendList();

	void MoveSelection(int32 MoveBy);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);

    void AddChatTab(FString UserId, FString DisplayName, FString PartyId);
    void RemovePartyChatTab(FString PartyId);

    void InviteToParty(FString UserId);
    typedef TMap<FString, FString> ProfileCache;

    TSharedPtr < ProfileCache, ESPMode::ThreadSafe > AvatarListCache;
    TSharedPtr < ProfileCache, ESPMode::ThreadSafe > DiplayNameListCache;
    TMap<FString, TSharedPtr<FSlateDynamicImageBrush> >  ThumbnailBrushCache;
    /** screen resolution */
    FIntPoint ScreenRes;

    FOptionalSize GetLobbyHeight() const;
    int32 GetLobbyWidth() const;



    bool CheckDisplayName(FString UserID) 
    {
        return DiplayNameListCache->Contains(UserID);
    }
    FString GetDisplayName(FString UserID)
    {
        return (*DiplayNameListCache)[UserID];
    }

    bool CheckAvatar(FString UserID)
    {
        return ThumbnailBrushCache.Contains(UserID);
    }

    TSharedPtr<FSlateDynamicImageBrush> GetAvatar(FString UserID)
    {
        return ThumbnailBrushCache[UserID];
    }

    void OnThumbImageReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FString UserID);
    TSharedPtr<FSlateDynamicImageBrush> CreateBrush(FString ContentType, FName ResourceName, TArray<uint8> ImageData);


protected:
	bool bSearchingForFriends;
	double LastSearchTime;
	double MinTimeBetweenSearches;
    FString CurrentUserDisplayName;
    FString CurrentUserID;
    FString CurrentAvatarURL;
	TArray< TSharedPtr<FFriendEntry> > FriendList;
	TArray< TSharedPtr<FFriendEntry> > CompleteFriendList;
	TSharedPtr< SListView< TSharedPtr<FFriendEntry> > > FriendListWidget;
	TSharedPtr<FFriendEntry> SelectedItem;
	FText GetBottomText() const;
	FText StatusText;
	FString MapFilterName;
	int32 BoxWidth;
	TWeakObjectPtr<class ULocalPlayer> PlayerOwner;
	TSharedPtr<class SWidget> OwnerWidget;
	TSharedPtr<SScrollBar> FriendScrollBar;

#pragma region CHAT

	int32 ActiveTabIndex;
	int32 ScrollBoxTabCount = 0;
	TSharedPtr<SButton> ButtonChatTabScrollRight;
	TSharedPtr<SButton> ButtonChatTabScrollLeft;
	TSharedPtr<SScrollBox> ScrollBoxChatTabs;
	TSharedPtr<SWidgetSwitcher> ChatPageSwitcher;
	TArray<TSharedPtr<SChatPage>> LobbyChatPages;
	TArray<TSharedPtr<SChatTabButton>> LobbyChatTabButtons;
	TSharedPtr<SWidget> GetActiveChatTabWidget();
	FReply OnChatTabScrollRightClicked();
	FReply OnChatTabScrollLeftClicked();
	void SelectTab(int32 TabIndex);
	void SendPrivateChat(FString UserId, FString Message);
    void SendPartyChat(FString PartyId, FString Message);

	void OnReceivePrivateChat(const FAccelByteModelsPersonalMessageNotice& Response);
    void OnReceivePartyChat(const FAccelByteModelsPartyMessageNotice& Response);
    void OnUserPresenceNotification(const FAccelByteModelsUsersPresenceNotice& Response);

#pragma endregion CHAT

public:
#pragma region PARTY
	TSharedPtr<SParty> PartyWidget;
	TSharedPtr<SOverlay> InvitationOverlay;
    FString CurrentPartyID;
    void OnInvitedToParty(const FAccelByteModelsPartyGetInvitedNotice& Notification);
    void OnInvitedFriendJoinParty(const FAccelByteModelsPartyJoinNotice& Notification);
    void OnGetPartyInfoResponse(const FAccelByteModelsInfoPartyResponse& PartyInfo);
    void OnKickedFromParty(const FAccelByteModelsGotKickedFromPartyNotice& KickInfo);
    void OnLeavingParty(const FAccelByteModelsLeavePartyNotice& LeaveInfo);
    FSlateColorBrush OverlayBackgroundBrush;
#pragma endregion PARTY

	TSharedPtr<SOverlay> NotificationOverlay;
	void OnIncomingNotification(const FAccelByteModelsNotificationMessage& MessageNotification);
};
