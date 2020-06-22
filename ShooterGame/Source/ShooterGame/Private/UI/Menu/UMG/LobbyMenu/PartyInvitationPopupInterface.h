// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PartyInvitationPopupInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPartyInvitationPopupInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for the UMG party invitation popup widget.
 */
class IPartyInvitationPopupInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	* @brief Accept party invitation.
	*
	* @param InvitationInformation The information of the party invitation.
	*/
	virtual void AcceptPartyInvitation(struct FAccelByteModelsPartyGetInvitedNotice InvitationInformation) = 0;
};
