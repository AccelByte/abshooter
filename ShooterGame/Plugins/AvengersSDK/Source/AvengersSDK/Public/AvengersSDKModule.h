// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.
#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"
#include "GameFramework/GameModeBase.h"

class AVENGERSSDK_API IAccelByteAvengersSDKModuleInterface : public IModuleInterface
{
public:
	static IAccelByteAvengersSDKModuleInterface& Get()
	{
		return FModuleManager::LoadModuleChecked<IAccelByteAvengersSDKModuleInterface>("AvengersSDK");
	}

	static bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("AvengersSDK");
	}

	virtual void Tick(float DeltaTime) = 0;
	virtual void BeginPlay(APlayerController* PlayerController) = 0;
    virtual void EndPlay() = 0;
};
