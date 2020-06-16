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
};
