// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "ShooterStyle.h"
#include "LobbyStyle.h"

DECLARE_DELEGATE_TwoParams(FOnTextCommited, FString, FString);
DECLARE_DELEGATE_TwoParams(FOnSendButtonPressed, FString, FString);

class SLobbyChatPage : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SLobbyChatPage)
	{}
	SLATE_DEFAULT_SLOT(FArguments, Content)
		SLATE_ARGUMENT(FString, Id)
		SLATE_ARGUMENT(FString, DisplayName)
		SLATE_ARGUMENT(int32, ChatPageIndex)
		SLATE_EVENT(FOnTextCommited, OnTextComitted)
		SLATE_EVENT(FOnSendButtonPressed, OnSendButtonPressed)
	SLATE_END_ARGS()

	const FLobbyStyle* LobbyStyle;
	TSharedPtr<SScrollBox> ConversationScrollBox;
	FTextBlockStyle ConversationTextStyle;
	int32 ChatPageIndex;
	FString Id;
	FOnTextCommited OnTextCommited;
	FOnSendButtonPressed OnSendButtonPressed;
	TSharedPtr<SEditableTextBox> InputTextBox;

	void Construct(const FArguments& InArgs);
	void AppendConversation(FString UserName, FString Message);
	void ResetConversation();
	void OnEditableTextBoxCommit(const FText& Text, ETextCommit::Type Type);
	FReply OnButtonPressed();
};