// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once
#include "CoreMinimal.h"
#include "ShooterGameTelemetry.generated.h"

USTRUCT(BlueprintType)
struct FShooterGameTelemetryLoginModel
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString GameSessionId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString UserId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LoginSessionId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LoginType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString GameVersion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString SDKVersion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString DSTargetVersion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Platform;
};

USTRUCT(BlueprintType)
struct FShooterGameTelemetryLogoutModel
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString GameSessionId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LoginSessionId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LoginSessionDuration;
};

USTRUCT(BlueprintType)
struct FShooterGameTelemetryStartMatchModel
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString GameSessionId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MatchId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool ConnectToLocal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString GameMode;
};

USTRUCT(BlueprintType)
struct FShooterGameTelemetryEndMatchModel
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString GameSessionId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsWinner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString EndReason;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MatchId;
};

USTRUCT(BlueprintType)
struct FShooterGameTelemetryHeartBeatModel
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString GameSessionId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsServer;
};

class ShooterGameTelemetry
{
public: 

	enum ELoginType
	{
		USERNAME,
		LAUNCHER,
		STEAM //TODO: support login using Steam
	};

	static ShooterGameTelemetry& Get()
	{
		static ShooterGameTelemetry Instance;
		return Instance;
	}

	void Login(const ELoginType& Type, const FString& UserId);
	void Logout();
	void StartMatch(const FString& MatchID, const FString& GameMode);
	void EndMatch(bool IsWinner, const FString& EndReason);
	void EnableHeartbeat();
	void DisableHeartbeat();

private:
	ShooterGameTelemetry(ShooterGameTelemetry const&) = delete;
	void operator=(ShooterGameTelemetry const&) = delete;
	ShooterGameTelemetry();
	~ShooterGameTelemetry() {}

	FString LoginSessionID = "";
	FString GameSessionID = "";
	FString GameVersion = "";
	FString SdkVersion = "";
	FString DsTargetVersion = "";
	FString Platform = "";
	FDateTime StartLoginSession;
	FString CurrentMatchID = "";

	FDelegateHandle HeartbeatTickerHandle;
	void Heartbeat();

	FString ELoginTypeToString(const ELoginType& Type);
};