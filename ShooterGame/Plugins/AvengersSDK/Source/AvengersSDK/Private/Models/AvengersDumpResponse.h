// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AvengersDumpResponse.generated.h"

/**
* @brief Describe a dump config response .
*/
USTRUCT()
struct AVENGERSSDK_API FAvengersDumpResponse
{
	GENERATED_BODY()
	UPROPERTY()
		FString ContentType = TEXT(""); /**< Stores the content type. */
	UPROPERTY()
		FString DumpID = TEXT(""); /**< Stores the dump id. */
	UPROPERTY()
		FString UploadURL; /**< Stores the upload URL. */
};
typedef TSharedPtr<FAvengersDumpResponse> FAvengersDumpResponsePtr;
