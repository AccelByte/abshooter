// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "LobbyMenuUI.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Components/WidgetSwitcher.h"
#include "Components/HorizontalBox.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"

FCriticalSection LobbyMenuUIMutex;

bool ULobbyMenuUI::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(AddFriendButton != nullptr)) return false;
	AddFriendButton->OnClicked.AddDynamic(this, &ULobbyMenuUI::AddFriend);

	if (!ensure(RefreshButton != nullptr)) return false;
	RefreshButton->OnClicked.AddDynamic(this, &ULobbyMenuUI::RefreshFriendList);

	if (!ensure(LobbySwitcher != nullptr)) return false;
	if (!ensure(ConnectSuccess != nullptr)) return false;
	if (!ensure(ConnectProcess != nullptr)) return false;
	if (!ensure(ConnectFailed != nullptr)) return false;
	if (!ensure(FriendUsernameField != nullptr)) return false;
	if (!ensure(FriendListView != nullptr)) return false;
	if (!ensure(OnlineFriendsField != nullptr)) return false;
	if (!ensure(LobbyErrorText != nullptr)) return false;

	return true;
}

void ULobbyMenuUI::OpenConnectSuccessPanel()
{
	LobbySwitcher->SetActiveWidget(ConnectSuccess);
}

void ULobbyMenuUI::OpenConnectProcessPanel()
{
	LobbySwitcher->SetActiveWidget(ConnectProcess);
}

void ULobbyMenuUI::OpenConnectFailedPanel(FString Message)
{
	LobbyErrorText->SetText(FText::FromString(Message));
	LobbySwitcher->SetActiveWidget(ConnectFailed);
}

void ULobbyMenuUI::SetInterface(ILobbyMenuInterface* MenuInterface)
{
	if (MenuInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ULobbyMenuUI] MenuInterface is null"));
		return;
	}
	LobbyMenuInterface = MenuInterface;
}

void ULobbyMenuUI::ClearFriendUsernameField()
{
	FriendUsernameField->SetText(FText::FromString(TEXT("")));
}

void ULobbyMenuUI::UpdateFriendList(TArray<UFriendEntryUI*> FriendList)
{
	if (this == NULL) return;

	FScopeLock Lock(&LobbyMenuUIMutex);

	FriendListView->SetListItems(FriendList);
	FriendListView->RegenerateAllEntries();

	int32 OnlineFriends = 0;
	int32 TotalFriends = 0;
	for (int i = 0; i < FriendList.Num(); i++)
	{
		if (FriendList[i]->Data.Presence == EFriendPresence::ONLINE) OnlineFriends++;
		if (FriendList[i]->Data.Type == EFriendType::FRIEND) TotalFriends++;
	}
	FString OnlineFriendsText = FString::Printf(TEXT("ONLINE FRIENDS: %d / %d"), OnlineFriends, TotalFriends);
	OnlineFriendsField->SetText(FText::FromString(OnlineFriendsText));
}

#pragma region Button Callback
void ULobbyMenuUI::AddFriend()
{
	// if the input field is empty or whitespace, do not send the request, return
	if (FriendUsernameField->GetText().IsEmptyOrWhitespace())
	{
		UE_LOG(LogTemp, Warning, TEXT("[ULobbyMenuUI] Friend username field is empty or whitespace."));
		return;
	}

	if (LobbyMenuInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ULobbyMenuUI] LobbyMenuInterface is null"));
		return;
	}

	const FString FriendEmail = FriendUsernameField->GetText().ToString();
	LobbyMenuInterface->AddFriend(FriendEmail);
}

void ULobbyMenuUI::RefreshFriendList()
{
	if (LobbyMenuInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ULobbyMenuUI] LobbyMenuInterface is null"));
		return;
	}
	LobbyMenuInterface->RefreshFriendList();
}
#pragma endregion Button Callback
