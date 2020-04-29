// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Models/AccelByteLeaderboardModels.h"
#include "AccelByteLeaderboardBlueprints.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UAccelByteBlueprintsLeaderboard : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FBlueprintErrorHandler, int32, ErrorCode, const FString&, ErrorMessage);

	DECLARE_DYNAMIC_DELEGATE_OneParam(FGetRankingsSuccess, const FAccelByteModelsLeaderboardRankingResult&, Result);
	UFUNCTION(BlueprintCallable, Category = "AccelByte | Leaderboard | Api")
		static void GetRankings(const FString& LeaderboardCode, const EAccelByteLeaderboardTimeFrame& TimeFrame, int32 Offset, int32 Limit, const FGetRankingsSuccess& OnSuccess, const FBlueprintErrorHandler& OnError);

	DECLARE_DYNAMIC_DELEGATE_OneParam(FGetUserRankingSuccess, const FAccelByteModelsUserRankingData &, Result);
	UFUNCTION(BlueprintCallable, Category = "AccelByte | Leaderboard | Api")
		static void GetUserRanking(const FString& UserID, const FString& LeaderboardCode, const FGetUserRankingSuccess& OnSuccess, const FBlueprintErrorHandler& OnError);
};

