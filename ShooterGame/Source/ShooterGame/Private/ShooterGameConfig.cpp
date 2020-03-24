#include "ShooterGameConfig.h"

ShooterGameConfig::ShooterGameConfig()
	:
	ServerPort_(ServerPort),
	LocalServerIP_(LocalServerIP),
	DsLocalModeCommandLineArg_(DsLocalModeCommandLineArg),
	ServerImageVersion_(ServerImageVersion)
{
	FString ACCELBYTE_CONFIG_SERVER_SECTION = "/Script/ShooterGame.AccelByteConfig.Server";

	GConfig->GetInt(*ACCELBYTE_CONFIG_SERVER_SECTION, TEXT("ServerPort"), ServerPort, GGameIni);
	GConfig->GetString(*ACCELBYTE_CONFIG_SERVER_SECTION, TEXT("LocalServerIP"), LocalServerIP, GGameIni);
	GConfig->GetString(*ACCELBYTE_CONFIG_SERVER_SECTION, TEXT("DsLocalModeCommandLineArg"), DsLocalModeCommandLineArg, GGameIni);
	GConfig->GetString(*ACCELBYTE_CONFIG_SERVER_SECTION, TEXT("ServerImageVersion"), ServerImageVersion, GGameIni);
}