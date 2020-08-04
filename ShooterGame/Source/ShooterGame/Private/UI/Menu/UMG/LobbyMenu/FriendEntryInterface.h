// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FriendEntryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFriendEntryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for the UMG friend entry widget.
 */
class IFriendEntryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	* @brief Send a party invitation request.
	*
	* @param UserId Friend's user id who will be invited to the party.
	*/
	virtual void SendPartyInvitationRequest(FString UserId) = 0;

	/**
	* @brief Send an unfriend request.
	*
	* @param UserId Friend's user id who will be unfriend.
	*/
	virtual void SendUnfriendRequest(FString UserId) = 0;

	/**
	* @brief Send accept incoming friend request.
	*
	* @param UserId Friend's user id who send the friend request.
	*/
	virtual void SendAcceptFriendRequest(FString UserId) = 0;

	/**
	* @brief Send reject incoming friend request.
	*
	* @param UserId Friend's user id who send the friend request.
	*/
	virtual void SendRejectFriendRequest(FString UserId) = 0;

	/**
	* @brief Send cancel outgoing friend request.
	*
	* @param UserId Friend's user id who will be cancelled.
	*/
	virtual void SendCancelFriendRequest(FString UserId) = 0;
};
