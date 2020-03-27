#pragma once
#include "CoreGlobals.h"

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

public:
	ShooterGameConfig(ShooterGameConfig const&) = delete;
	void operator=(ShooterGameConfig const&) = delete;

	const int32 &ServerPort_;
	const FString &LocalServerIP_;
	const FString &LocalServerName_;
	const FString &DsLocalModeCommandLineArg_;
	const FString &ServerImageVersion_;
	const bool &IsLocalMode_;
	const int &ServerHeartbeatInterval_;
};