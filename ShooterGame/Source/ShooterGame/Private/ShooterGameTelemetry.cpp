// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "ShooterGameTelemetry.h"
#include "CoreMinimal.h"
#include "JsonUtilities.h"
#include "ShooterGameConfig.h"
#include "Kismet/GameplayStatics.h"
#include "Core/AccelByteRegistry.h"
#include "Api/AccelByteGameTelemetryApi.h"
#include "GameServerApi/AccelByteServerGameTelemetryApi.h"

FString ShooterGameTelemetry::ELoginTypeToString(const ELoginType& Type)
{
	switch (Type)
	{
	case ELoginType::LAUNCHER:
		return "Launcher";
	case ELoginType::STEAM:
		return "Steam";
	case ELoginType::USERNAME:
		return "Username";
	default:
		return "";
	}
}

void TelemetryDispatcher(TSharedPtr<FJsonObject> JsonObject, const FString& EventName)
{
	FAccelByteModelsTelemetryBody TelemetryBody{ "abshooter", EventName, JsonObject };
#if UE_SERVER
	FRegistry::ServerGameTelemetry.Send(
		TelemetryBody,
		FVoidHandler::CreateLambda([EventName]()
		{
			UE_LOG(LogTemp, Display, TEXT("%s event sent successfully."), *EventName);
		})
		, FErrorHandler::CreateLambda([EventName](int32 ErrorCode, FString Message)
		{
			UE_LOG(LogTemp, Display, TEXT("%s event error.\nCode:%d\nMessage:%s"), *EventName, ErrorCode, *Message);
		}));
#else
	FRegistry::GameTelemetry.Send(
		TelemetryBody,
		FVoidHandler::CreateLambda([EventName]()
		{
			UE_LOG(LogTemp, Display, TEXT("%s event sent successfully."), *EventName);
		})
		, FErrorHandler::CreateLambda([EventName](int32 ErrorCode, FString Message)
		{
			UE_LOG(LogTemp, Display, TEXT("%s event error.\nCode:%d\nMessage:%s"), *EventName, ErrorCode, *Message);
		}));
#endif
}

ShooterGameTelemetry::ShooterGameTelemetry()
{
	GameSessionID = FGuid::NewGuid().ToString(EGuidFormats::Digits);
	GameVersion = ShooterGameConfig::Get().GameReleaseVersion_;
	SdkVersion = ShooterGameConfig::Get().SdkVersion_;
	DsTargetVersion = ShooterGameConfig::Get().ServerImageVersion_;
	Platform = UGameplayStatics::GetPlatformName();
}

void ShooterGameTelemetry::Login(const ELoginType& Type, const FString& UserId)
{
	if (LoginSessionID.IsEmpty())
	{
		LoginSessionID = FGuid::NewGuid().ToString(EGuidFormats::Digits);
	}

	StartLoginSession = FDateTime::UtcNow();

	FShooterGameTelemetryLoginModel Request;
	Request.DSTargetVersion = DsTargetVersion;
	Request.SDKVersion = SdkVersion;
	Request.GameVersion = GameVersion;
	Request.GameSessionId = GameSessionID;
	Request.LoginSessionId = LoginSessionID;
	Request.LoginType = ELoginTypeToString(Type);
	Request.Platform = Platform;
	Request.UserId = UserId;

	auto JsonObject = FJsonObjectConverter::UStructToJsonObject(Request);
	TelemetryDispatcher(JsonObject, ShooterGameConfig::Get().TelemetryEvents_.LoggedIn);
}

void ShooterGameTelemetry::Logout()
{
	FTimespan Duration = FDateTime::UtcNow() - StartLoginSession;

	FShooterGameTelemetryLogoutModel Request;
	Request.GameSessionId = GameSessionID;
	Request.LoginSessionId = LoginSessionID;
	Request.LoginSessionDuration = Duration.ToString();

	auto JsonObject = FJsonObjectConverter::UStructToJsonObject(Request);
	if (LoginSessionID != "") // If user not logged out, then 
	{
		TelemetryDispatcher(JsonObject, ShooterGameConfig::Get().TelemetryEvents_.LoggedOut);
	}
	DisableHeartbeat();
}

void ShooterGameTelemetry::StartMatch(const FString& MatchID, const FString& GameMode)
{
	CurrentMatchID = MatchID;

	FShooterGameTelemetryStartMatchModel Request;
	Request.GameSessionId = GameSessionID;
	Request.MatchId = MatchID;
	Request.ConnectToLocal = ShooterGameConfig::Get().IsLocalMode_;
	Request.GameMode = GameMode;

	auto JsonObject = FJsonObjectConverter::UStructToJsonObject(Request);
	TelemetryDispatcher(JsonObject, ShooterGameConfig::Get().TelemetryEvents_.MatchStart);
}

void ShooterGameTelemetry::EndMatch(bool IsWinner, const FString& EndReason)
{
	FShooterGameTelemetryEndMatchModel Request;
	Request.GameSessionId = GameSessionID;
	Request.MatchId = CurrentMatchID;
	Request.EndReason = EndReason;
	Request.IsWinner = IsWinner;

	auto JsonObject = FJsonObjectConverter::UStructToJsonObject(Request);
	TelemetryDispatcher(JsonObject, ShooterGameConfig::Get().TelemetryEvents_.MatchEnd);

	CurrentMatchID = "";
}

void ShooterGameTelemetry::EnableHeartbeat()
{
	FTickerDelegate HeartbeatTicker = FTickerDelegate::CreateLambda([&](float Interval)
		{
			this->Heartbeat();
			return true;
		});
	HeartbeatTickerHandle = FTicker::GetCoreTicker().AddTicker(HeartbeatTicker, ShooterGameConfig::Get().TelemetryHeartbeatInterval_);
}

void ShooterGameTelemetry::DisableHeartbeat()
{
	FTicker::GetCoreTicker().RemoveTicker(HeartbeatTickerHandle);
}

void ShooterGameTelemetry::Heartbeat()
{
	FShooterGameTelemetryHeartBeatModel Request;
	Request.GameSessionId = GameSessionID;
#if UE_SERVER
	Request.IsServer = true;
#else
	Request.IsServer = false;
#endif

	auto JsonObject = FJsonObjectConverter::UStructToJsonObject(Request);
	TelemetryDispatcher(JsonObject, ShooterGameConfig::Get().TelemetryEvents_.Heartbeat);
}
