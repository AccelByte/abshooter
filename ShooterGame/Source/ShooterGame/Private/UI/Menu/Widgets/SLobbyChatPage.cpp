// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "SLobbyChatPage.h"

void SLobbyChatPage::Construct(const FArguments& InArgs)
	{
		LobbyStyle = &FShooterStyle::Get().GetWidgetStyle<FLobbyStyle>("DefaultLobbyStyle");

		ChatPageIndex = InArgs._ChatPageIndex;
		Id = InArgs._Id;
		ConversationTextStyle = LobbyStyle->ConversationTextStyle;
		OnTextCommited = InArgs._OnTextComitted;
		OnSendButtonPressed = InArgs._OnSendButtonPressed;

		ChildSlot
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SVerticalBox)

			+ SVerticalBox::Slot()	//ChatScrollBox conversation
			.FillHeight(1.0f)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(ConversationScrollBox, SScrollBox)
				.Style(&LobbyStyle->ConversationScrollBoxStyle)
				.Orientation(EOrientation::Orient_Vertical)
				.ScrollBarAlwaysVisible(true)
				.ScrollBarStyle(&LobbyStyle->ConversationScrollBarStyle)
			]

			+ SVerticalBox::Slot()	//ChatInputArea
			.AutoHeight()
			[
				SNew(SOverlay)
						
				+ SOverlay::Slot()		//ChatInput TypeBackGround
				[
					SNew(SImage)
					.Image(&LobbyStyle->ConversationInputBackgroundBrush)
				]

				+ SOverlay::Slot()		//ChatInput Input
				.VAlign(VAlign_Center)
				[
					SNew(SHorizontalBox)

					+ SHorizontalBox::Slot()	//ChatInput
					.FillWidth(1.0f)
					[
						SAssignNew(InputTextBox, SEditableTextBox)
						.Style(&LobbyStyle->ConversationInputTextStyle)
						.OnTextCommitted(this, &SLobbyChatPage::OnEditableTextBoxCommit)
						.ClearKeyboardFocusOnCommit(false)
					]

					+ SHorizontalBox::Slot()	//SendButton
					.AutoWidth()
					[
						SNew(SButton)
						.ButtonStyle(&LobbyStyle->ConversationInputSendButtonStyle)
						.OnClicked(this, &SLobbyChatPage::OnButtonPressed)
					]
				]
			]

		];
	}

void SLobbyChatPage::AppendConversation(FString UserName, FString Message)
	{
		TSharedPtr<SMultiLineEditableText> Text;
		FString FormatText = FString::Printf(TEXT("[%s] : %s"), *UserName, *Message);
		ConversationScrollBox->AddSlot()
			.VAlign(VAlign_Top)
			.HAlign(HAlign_Fill)
			.AttachWidget
			(
				SAssignNew(Text, SMultiLineEditableText)
				.Justification(ETextJustify::Left)
				.TextStyle(&ConversationTextStyle)
				.Text(FText::FromString(FormatText))
				.AutoWrapText(true)
				.IsReadOnly(true)
			);
		ConversationScrollBox->ScrollDescendantIntoView(Text);
	}

void SLobbyChatPage::ResetConversation()
	{

	}

void SLobbyChatPage::OnEditableTextBoxCommit(const FText& Text, ETextCommit::Type Type)
	{
		if (Type == ETextCommit::Type::OnEnter)
		{
			OnTextCommited.ExecuteIfBound(Id, Text.ToString());
			this->InputTextBox->SetText(FText::FromString(TEXT("")));
		}
	}

FReply SLobbyChatPage::OnButtonPressed()
	{
		this->OnSendButtonPressed.ExecuteIfBound(Id, InputTextBox->GetText().ToString());
		this->InputTextBox->SetText(FText::FromString(TEXT("")));
		return FReply::Handled();
	}
