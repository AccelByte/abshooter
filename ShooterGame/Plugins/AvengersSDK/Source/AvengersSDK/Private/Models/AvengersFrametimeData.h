// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AvengersFrametimeData.generated.h"

/**
* @brief Describe a frametime.
*/
USTRUCT()
struct AVENGERSSDK_API FAvengersFrametime
{
	GENERATED_BODY()
	UPROPERTY()
		int frametime = 0; /**< Stores the frametime. */
};

USTRUCT()
struct AVENGERSSDK_API FAvengersDITime
{
    GENERATED_BODY()
        UPROPERTY()
        float di = 0; /**< Stores the frametime. */
};



/**
* @brief Describe a frametime data.
*/
USTRUCT()
struct AVENGERSSDK_API FAvengersFrametimeData
{
	GENERATED_BODY()
	UPROPERTY()
		FString session_id = TEXT(""); /**< Stores the session id. */
	UPROPERTY()
		FString timestamp_start = TEXT(""); /**< Stores the timestamp. */
	UPROPERTY()
		TArray<FAvengersFrametime> payload; /**< Stores the frametime payload data. */
};


USTRUCT()
struct AVENGERSSDK_API FAvengersDynamicInstrumentData
{
    GENERATED_BODY()
        UPROPERTY()
        FString session_id = TEXT(""); /**< Stores the session id. */
    UPROPERTY()
        FString timestamp_start = TEXT(""); /**< Stores the timestamp. */
    UPROPERTY()
        TArray<FAvengersDITime> payload; /**< Stores the frametime payload data. */
};
