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
	FString DsLocalModeCommandLineArg;
	FString ServerImageVersion;

public:
	ShooterGameConfig(ShooterGameConfig const&) = delete;
	void operator=(ShooterGameConfig const&) = delete;

	const int32 &ServerPort_;
	const FString &LocalServerIP_;
	const FString &DsLocalModeCommandLineArg_;
	const FString &ServerImageVersion_;
};