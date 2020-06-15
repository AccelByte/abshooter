// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once
#include "CoreMinimal.h"

// AccelByte
#include "AccelByteError.h"

class ShooterGameSteamUtility
{
public:
	static void SteamLogin(FVoidHandler OnSuccess, FErrorHandler OnError);
	static void OnIdentityLoginComplete(int32 LocalUserNum, bool bSuccessful, const FUniqueNetId& UserId, const FString& ErrorStr, FVoidHandler OnSuccessExt, FErrorHandler OnErrorExt);
};
