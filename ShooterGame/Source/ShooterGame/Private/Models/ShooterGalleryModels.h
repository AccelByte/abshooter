// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Api/AccelByteCloudStorageApi.h"
#include "ShooterGalleryModels.generated.h"

UENUM(BlueprintType)
enum class EGalleryState : uint8
{
	NONE = 0,
	ERROR_UNKNOWN, // fix compile error on Xbox, ERROR already defined macro on Xbox
	DONE,
	// loading bar would be showed (state > DONE)
	DOWNLOADING,
	UPLOADING,
	DELETING,
	UPDATING
};

USTRUCT(BlueprintType)
struct FScreenshotMetadata
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gallery | Models")
		TArray<FAccelByteModelsSlot> Screenshots;
};

USTRUCT(BlueprintType)
struct FScreenshotSave
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gallery | Models")
		TArray<FAccelByteModelsSlot> Screenshots;
};
