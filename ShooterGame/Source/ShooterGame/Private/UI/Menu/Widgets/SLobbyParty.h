// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "LobbyStyle.h"
#include "SLobbyPartyMember.h"

class SParty: public SOverlay
{
public:
	SLATE_BEGIN_ARGS(SParty)
	{}
		SLATE_DEFAULT_SLOT(FArguments, Content)
		SLATE_STYLE_ARGUMENT(FLobbyStyle, LobbyStyle)
	SLATE_END_ARGS()

	TSharedPtr<SLobbyPartyMember> Leader;
	TSharedPtr<SLobbyPartyMember> Member1;
	TSharedPtr<SLobbyPartyMember> Member2;
	TSharedPtr<SLobbyPartyMember> Member3;
	TSharedPtr<SButton> ButtonCreateParty;
	TArray<TSharedPtr<SLobbyPartyMember>> PartyMembers;

	void Construct(const FArguments& InArgs);

	void InsertMember(FString ID, FString DisplayName, FSlateBrush* AvatarBrush, bool bMyself);

	void InsertLeader(FString ID, FString DisplayName, FSlateBrush* AvatarBrush, bool bMyself);

	void ResetAll();

	int32 GetCurrentPartySize();

	FReply OnCreatePartyClicked() const;
};
