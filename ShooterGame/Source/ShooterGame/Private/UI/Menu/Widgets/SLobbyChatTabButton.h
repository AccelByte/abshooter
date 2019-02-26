// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "LobbyStyle.h"
#include "ShooterStyle.h"

DECLARE_DELEGATE_OneParam(FOnClickedChatTabButton, int32);

class SLobbyChatTabButton : public SButton
{
public:
	SLATE_BEGIN_ARGS(SLobbyChatTabButton)
	{}
	SLATE_DEFAULT_SLOT(FArguments, Content)
		SLATE_ARGUMENT(int32, TabIndex)
		SLATE_ARGUMENT(FString, UserId)
        SLATE_ARGUMENT(FString, PartyId)
        SLATE_ARGUMENT(FString, DisplayName)
		SLATE_EVENT(FOnClickedChatTabButton, OnClicked)

		SLATE_END_ARGS()

	int32 TabIndex = 0;
	FString UserId = TEXT("");
    FString PartyId = TEXT("");
    FString DisplayName = TEXT("");
	FOnClickedChatTabButton OnChatTabClicked;
	const FLobbyStyle* LobbyStyle;
	FTextBlockStyle ActiveTextStyle;
	FTextBlockStyle PassiveTextStyle;
	TSharedPtr<FTextBlockStyle> CurrentTextStyle = MakeShareable(new FTextBlockStyle());
	TSharedPtr<STextBlock> TextWidget;

	void Construct(const FArguments& InArgs);

	void Selected();

	void NotSelected();

	FReply InternalOnClicked();
	
};
