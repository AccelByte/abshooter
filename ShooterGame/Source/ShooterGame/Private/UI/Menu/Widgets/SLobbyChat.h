// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "ShooterStyle.h"
#include "LobbyStyle.h"
#include "SLobbyChatPage.h"
#include "SLobbyChatTabButton.h"

class SLobby;

class SLobbyChat : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLobbyChat)
	{}
	SLATE_ARGUMENT(TSharedPtr<SLobby>, LobbyParent)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	const FLobbyStyle* LobbyStyle;
	FString* CurrentPartyId;
	TSharedPtr<SLobby> LobbyParent;
	TSharedPtr<SButton> ButtonChatTabScrollLeft;
	TSharedPtr<SButton> ButtonChatTabScrollRight;
	TSharedPtr<SScrollBox> ScrollBoxChatTabs;
	TSharedPtr<SWidgetSwitcher> ChatPageSwitcher;
	TArray<TSharedPtr<SLobbyChatTabButton>> LobbyChatTabButtons;
	TArray<TSharedPtr<SLobbyChatPage>> LobbyChatPages;
	int32 ActiveTabIndex = 0;

	FReply OnScrollLeftClicked();
	FReply OnScrollRightClicked();
	void SelectTab(int32 TabIndex);
	void AddPrivate(FString UserId, FString DisplayName);
	void AddParty(FString UserId);
	void Remove(FString UserId);
	void RemovePartyChatTab(FString PartyId = "");
	void SendPrivateChat(FString UserId, FString Message);
	void SendPartyChat(FString PartyId, FString Message);
	void OnReceivePrivateChat(const FAccelByteModelsPersonalMessageNotice& Response);
	void OnReceivePartyChat(const FAccelByteModelsPartyMessageNotice& Response);
private:
	void Add(FString Identifier, FString TabName, bool bIsPartyMode);
	void AppendMessage(FString UserId, FString Sender, FString Message, bool bIsPartyMode);
};
