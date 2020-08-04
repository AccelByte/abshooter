// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "ShooterLobbyModels.generated.h"

UENUM(BlueprintType)
enum class EFriendPresence : uint8
{
	ONLINE = 0,
	INGAME,
	IDLE,
	OFFLINE
};

UENUM(BlueprintType)
enum class EFriendType : uint8
{
	FRIEND = 0,
	INCOMING,
	OUTGOING
};

USTRUCT(BlueprintType)
struct FFriendEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby | Models")
		FString UserId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby | Models")
		FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby | Models")
		EFriendPresence Presence;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby | Models")
		EFriendType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby | Models")
		FSlateBrush Avatar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby | Models")
		bool onParty = false;
};

USTRUCT(BlueprintType)
struct FGameModeEntry
{
	GENERATED_BODY()

	/* Need to rename it to DisplayName for more clarity. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby | Models")
		FString DisplayName;

	/* GameModeName that will be accepted by backend e.g 10ffa, 3v3, 5v5, br. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby | Models")
		FString GameMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby | Models")
		int32 MaxMembers = 0;
};

USTRUCT(BlueprintType)
struct FPartyMemberEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby | Models")
		FString UserId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby | Models")
		FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby | Models")
		FSlateBrush Avatar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby | Models")
		bool isLeader = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby | Models")
		bool isMySelf = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby | Models")
		bool isKickable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby | Models")
		bool onInvitation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby | Models")
		bool onBeingKicked = false;
};