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
		SLATE_STYLE_ARGUMENT(FLobbyStyle, LobbyStyle)
		SLATE_EVENT(FOnClickedChatTabButton, OnClicked)

		SLATE_END_ARGS()

	int32 TabIndex = 0;
	FString UserId = TEXT("");
	FOnClickedChatTabButton OnChatTabClicked;
	FTextBlockStyle ActiveTextStyle;
	FTextBlockStyle PassiveTextStyle;
	TSharedPtr<FTextBlockStyle> CurrentTextStyle = MakeShareable(new FTextBlockStyle());
	TSharedPtr<STextBlock> TextWidget;

	void Construct(const FArguments& InArgs)
	{
		UE_LOG(LogTemp, Log, TEXT("Construct Chat Button %d %s") , InArgs._TabIndex, *InArgs._UserId);
		OnChatTabClicked = InArgs._OnClicked;
		TabIndex = InArgs._TabIndex;
		ActiveTextStyle = (InArgs._LobbyStyle)->ChatTabTextStyle;
		PassiveTextStyle = (InArgs._LobbyStyle)->ChatTabTextDisabledStyle;
		UserId = InArgs._UserId;

		SButton::Construct(
			SButton::FArguments()
			.ButtonStyle(&(InArgs._LobbyStyle)->ChatTabButtonStyle)
			.OnClicked(this, &SChatTabButton::InternalOnClicked)
			.IsEnabled(true)
			[
				SAssignNew(TextWidget, STextBlock)
				.TextStyle(&ActiveTextStyle)
				.Text(FText::FromString(InArgs._UserId))
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
		SLATE_ARGUMENT(FString, ChatStat)
		SLATE_ARGUMENT(FString, UserId)
		SLATE_ARGUMENT(int32, ChatPageIndex)
		SLATE_EVENT(FOnTextCommited, OnTextComitted)
		SLATE_EVENT(FOnSendButtonPressed, OnSendButtonPressed)
		SLATE_STYLE_ARGUMENT(FLobbyStyle, LobbyStyle)
		SLATE_END_ARGS()

	TSharedPtr<SScrollBox> ConversationScrollBox;
	FTextBlockStyle ConversationTextStyle;
	int32 ChatPageIndex;
	FString UserId;
	FOnTextCommited OnTextCommited;
	FOnSendButtonPressed OnSendButtonPressed;
	TSharedPtr<SEditableTextBox> InputTextBox;

	void Construct(const FArguments& InArgs)
	{
		ChatPageIndex = InArgs._ChatPageIndex;
		UserId = InArgs._UserId;
		ConversationTextStyle = InArgs._LobbyStyle->ConversationTextStyle;
		OnTextCommited = InArgs._OnTextComitted;
		OnSendButtonPressed = InArgs._OnSendButtonPressed;

		SVerticalBox::Construct(
			SVerticalBox::FArguments()
			
			+ SVerticalBox::Slot()	//ChatStat
			.AutoHeight()
			[
				SNew(STextBlock)
				.Text(FText::FromString(InArgs._ChatStat))
				.TextStyle(&(InArgs._LobbyStyle)->ChatStatStyle)
			]
			
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
		//ConversationScrollBox->
	}

	void OnEditableTextBoxCommit(const FText& Text, ETextCommit::Type Type)
	{
		if (Type == ETextCommit::Type::OnEnter)
		{
			OnTextCommited.ExecuteIfBound(this->UserId, Text.ToString());
			this->InputTextBox->SetText(FText::FromString(TEXT("")));
		}
	}

	FReply OnButtonPressed()
	{
		this->OnSendButtonPressed.ExecuteIfBound(this->UserId, InputTextBox->GetText().ToString());
		this->InputTextBox->SetText(FText::FromString(TEXT("")));
		return FReply::Handled();
	}


};

//class declare
class SLobby : public SCompoundWidget/*, public TSharedFromThis<SLobby>*/
{
public:
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
    void AddFriend(FString UserID, FString DisplayName, FString Avatar);
    void RefreshFriendList();


	void BeginFriendSearch();
	void OnFriendSearchFinished();
	void UpdateFriendList();

	void MoveSelection(int32 MoveBy);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);

    void AddChatTab(bool IsParty, FString PartyId, FString UserId);

    //static TSharedRef<SLobby> CreateRoot()
    //{
    //    return MakeShareable(new SLobby());
    //}
protected:

	bool bSearchingForFriends;

	double LastSearchTime;

	double MinTimeBetweenSearches;

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
	
	void SendChat(FString UserId, FString Message);
	void ReceiveChat(FString UserId, FString Message);

#pragma endregion CHAT
};
