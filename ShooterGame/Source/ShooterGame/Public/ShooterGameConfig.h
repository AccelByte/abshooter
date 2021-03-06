#pragma once
#include "CoreGlobals.h"
#include "Models/AccelByteQosModels.h"

struct GameModeData
{
	FString Name;
	FString GameModeName;
	int32 MaxPlayer;
};

struct ShooterGameTelemetryEvents
{
	FString LoggedIn;
	FString LoggedOut;
	FString MatchStart;
	FString MatchEnd;
	FString Heartbeat;
	FString ItemEquip;
};

class ShooterGameConfig
{
public:
	static ShooterGameConfig& Get()
	{
		static ShooterGameConfig instance;
		return instance;
	}

private:
	ShooterGameConfig();

	int32 ServerPort;
	FString LocalServerIP;
	FString LocalServerName;
	FString DsLocalModeCommandLineArg;
	FString ServerImageVersion;
	bool IsLocalMode;
	int ServerHeartbeatInterval;
	TArray<TPair<FString, float>> ServerLatencies;
	TArray<TPair<FString, float>> SelectedRegion;

	float PlayerEnteringServerDelay;

	bool IsSteamLaunch;

	FString GameReleaseVersion;
	FString SdkVersion;
	FString SteamAppID;

	FString StatisticCodeKill;
	FString StatisticCodeMatch;
	FString StatisticCodeDeath;
	FString StatisticCodeMVP;

	FString ItemImageSetAs;

	FString MessageNotificationTopic;

	ShooterGameTelemetryEvents TelemetryEvents;
	float TelemetryHeartbeatInterval = 99;

	bool FindArgFromCommandLine(FString Arg);

public:

	TArray<GameModeData> AvailableGameMode;

	ShooterGameConfig(ShooterGameConfig const&) = delete;
	void operator=(ShooterGameConfig const&) = delete;

	void SetServerLatencies(TArray<TPair<FString, float>> value);
	void SelectRegion(TPair<FString, float> value);

	void PopulateGameMode();

	const int32 &ServerPort_;
	const FString &LocalServerIP_;
	const FString &LocalServerName_;
	const FString &DsLocalModeCommandLineArg_;
	const FString &ServerImageVersion_;
	const bool &IsLocalMode_;
	const int &ServerHeartbeatInterval_;
	const TArray<TPair<FString, float>> &ServerLatencies_;
	const TArray<TPair<FString, float>> &SelectedRegion_;

	const float &PlayerEnteringServerDelay_; //Second

	const bool &IsSteamLaunch_;

	const FString &GameReleaseVersion_;
	const FString &SdkVersion_;
	const FString &SteamAppID_;

	const FString &StatisticCodeKill_;
	const FString &StatisticCodeMatch_;
	const FString &StatisticCodeDeath_;
	const FString &StatisticCodeMVP_;

	const FString &ItemImageSetAs_;

	const FString &MessageNotificationTopic_;

	const ShooterGameTelemetryEvents& TelemetryEvents_;
	const float& TelemetryHeartbeatInterval_;
};
