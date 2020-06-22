// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PartyMemberEntryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPartyMemberEntryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for the UMG party member entry widget.
 */
class IPartyMemberEntryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/** Leave a party.	*/
	virtual void LeaveParty() = 0;

	/**
	* @brief Kick a party member.
	*
	* @param UserId The id of party member who is kicked.
	*/
	virtual void KickPartyMember(FString UserId) = 0;
};
