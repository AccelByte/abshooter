// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULoginMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for the UMG Login menu widget.
 */
class ILoginMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/**
	* @brief Login with username and password.
	*
	* @param Username The login's username of the user.
	* @param Password The login's password of the user.
	*/
	virtual void LoginWithUsername(FString Username, FString Password) = 0;
};
