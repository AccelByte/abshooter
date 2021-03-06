// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IncomingFriendRequestPopupInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIncomingFriendRequstPopupInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for the UMG incoming friend request popup widget.
 */
class IIncomingFriendRequstPopupInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	* @brief Ignore incoming friend request.
	*
	* @param UserId Friend's userid who sends the friend request.
	*/
	virtual void IgnoreIncomingFriendRequest(FString UserId) = 0;

	/**
	* @brief Reject incoming friend request.
	*
	* @param UserId Friend's userid who sends the friend request.
	*/
	virtual void RejectIncomingFriendRequest(FString UserId) = 0;

	/**
	* @brief Accept incoming friend request.
	*
	* @param UserId Friend's userid who sends the friend request.
	*/
	virtual void AcceptIncomingFriendRequest(FString UserId) = 0;
};
