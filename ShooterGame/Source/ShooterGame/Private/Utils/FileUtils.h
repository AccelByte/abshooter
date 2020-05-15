// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"

class FShooterFileUtils
{
public:
	/**
	* @brief Get avatar cache path based on the user id.
	*
	* @param UserId the id of the user.
	*/
	static FString GetAvatarCachePatch(FString UserId);
};
