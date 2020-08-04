// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyMenuInterface.h"
#include "FriendEntryUI.h"
#include "PartyMemberEntryUI.h"
#include "LobbyMenuUI.generated.h"


UENUM()
enum class EMatchmakingState : int32
{
	PRESTART	UMETA(DisplayName = "PreStart"),
	INPROGRESS	UMETA(DisplayName = "InProgress"),
	DISABLED	UMETA(DisplayName = "Disabled"),
	FOUND		UMETA(DisplayName = "Found"),
	READY		UMETA(DisplayName = "Ready")
};

/**
 * Lobby menu UI widget.
 */
UCLASS()
class ULobbyMenuUI : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Open connect success panel (lobby panel). */
	void OpenConnectSuccessPanel();

	/** Open connect process panel (loading bar). */
	void OpenConnectProcessPanel();

	/**
	* @brief Open connect failed panel (error message).
	*
	* @param Message Lobby error message.
	*/
	void OpenConnectFailedPanel(FString Message);

	/**
	* @brief Set lobby menu interface.
	*
	* @param MenuInterface The menu interface for the widget.
	*/
	void SetInterface(ILobbyMenuInterface* MenuInterface);

	/** Clear username text on FriendUsernameField widget. */
	void ClearFriendUsernameField();

	/**
	* @brief Update friend list view.
	*
	* @param FriendList The array of friend entry. 
	*/
	void UpdateFriendList(TArray<UFriendEntryUI*> FriendList);

	/**
	* @brief Set Game Modes into combo box.
	*
	* @param GameModeNames The array of the game mode names.
	*/
	void SetGameModes(TArray<FString> GameModeNames);

	/**
	* @brief Update party member list view.
	*
	* @param PartyMemberList The array of party member entry.
	*/
	void UpdatePartyMemberList(TArray<UPartyMemberEntryUI*> PartyMemberList);

	/** Open create party button. */
	void OpenCreatePartyPanel();

	/** Open party setup box. */
	void OpenPartySetupPanel();

	/**
	* @brief Show game mode combo box.
	*
	* @param isShowed True for showing game mode combo box or false otherwise.
	*/
	void ShowGameModeComboBox(bool isShowed);

	/**
	* @brief Set number of must-kicked party member in the kick member message text.
	*
	* @param OverPartyMember The number of must-kicked party member.
	*/
	void SetOverPartyMember(int32 OverPartyMember);

	/*
	*
	* @brief Set Index of Start Match widget UWidgetSwitcher.
	* 
	* @param WidgetIndex The index of the widgets
	*
	*/
	void SetMatchmakingWidgetStatus(EMatchmakingState MatchmakingState);


	/*
	*
	* @brief Set Current Matchmaking Countdown when player is presented with Ready Action.
	*
	* @param Countdown Current Time left for ready acceptance
	*
	*/
	void SetMatchmakingCountdown(int Countdown);
	
	/*
	*
	* @brief Set Current Matchmaking Duration when player is finding a match.
	*
	* @param Duration Duration of player looking for a match.
	*
	*/
	void SetMatchmakingDuration(int Duration);

private:
	/** Initialize widget. */
	virtual bool Initialize();

private:

	/** Search friend. */
	UFUNCTION()
	void AddFriend();

	/** Refresh friend list. */
	UFUNCTION()
	void RefreshFriendList();

	/** Start Matchmaking */
	UFUNCTION()
	void StartMatch();

	/** Cancel Matchmaking */
	UFUNCTION()
	void CancelMatch();

	/** Cancel Matchmaking */
	UFUNCTION()
	void ReadyMatch();

	/** Game Mode combo box. */
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* GameModesComboBox;

	/** Create a party. */
	UFUNCTION()
	void CreateParty();

	/** Handle Game Mode changing. */
	UFUNCTION()
	void ChangeGameMode(FString SelectedItem, ESelectInfo::Type SelectionType);

	/** Lobby response switcher. */
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* LobbySwitcher;

	/** Create party button switcher. */
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* CreatePartySwitcher;

	/** Lobby connect success panel. */
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* ConnectSuccess;

	/** Lobby connect process panel. */
	UPROPERTY(meta = (BindWidget))
	class UOverlay* ConnectProcess;

	/** Lobby connect failed panel. */
	UPROPERTY(meta = (BindWidget))
	class UOverlay* ConnectFailed;

	/** Create party process panel. */
	UPROPERTY(meta = (BindWidget))
	class UOverlay* CreatePartyProcess;

	/** Friend username field. */
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* FriendUsernameField;

	/** Add friend button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* AddFriendButton;

	/** Refresh friend list button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* RefreshButton;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MatchmakingStatusSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* MatchmakingPreStart;

	UPROPERTY(meta = (BindWidget))
	class UButton* StartMatchButton;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* MatchmakingInProgress;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MatchmakingDurationText;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelMatchButton;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* MatchmakingDisabled;

	// TODO : Simplify this by combining it with PreStart, then adding BanDuration as collapsible Text
	UPROPERTY(meta = (BindWidget))
	class UButton* DisabledMatchButton;
	
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* MatchmakingFound;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MatchCountdownText;

	UPROPERTY(meta = (BindWidget))
	class UButton* MatchReadyButton;

	/** Create a party button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* CreatePartyButton;

	/** Friend list view. */
	UPROPERTY(meta = (BindWidget))
	class UListView* FriendListView;

	/** Party member list view. */
	UPROPERTY(meta = (BindWidget))
	class UListView* PartyMemberListView;

	/** Online friends field. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* OnlineFriendsField;

	/** Lobby error message text. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LobbyErrorText;

	/** Kick member message text. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* KickMemberText;

	/** Party setup box. */
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* PartySetupBox;

	/** Lobby menu interface. */
	ILobbyMenuInterface* LobbyMenuInterface;

	/** Game Mode options. */
	TArray<FString> GameModeOptions;
};
