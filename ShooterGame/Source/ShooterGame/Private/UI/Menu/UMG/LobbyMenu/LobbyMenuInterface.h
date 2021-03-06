// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LobbyMenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULobbyMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for the UMG Lobby menu widget.
 */
class ILobbyMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	* @brief Add friend based on the its username.
	*
	* @param Username Friend's username who will be added.
	*/
	virtual void AddFriend(FString Username) = 0;

	/** Refresh friend list. */
	virtual void RefreshFriendList() = 0;

	/** Create a party. */
	virtual void CreateParty() = 0;

	/**
	* @brief Change Game Mode.
	*
	* @param GameModeName The Game Mode for the matchmaking.
	*/
	virtual void ChangeGameMode(FString GameModeName) = 0;

	/** Start Matchmaking. */
	virtual void StartMatchmaking(FString GameModeDisplayName) = 0;

	/** Cancel Matchmaking. */
	virtual void CancelMatchmaking() = 0;

	/** Ready matchmaking. */
	virtual void ReadyMatchmaking() = 0;
};
