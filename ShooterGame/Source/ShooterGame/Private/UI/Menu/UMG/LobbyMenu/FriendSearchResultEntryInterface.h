// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FriendSearchResultEntryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFriendSearchResultEntryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for the UMG friend search result entry widget.
 */
class IFriendSearchResultEntryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	* @brief Send a friend request.
	*
	* @param UserId Friend's userid who will be added.
	*/
	virtual void SendFriendRequest(FString UserId) = 0;
};
