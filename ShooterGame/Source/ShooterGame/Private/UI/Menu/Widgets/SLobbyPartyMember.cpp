// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "LobbyStyle.h"
#include "SLobbyPartyMember.h"
#include "Api/AccelByteLobbyApi.h"
#include "Core/AccelByteRegistry.h"

void SLobbyPartyMember::Construct(const FArguments& InArgs)
{
	LobbyStyle = &FShooterStyle::Get().GetWidgetStyle<FLobbyStyle>("DefaultLobbyStyle");

	LeavePartyMemberButton = LobbyStyle->LeavePartyMemberButton;
	KickPartyMemberButton = LobbyStyle->KickPartyMemberButton;

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
					.Image(&LobbyStyle->PartyLeaderIcon)
					.Visibility(TAttribute<EVisibility>::Create([&]() {return SLobbyPartyMember::GetIsOccupied() ? EVisibility::Visible : EVisibility::Hidden; }))
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
							.Visibility(TAttribute<EVisibility>::Create([&]() {return SLobbyPartyMember::GetIsOccupied() ? EVisibility::Visible : EVisibility::Hidden; }))
						]
					]

					+ SHorizontalBox::Slot()			//Name
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Center)
					.Padding(5, 0, 0, 0)
					.FillWidth(1.0f)
					[
						SAssignNew(Name, STextBlock)
						.Visibility(TAttribute<EVisibility>::Create([&]() {return SLobbyPartyMember::GetIsOccupied() ? EVisibility::Visible : EVisibility::Hidden; }))
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
					.OnClicked(this, &SLobbyPartyMember::OnKickButtonClicked)
					.ButtonStyle(&LobbyStyle->LeavePartyMemberButton)
					.Visibility(TAttribute<EVisibility>::Create([&]() {return SLobbyPartyMember::GetIsOccupied()?EVisibility::Visible:EVisibility::Hidden; }))
				]
			]

			+ SOverlay::Slot()			//NoMemberYet
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(MemberImage, SImage)
				.Image(&LobbyStyle->UnoccupiedPartySlot)
			]

		];
}

void SLobbyPartyMember::Set(FString ID, bool IsPartyLeader, FString DisplayName, FSlateBrush* AvatarBrush)
{
	this->SetVisibility(EVisibility::Visible);
	UserId = ID;
	Name->SetText(FText::FromString(DisplayName));
    ProfilePicture->SetImage(AvatarBrush);

	LeaderBadge->SetVisibility(IsPartyLeader ? EVisibility::Visible : EVisibility::Hidden);
	KickButton->SetVisibility(!IsPartyLeader ? EVisibility::Visible : EVisibility::Hidden);
	MemberImage->SetImage(IsPartyLeader ? &LobbyStyle->LeaderBoxPartySlot : &LobbyStyle->MemberBoxPartySlot);
	bIsOccupied = true;
}

void SLobbyPartyMember::Release()
{
	bIsOccupied = false;
	Name->SetText(FString::Printf(TEXT("")));
	MemberImage->SetImage(&LobbyStyle->UnoccupiedPartySlot);
	MemberImage->SetVisibility(EVisibility::Visible);
}

FReply SLobbyPartyMember::OnKickButtonClicked()
{
	if (bMySelf)
	{
		AccelByte::FRegistry::Lobby.SendLeavePartyRequest();
	}
	else
	{
		AccelByte::FRegistry::Lobby.SendKickPartyMemberRequest(UserId);
		AccelByte::FRegistry::Lobby.SendInfoPartyRequest();
	}
	return FReply::Handled();
}

void SLobbyPartyMember::UpdateButtonStyleMode()
{
	if (bMySelf)
	{
		KickButton->SetButtonStyle(&LeavePartyMemberButton);
	}
	else
	{
		KickButton->SetButtonStyle(&KickPartyMemberButton);
	}
}

bool SLobbyPartyMember::GetIsOccupied() const
{
	return bIsOccupied;
}