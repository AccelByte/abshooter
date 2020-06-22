// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "PartyInvitationPopupUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

bool UPartyInvitationPopupUI::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(RejectButton != nullptr)) return false;
	RejectButton->OnClicked.AddDynamic(this, &UPartyInvitationPopupUI::RejectPartyInvitation);

	if (!ensure(AcceptButton != nullptr)) return false;
	AcceptButton->OnClicked.AddDynamic(this, &UPartyInvitationPopupUI::AcceptPartyInvitation);

	if (!ensure(MessageText != nullptr)) return false;

	return true;
}

void UPartyInvitationPopupUI::Show(FString DisplayName, FAccelByteModelsPartyGetInvitedNotice InvitationInformation)
{
	InvitationInfo = InvitationInformation;
	FString Message = FString::Printf(TEXT("You're invited by [%s] to join a party."), *DisplayName);
	MessageText->SetText(FText::FromString(Message));

	this->AddToPlayerScreen();
}

void UPartyInvitationPopupUI::SetInterface(IPartyInvitationPopupInterface* Interface)
{
	if (Interface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UIncomingFriendRequestPopupUI] Interface is null"));
		return;
	}
	PartyInvitationPopupInterface = Interface;
}


void UPartyInvitationPopupUI::Tick(float DeltaTime)
{
	PartyInvitationCounter -= DeltaTime;
	if (PartyInvitationCounter <= 0) 
	{
		PartyInvitationCounter = 0;
		RejectPartyInvitation();
	}
	RejectText->SetText(FText::FromString(FString::Printf(TEXT("REJECT (%.0f)"), PartyInvitationCounter)));
}

bool UPartyInvitationPopupUI::IsTickable() const
{
	return !InvitationInfo.From.IsEmpty();
}

bool UPartyInvitationPopupUI::IsTickableInEditor() const
{
	return false;
}

bool UPartyInvitationPopupUI::IsTickableWhenPaused() const
{
	return false;
}

TStatId UPartyInvitationPopupUI::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UPartyInvitationPopupUI, STATGROUP_Tickables);
}

#pragma region Button Callback
void UPartyInvitationPopupUI::RejectPartyInvitation()
{
	this->RemoveFromViewport();
}

void UPartyInvitationPopupUI::AcceptPartyInvitation()
{
	if (PartyInvitationPopupInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UPartyInvitationPopupUI] PartyInvitationPopupInterface is null"));
		return;
	}
	PartyInvitationPopupInterface->AcceptPartyInvitation(InvitationInfo);

	this->RemoveFromViewport();
}
#pragma endregion Button Callback
