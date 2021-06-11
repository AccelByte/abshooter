#pragma once

#include "CoreMinimal.h"

#include "ShooterMemberModels.generated.h"

USTRUCT(BlueprintType)
struct FShooterMemberAttribute
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Member | Models")
		FString user_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Member | Models")
		int32 match;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Member | Models")
		int32 kill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Member | Models")
		int32 death;
};