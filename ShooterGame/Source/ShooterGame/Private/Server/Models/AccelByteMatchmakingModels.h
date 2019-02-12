// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "AccelByteMatchmakingModels.generated.h"

// Client send matchmaking info to dedicated server (for testing purpose would be removed in the future)
#define SIMULATE_SETUP_MATCHMAKING 1

USTRUCT(BlueprintType)
struct FAccelByteModelsMatchmakingMember
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Matchmaking | Models | Member")
	int32 assist;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Matchmaking | Models | Member")
	int32 death;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Matchmaking | Models | Member")
	int32 kill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Matchmaking | Models | Member")
	FString user_id;
};

USTRUCT(BlueprintType)
struct FAccelByteModelsMatchmakingResult
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Matchmaking | Models | Result")
	FString leader;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Matchmaking | Models | Result")
	TArray<FAccelByteModelsMatchmakingMember> members;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Matchmaking | Models | Result")
	FString party_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Matchmaking | Models | Result")
	int32 rank;
};

USTRUCT(BlueprintType)
struct FAccelByteModelsMatchmakingPartyMember
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Matchmaking | Models | PartyMember")
		FString user_id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AccelByte | Matchmaking | Models | PartyMember")
		bool joined{false};
};

USTRUCT(BlueprintType)
struct FAccelByteModelsMatchmakingParty
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Matchmaking | Models | Party")
		FString party_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Matchmaking | Models | Party")
		FString leader_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Matchmaking | Models | Party")
		TArray<FAccelByteModelsMatchmakingPartyMember> party_members;
};

USTRUCT(BlueprintType)
struct FAccelByteModelsMatchmakingInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Matchmaking | Models | Info")
		FString match_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Matchmaking | Models | Info")
		FString channel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AccelByte | Matchmaking | Models | Info")
		TArray<FAccelByteModelsMatchmakingParty> matching_parties;
};