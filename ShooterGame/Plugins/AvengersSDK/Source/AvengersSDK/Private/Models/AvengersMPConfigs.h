// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AvengersMPConfigs.generated.h"

/**
* @brief Describe a game symbol.
*/
USTRUCT()
struct AVENGERSSDK_API FAvengersGameSymbol
{
	GENERATED_BODY()
	UPROPERTY()
		FString module_id = TEXT(""); /**< Stores the module id. */
	UPROPERTY()
		FString symbol_name = TEXT(""); /**< Stores the symbol name. */
};

/**
* @brief Describe a MicroProfile configurations.
*/
USTRUCT()
struct AVENGERSSDK_API FAvengersMPConfigs
{
	GENERATED_BODY()
	UPROPERTY()
		 TArray<FAvengersGameSymbol> GameSymbols; /**< Stores the game symbols. */
	UPROPERTY()
		FString SessionID = TEXT(""); /**< Stores the session id. */
};
typedef TSharedPtr<FAvengersMPConfigs> FAvengersMPConfigsPtr;
