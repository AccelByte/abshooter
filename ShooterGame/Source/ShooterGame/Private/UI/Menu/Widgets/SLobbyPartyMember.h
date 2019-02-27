// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "LobbyStyle.h"
#include "ShooterStyle.h"

class SLobbyPartyMember : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLobbyPartyMember)
	{}
	SLATE_DEFAULT_SLOT(FArguments, Content)
	SLATE_END_ARGS()
	
	const FLobbyStyle* LobbyStyle;
	TSharedPtr<SImage> LeaderBadge;
    TSharedPtr<SImage> ProfilePicture;
	TSharedPtr<STextBlock> Name;
	TSharedPtr<SButton> KickButton;
	TSharedPtr<SImage> MemberImage;
	FString UserId;
	FButtonStyle LeavePartyMemberButton;
	FButtonStyle KickPartyMemberButton;

	bool bMySelf = false;
	bool bIsOccupied = false;

	void Construct(const FArguments& InArgs);

	void Set(FString ID, bool IsPartyLeader, FString DisplayName, FSlateBrush* AvatarBrush);

	void Release();

	FReply OnKickButtonClicked();

	void UpdateButtonStyleMode();

	bool GetIsOccupied() const;
};
