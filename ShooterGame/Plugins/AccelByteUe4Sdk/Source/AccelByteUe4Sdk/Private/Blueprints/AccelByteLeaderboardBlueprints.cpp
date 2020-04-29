// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "Blueprints/AccelByteLeaderboardBlueprints.h"
#include "Api/AccelByteLeaderboardApi.h"
#include "Core/AccelByteRegistry.h"

using AccelByte::FRegistry;
using AccelByte::FErrorHandler;


void UAccelByteBlueprintsLeaderboard::GetRankings(const FString & LeaderboardCode, const EAccelByteLeaderboardTimeFrame & TimeFrame, int32 Offset, int32 Limit, const FGetRankingsSuccess & OnSuccess, const FBlueprintErrorHandler & OnError)
{
	FRegistry::Leaderboard.GetRankings(
		LeaderboardCode,
		TimeFrame,
		Offset,
		Limit,
		THandler<FAccelByteModelsLeaderboardRankingResult>::CreateLambda([OnSuccess](const FAccelByteModelsLeaderboardRankingResult& Result)
		{
				OnSuccess.ExecuteIfBound(Result);
		}),
		FErrorHandler::CreateLambda([OnError](int32 Code, FString Message)
		{
			OnError.ExecuteIfBound(Code, Message);
		}));
}

void UAccelByteBlueprintsLeaderboard::GetUserRanking(const FString & UserID, const FString & LeaderboardCode, const FGetUserRankingSuccess & OnSuccess, const FBlueprintErrorHandler & OnError)
{
	FRegistry::Leaderboard.GetUserRanking(
		UserID,
		LeaderboardCode,
		THandler<FAccelByteModelsUserRankingData>::CreateLambda([OnSuccess](const FAccelByteModelsUserRankingData& Result)
		{
			OnSuccess.ExecuteIfBound(Result);
		}),
		FErrorHandler::CreateLambda([OnError](int32 Code, FString Message)
		{
			OnError.ExecuteIfBound(Code, Message);
		}));
}
