// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AvengersClientDesc.generated.h"

/**
* @brief Describe a client description.
*/
USTRUCT()
struct AVENGERSSDK_API FAvengersClientDesc
{
	GENERATED_BODY()
	UPROPERTY()
		FString CPU = TEXT(""); /**< Stores the client CPU. */
	UPROPERTY()
		FString ClientID = TEXT(""); /**< Stores the client ID. */
	UPROPERTY()
		FString Country = TEXT(""); /**< Stores the country. */
	UPROPERTY()
		FString GPU = TEXT(""); /**< Stores the client GPU. */
	UPROPERTY()
		FString GPUDriver = TEXT(""); /**< Stores the client GPU Driver. */
	UPROPERTY()
		FString GameVersionID = TEXT(""); /**< Stores the game version ID. */
	UPROPERTY()
		FString IPAddress = TEXT(""); /**< Stores the client IP Address. */
	UPROPERTY()
		FString Locale = TEXT(""); /**< Stores the client locale. */
	UPROPERTY()
		int Memory = 0; /**< Stores the client memory. */
	UPROPERTY()
		FString OperatingSystem = TEXT(""); /**< Stores the client operating system. */
	UPROPERTY()
		FString OperatingVersion = TEXT(""); /**< Stores the client operating version. */
	UPROPERTY()
		FString Renderer = TEXT(""); /**< Stores the client renderer. */
	UPROPERTY()
		FString SessionStartedAt = TEXT(""); /**< Stores the client session started at. */
	UPROPERTY()
		FString SystemArchitecture = TEXT(""); /**< Stores the client system architecture. */
};
