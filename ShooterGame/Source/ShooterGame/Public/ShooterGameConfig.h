#pragma once
#include "CoreGlobals.h"
#include "Models/AccelByteQosModels.h"

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

	FString StatisticCodeKill;
	FString StatisticCodeAssist;
	FString StatisticCodeDeath;

	FString ItemImageSetAs;

public:
	ShooterGameConfig(ShooterGameConfig const&) = delete;
	void operator=(ShooterGameConfig const&) = delete;

	void SetServerLatencies(TArray<TPair<FString, float>> value);

	const int32 &ServerPort_;
	const FString &LocalServerIP_;
	const FString &LocalServerName_;
	const FString &DsLocalModeCommandLineArg_;
	const FString &ServerImageVersion_;
	const bool &IsLocalMode_;
	const int &ServerHeartbeatInterval_;
	const TArray<TPair<FString, float>> &ServerLatencies_;

	const FString &StatisticCodeKill_;
	const FString &StatisticCodeAssist_;
	const FString &StatisticCodeDeath_;

	const FString &ItemImageSetAs_;
};