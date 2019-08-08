// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "LobbyStyle.h"
#include "SLobbyParty.h"
#include "Api/AccelByteLobbyApi.h"
#include "Core/AccelByteRegistry.h"

void SParty::Construct(const FArguments& InArgs)
{
    SOverlay::Construct(
        SOverlay::FArguments()
        + SOverlay::Slot()	//hold party members
        .HAlign(HAlign_Fill)
        .VAlign(VAlign_Fill)
        .Padding(FMargin(0, 3))
        [
            SNew(SVerticalBox)

            + SVerticalBox::Slot()	//member 0 (lead)
            .HAlign(HAlign_Fill)
            .VAlign(VAlign_Fill)
            .MaxHeight(140.f)
            [
                SAssignNew(Leader, SLobbyPartyMember)
                .Visibility(EVisibility::Hidden)
            ]

            + SVerticalBox::Slot()	// + member 1
            .HAlign(HAlign_Fill)
            .VAlign(VAlign_Fill)
            .MaxHeight(140.f)
            [
                SAssignNew(Member1, SLobbyPartyMember)
                .Visibility(EVisibility::Hidden)
            ]

            + SVerticalBox::Slot()	//member 2
            .HAlign(HAlign_Fill)
            .VAlign(VAlign_Fill)
            .MaxHeight(140.f)
            [
                SAssignNew(Member2, SLobbyPartyMember)
                .Visibility(EVisibility::Hidden)
            ]

            + SVerticalBox::Slot()	//member 3
            .HAlign(HAlign_Fill)
            .VAlign(VAlign_Fill)
            .MaxHeight(140.f)
            [
                SAssignNew(Member3, SLobbyPartyMember)
                .Visibility(EVisibility::Hidden)
            ]
        ]

        + SOverlay::Slot()
        .HAlign(HAlign_Fill)
        .VAlign(VAlign_Fill)
        [
            SAssignNew(ButtonCreateParty, SButton)
            .HAlign(HAlign_Center)
            .VAlign(VAlign_Center)
            .ButtonStyle(&(InArgs._LobbyStyle)->CreatePartyMemberButton)
            .OnClicked(this, &SParty::OnCreatePartyClicked)
        ]
    );
    PartyMembers.Add(Leader);
    PartyMembers.Add(Member1);
    PartyMembers.Add(Member2);
    PartyMembers.Add(Member3);
}

void SParty::InsertMember(FString ID, FString DisplayName, FSlateBrush* AvatarBrush, bool bMyself)
{
    bool IsClientPartyLeader = PartyMembers[0]->bMySelf ? true : false;
    for (int i = 1; i < 4; i++)
    {
        if (!PartyMembers[i]->bIsOccupied)
        {
            PartyMembers[i]->bMySelf = bMyself;
            PartyMembers[i]->Set(ID, false, DisplayName, AvatarBrush, IsClientPartyLeader);
            PartyMembers[i]->UpdateButtonStyleMode();
            break;
        }
    }
}

void SParty::InsertLeader(FString ID, FString DisplayName, FSlateBrush* AvatarBrush, bool bMyself)
{
    PartyMembers[0]->bMySelf = bMyself;
    PartyMembers[0]->Set(ID, true, DisplayName, AvatarBrush, bMyself);
    PartyMembers[0]->UpdateButtonStyleMode();

}

void SParty::ResetAll()
{
    for (auto a : PartyMembers)
    {
        a->Release();
    }
    ButtonCreateParty->SetVisibility(EVisibility::Visible);
}

int32 SParty::GetCurrentPartySize()
{
    int32 Counter = 0;
    for (int i = 0; i < 4; i++)
    {
        Counter += (PartyMembers[i]->bIsOccupied);
    }
    return Counter;
}

FReply SParty::OnCreatePartyClicked() const
{
    for (auto a : PartyMembers)
    {
        a->SetVisibility(EVisibility::Visible);
    }
    AccelByte::FRegistry::Lobby.SendCreatePartyRequest();
    ButtonCreateParty->SetVisibility(EVisibility::Hidden);
    return FReply::Handled();
}