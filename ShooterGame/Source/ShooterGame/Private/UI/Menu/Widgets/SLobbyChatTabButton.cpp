// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "LobbyStyle.h"
#include "SLobbyChatTabButton.h"

void SLobbyChatTabButton::Construct(const FArguments& InArgs)
{
	LobbyStyle = &FShooterStyle::Get().GetWidgetStyle<FLobbyStyle>("DefaultLobbyStyle");

	OnChatTabClicked = InArgs._OnClicked;
	TabIndex = InArgs._TabIndex;
	ActiveTextStyle = LobbyStyle->ChatTabTextStyle;
	PassiveTextStyle = LobbyStyle->ChatTabTextDisabledStyle;
	UserId = InArgs._UserId;
    PartyId = InArgs._PartyId;
    DisplayName = InArgs._DisplayName;

	SButton::Construct(
		SButton::FArguments()
		.ButtonStyle(&LobbyStyle->ChatTabButtonStyle)
		.OnClicked(this, &SLobbyChatTabButton::InternalOnClicked)
		.IsEnabled(true)
		.VAlign(VAlign_Center)
		[
			SAssignNew(TextWidget, STextBlock)
			.TextStyle(&ActiveTextStyle)
			.Text(FText::FromString(DisplayName))
		]
	);
}

void SLobbyChatTabButton::Selected()
{
	UE_LOG(LogTemp, Log, TEXT("Button %s is selected"), *UserId);
	this->SetEnabled(false);
	TextWidget->SetTextStyle(&PassiveTextStyle);
};

void SLobbyChatTabButton::NotSelected()
{
	UE_LOG(LogTemp, Log, TEXT("Button %s is deselected"), *UserId);
	this->SetEnabled(true);
	TextWidget->SetTextStyle(&ActiveTextStyle);
};

FReply SLobbyChatTabButton::InternalOnClicked()
{
	OnChatTabClicked.ExecuteIfBound(TabIndex);
	return FReply::Handled();
}
	