// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "FriendSearchResultEntryUI.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

bool UFriendSearchResultEntryUI::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(AddFriendButton != nullptr)) return false;
	AddFriendButton->OnClicked.AddDynamic(this, &UFriendSearchResultEntryUI::SendFriendRequest);

	if (!ensure(DisplayNameField != nullptr)) return false;
	if (!ensure(EmailField != nullptr)) return false;

	return true;
}

void UFriendSearchResultEntryUI::SetListItemObjectInternal(UObject* InObject)
{
	UFriendSearchResultEntryUI* Entry = Cast<UFriendSearchResultEntryUI>(InObject);

	UserId = Entry->UserId;

	DisplayName = Entry->DisplayName;
	DisplayNameField->SetText(FText::FromString(Entry->DisplayName));

	Email = Entry->Email;
	EmailField->SetText(FText::FromString(Entry->Email));

	EntryInterface = Entry->EntryInterface;
}

void UFriendSearchResultEntryUI::SetInterface(IFriendSearchResultEntryInterface* Interface)
{
	if (Interface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UFriendSearchResultEntryUI] Interface is null"));
		return;
	}
	EntryInterface = Interface;
}

#pragma region Button Callback
void UFriendSearchResultEntryUI::SendFriendRequest()
{
	if (EntryInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UFriendSearchResultEntryUI] EntryInterface is null"));
		return;
	}
	EntryInterface->SendFriendRequest(UserId);
}
#pragma endregion Button Callback
