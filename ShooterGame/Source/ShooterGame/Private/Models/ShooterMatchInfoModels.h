#pragma once

#include "CoreMinimal.h"
#include "Models/AccelByteMatchmakingModels.h"

#include "ShooterMatchInfoModels.generated.h"

USTRUCT(BlueprintType)
struct FShooterMatchPlayer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MatchPlayer | Models")
	FString user_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MatchPlayer | Models")
	FString name;
};

USTRUCT(BlueprintType)
struct FShooterMatchInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MatchInfo | Models")
	FAccelByteModelsMatchmakingResult matchmaking_info;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MatchInfo | Models")
	int32 remaining_time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MatchInfo | Models")
	FName match_state;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MatchInfo | Models")
	TArray<FShooterMatchPlayer> players;
};