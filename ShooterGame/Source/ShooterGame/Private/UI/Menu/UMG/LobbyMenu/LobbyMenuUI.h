// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyMenuInterface.h"
#include "FriendEntryUI.h"
#include "LobbyMenuUI.generated.h"

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

	/** Open connect failed panel (error message). */
	void OpenConnectFailedPanel();

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

protected:
	/** Initialize widget. */
	virtual bool Initialize();

private:
	/** Search friend. */
	UFUNCTION()
	void AddFriend();

	/** Refresh friend list. */
	UFUNCTION()
	void RefreshFriendList();

	/** Lobby response switcher. */
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* LobbySwitcher;

	/** Lobby connect success panel. */
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* ConnectSuccess;

	/** Lobby connect process panel. */
	UPROPERTY(meta = (BindWidget))
	class UOverlay* ConnectProcess;

	/** Lobby connect failed panel. */
	UPROPERTY(meta = (BindWidget))
	class UOverlay* ConnectFailed;

	/** Friend username field. */
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* FriendUsernameField;

	/** Add friend button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* AddFriendButton;

	/** Refresh friend list button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* RefreshButton;
	
	/** Friend list view. */
	UPROPERTY(meta = (BindWidget))
	class UListView* FriendListView;

	/** Online friends field. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* OnlineFriendsField;

	/** Lobby menu interface. */
	ILobbyMenuInterface* LobbyMenuInterface;
};
