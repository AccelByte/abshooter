// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "IncomingFriendRequestPopupUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

bool UIncomingFriendRequestPopupUI::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(IgnoreButton != nullptr)) return false;
	IgnoreButton->OnClicked.AddDynamic(this, &UIncomingFriendRequestPopupUI::IgnoreRequest);

	if (!ensure(RejectButton != nullptr)) return false;
	RejectButton->OnClicked.AddDynamic(this, &UIncomingFriendRequestPopupUI::RejectRequest);

	if (!ensure(AcceptButton != nullptr)) return false;
	AcceptButton->OnClicked.AddDynamic(this, &UIncomingFriendRequestPopupUI::AcceptRequest);

	if (!ensure(MessageText != nullptr)) return false;

	return true;
}

void UIncomingFriendRequestPopupUI::Show(FString FriendId, FString DisplayName)
{
	UserId = FriendId;
	FString Message = FString::Printf(TEXT("You have an incoming friend request from [%s]"), *DisplayName);
	MessageText->SetText(FText::FromString(Message));
	
	this->AddToPlayerScreen();
}

void UIncomingFriendRequestPopupUI::SetInterface(IIncomingFriendRequstPopupInterface* Interface)
{
	if (Interface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UIncomingFriendRequestPopupUI] Interface is null"));
		return;
	}
	IncomingFriendRequstPopupInterface = Interface;
}

#pragma region Button Callback
void UIncomingFriendRequestPopupUI::IgnoreRequest()
{
	if (IncomingFriendRequstPopupInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UIncomingFriendRequestPopupUI] IncomingFriendRequstPopupInterface is null"));
		return;
	}
	IncomingFriendRequstPopupInterface->IgnoreIncomingFriendRequest(UserId);

	this->RemoveFromViewport();
}

void UIncomingFriendRequestPopupUI::RejectRequest()
{
	if (IncomingFriendRequstPopupInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UIncomingFriendRequestPopupUI] IncomingFriendRequstPopupInterface is null"));
		return;
	}
	IncomingFriendRequstPopupInterface->RejectIncomingFriendRequest(UserId);

	this->RemoveFromViewport();
}

void UIncomingFriendRequestPopupUI::AcceptRequest()
{
	if (IncomingFriendRequstPopupInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UIncomingFriendRequestPopupUI] IncomingFriendRequstPopupInterface is null"));
		return;
	}
	IncomingFriendRequstPopupInterface->AcceptIncomingFriendRequest(UserId);

	this->RemoveFromViewport();
}
#pragma endregion Button Callback
