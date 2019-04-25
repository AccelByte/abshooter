// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AvengersDumpConfig.generated.h"

/**
* @brief Describe a dump config.
*/
USTRUCT()
struct AVENGERSSDK_API FAvengersDumpConfig
{
	GENERATED_BODY()
	UPROPERTY()
		int FrameCaptured; /**< Stores the frame captured. */
	UPROPERTY()
		FString SessionID = TEXT(""); /**< Stores the session id. */
};
