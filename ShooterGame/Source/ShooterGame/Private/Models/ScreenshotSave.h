#pragma once

#include "CoreMinimal.h"
#include "Api/AccelByteCloudStorageApi.h"
#include "GameFramework/SaveGame.h"
#include "ScreenshotSave.generated.h"

USTRUCT(BlueprintType)
struct FScreenshotSave
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Models")
	TArray<FAccelByteModelsSlot> Screenshots;
};