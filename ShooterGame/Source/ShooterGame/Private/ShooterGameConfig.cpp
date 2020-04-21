#include "ShooterGameConfig.h"
#include "Misc/CommandLine.h"
#include "GenericPlatform/GenericPlatformMisc.h"

ShooterGameConfig::ShooterGameConfig()
	:
	ServerPort_(ServerPort),
	LocalServerIP_(LocalServerIP),
	LocalServerName_(LocalServerName),
	DsLocalModeCommandLineArg_(DsLocalModeCommandLineArg),
	ServerImageVersion_(ServerImageVersion),
	IsLocalMode_(IsLocalMode),
	ServerHeartbeatInterval_(ServerHeartbeatInterval),
	ServerLatencies_(ServerLatencies),
	StatisticCodeKill_(StatisticCodeKill),
	StatisticCodeMatch_(StatisticCodeMatch),
	StatisticCodeDeath_(StatisticCodeDeath),
	StatisticCodeMVP_(StatisticCodeMVP),
	ItemImageSetAs_(ItemImageSetAs),
	MessageNotificationTopic_(MessageNotificationTopic)
{
	FString ACCELBYTE_CONFIG_SERVER_SECTION = "/Script/ShooterGame.AccelByteConfig.Server";

	GConfig->GetInt(*ACCELBYTE_CONFIG_SERVER_SECTION, TEXT("ServerPort"), ServerPort, GGameIni);
	GConfig->GetString(*ACCELBYTE_CONFIG_SERVER_SECTION, TEXT("LocalServerIP"), LocalServerIP, GGameIni);

	FString LocalServerNamePrefix;
	GConfig->GetString(*ACCELBYTE_CONFIG_SERVER_SECTION, TEXT("LocalServerNamePrefix"), LocalServerNamePrefix, GGameIni);
	LocalServerName = FString::Printf(TEXT("%s-%s"), *LocalServerNamePrefix, *FGenericPlatformMisc::GetDeviceId());

	GConfig->GetString(*ACCELBYTE_CONFIG_SERVER_SECTION, TEXT("DsLocalModeCommandLineArg"), DsLocalModeCommandLineArg, GGameIni);
	GConfig->GetString(*ACCELBYTE_CONFIG_SERVER_SECTION, TEXT("ServerImageVersion"), ServerImageVersion, GGameIni);
	GConfig->GetInt(*ACCELBYTE_CONFIG_SERVER_SECTION, TEXT("ServerHeartbeatInterval"), ServerHeartbeatInterval, GGameIni);

	GConfig->GetString(*ACCELBYTE_CONFIG_SERVER_SECTION, TEXT("StatisticCodeKill"), StatisticCodeKill, GGameIni);
	GConfig->GetString(*ACCELBYTE_CONFIG_SERVER_SECTION, TEXT("StatisticCodeMatch"), StatisticCodeMatch, GGameIni);
	GConfig->GetString(*ACCELBYTE_CONFIG_SERVER_SECTION, TEXT("StatisticCodeDeath"), StatisticCodeDeath, GGameIni);
	GConfig->GetString(*ACCELBYTE_CONFIG_SERVER_SECTION, TEXT("StatisticCodeMvp"), StatisticCodeMVP, GGameIni);

	auto cmdLineArgs = FCommandLine::Get();
	TArray<FString> tokens, switches;
	FCommandLine::Parse(FCommandLine::Get(), tokens, switches);
	IsLocalMode = tokens.Contains(TEXT("localds"));


	FString ACCELBYTE_CONFIG_STORE_SECTION = "/Script/ShooterGame.AccelByteConfig.Store";
	GConfig->GetString(*ACCELBYTE_CONFIG_STORE_SECTION, TEXT("ItemImageSetAs"), ItemImageSetAs, GGameIni);

	FString ACCELBYTE_CONFIG_NOTIFICATION_SECTION = "/Script/ShooterGame.AccelByteConfig.Notification";
	GConfig->GetString(*ACCELBYTE_CONFIG_NOTIFICATION_SECTION, TEXT("MessageNotificationTopic"), MessageNotificationTopic, GGameIni);
}

void ShooterGameConfig::SetServerLatencies(TArray<TPair<FString, float>> value)
{
	ServerLatencies = value;
}
