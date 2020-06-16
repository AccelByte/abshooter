// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Utils/ImageUtils.h"
#include "ShooterCacheModels.generated.h"

USTRUCT(BlueprintType)
struct FUserCache
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache | Models")
		FString UserId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache | Models")
		FString DisplayName;
};

USTRUCT(BlueprintType)
struct FUserCaches
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache | Models")
		TArray<FUserCache> Caches;
};

