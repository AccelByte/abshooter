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
#include "Components/ComboBoxString.h"
#include "Components/VerticalBox.h"

FCriticalSection LobbyMenuUIMutex;




bool ULobbyMenuUI::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(AddFriendButton != nullptr)) return false;
	AddFriendButton->OnClicked.AddDynamic(this, &ULobbyMenuUI::AddFriend);

	if (!ensure(RefreshButton != nullptr)) return false;
	RefreshButton->OnClicked.AddDynamic(this, &ULobbyMenuUI::RefreshFriendList);

	if (!ensure(CreatePartyButton != nullptr)) return false;
	CreatePartyButton->OnClicked.AddDynamic(this, &ULobbyMenuUI::CreateParty);

	if (!ensure(GameModesComboBox != nullptr)) return false;
	GameModesComboBox->OnSelectionChanged.AddDynamic(this, &ULobbyMenuUI::ChangeGameMode);

	if (!ensure(StartMatchButton != nullptr)) return false;
	StartMatchButton->OnClicked.AddDynamic(this, &ULobbyMenuUI::StartMatch);

	if (!ensure(CancelMatchButton != nullptr)) return false;
	CancelMatchButton->OnClicked.AddDynamic(this, &ULobbyMenuUI::CancelMatch);

	if (!ensure(MatchReadyButton != nullptr)) return false;
	MatchReadyButton->OnClicked.AddDynamic(this, &ULobbyMenuUI::ReadyMatch);

	if (!ensure(LobbySwitcher != nullptr)) return false;
	if (!ensure(ConnectSuccess != nullptr)) return false;
	if (!ensure(ConnectProcess != nullptr)) return false;
	if (!ensure(ConnectFailed != nullptr)) return false;
	if (!ensure(CreatePartyProcess != nullptr)) return false;
	if (!ensure(FriendUsernameField != nullptr)) return false;
	if (!ensure(FriendListView != nullptr)) return false;
	if (!ensure(OnlineFriendsField != nullptr)) return false;
	if (!ensure(LobbyErrorText != nullptr)) return false;
	if (!ensure(GameModesComboBox != nullptr)) return false;
	if (!ensure(CreatePartySwitcher != nullptr)) return false;
	if (!ensure(PartySetupBox != nullptr)) return false;
	if (!ensure(PartyMemberListView != nullptr)) return false;
	if (!ensure(KickMemberText != nullptr)) return false;

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

void ULobbyMenuUI::SetMatchmakingCountdown(int Countdown)
{
	FText TextItem = FText::FromString(FString::Printf(TEXT("%d s"), Countdown));
	MatchCountdownText->SetText(TextItem);
}

void ULobbyMenuUI::SetMatchmakingDuration(int Duration)
{
	int Minutes = Duration /60;
	int Seconds = Duration %60;
	FText TextItem = FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds));
	MatchmakingDurationText->SetText(TextItem);
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

void ULobbyMenuUI::SetGameModes(TArray<FString> GameModeNames)
{
	if (GameModeNames.Num() == 0)
	{
		UE_LOG(LogTemp, Fatal, TEXT("[ULobbyMenuUI] Failed to set Game Mode combo box. GameMode options is empty."));
		return;
	}

	GameModeOptions = GameModeNames;
	for (FString GameModeName : GameModeNames)
	{
		GameModesComboBox->AddOption(GameModeName);
	}
	GameModesComboBox->SetSelectedOption(GameModeNames[0]);
}

void ULobbyMenuUI::UpdatePartyMemberList(TArray<UPartyMemberEntryUI*> PartyMemberList)
{
	FScopeLock Lock(&LobbyMenuUIMutex);

	PartyMemberListView->SetListItems(PartyMemberList);
	PartyMemberListView->RegenerateAllEntries();

	if (PartyMemberList.Num() == 0)
	{
		CreatePartySwitcher->SetActiveWidget(CreatePartyButton);
	}
}

void ULobbyMenuUI::OpenCreatePartyPanel()
{
	CreatePartySwitcher->SetActiveWidget(CreatePartyButton);
}

void ULobbyMenuUI::OpenPartySetupPanel()
{
	CreatePartySwitcher->SetActiveWidget(PartySetupBox);
}

void ULobbyMenuUI::ShowGameModeComboBox(bool isShowed)
{
	if (isShowed) GameModesComboBox->SetVisibility(ESlateVisibility::Visible);
	else GameModesComboBox->SetVisibility(ESlateVisibility::Hidden);
}

void ULobbyMenuUI::SetOverPartyMember(int32 OverPartyMember)
{
	if (OverPartyMember > 0)
	{
		FString Message = FString::Printf(TEXT("Kick %d party member%s or change Game Mode!"), OverPartyMember, OverPartyMember == 1 ? TEXT("") : TEXT("s"));
		KickMemberText->SetText(FText::FromString(Message));
		KickMemberText->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		KickMemberText->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ULobbyMenuUI::SetMatchmakingWidgetStatus(EMatchmakingState MatchmakingState)
{
	MatchmakingStatusSwitcher->SetActiveWidgetIndex((int)MatchmakingState);
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

void ULobbyMenuUI::StartMatch()
{
	if (LobbyMenuInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ULobbyMenuUI] LobbyMenuInterface is null"));
		return;
	}
	// Game Mode Name for Backend References, not UI
	FString GameModeDisplayName = GameModesComboBox->GetSelectedOption();
	LobbyMenuInterface->StartMatchmaking(GameModeDisplayName);
}

void ULobbyMenuUI::CancelMatch()
{
	if (LobbyMenuInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ULobbyMenuUI] LobbyMenuInterface is null"));
		return;
	}
	LobbyMenuInterface->CancelMatchmaking();
}

void ULobbyMenuUI::ReadyMatch()
{
	if (LobbyMenuInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ULobbyMenuUI] LobbyMenuInterface is null"));
		return;
	}
	LobbyMenuInterface->ReadyMatchmaking();
}


void ULobbyMenuUI::CreateParty()
{
	if (LobbyMenuInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ULobbyMenuUI] LobbyMenuInterface is null"));
		return;
	}

	if (GameModeOptions.Num() == 0)
	{
		UE_LOG(LogTemp, Fatal, TEXT("[ULobbyMenuUI] Failed to set Game Mode combo box. GameMode options is empty."));
		return;
	}
	GameModesComboBox->SetSelectedOption(GameModeOptions[0]);

	CreatePartySwitcher->SetActiveWidget(CreatePartyProcess);
	LobbyMenuInterface->CreateParty();
}
#pragma endregion Button Callback

#pragma region ComboBox Callback
void ULobbyMenuUI::ChangeGameMode(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (LobbyMenuInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ULobbyMenuUI] LobbyMenuInterface is null"));
		return;
	}

	if (SelectionType == ESelectInfo::Type::OnMouseClick)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ULobbyMenuUI] SelectedItem: %s"), *SelectedItem);
		LobbyMenuInterface->ChangeGameMode(SelectedItem);
	}
}
#pragma endregion ComboBox Callback