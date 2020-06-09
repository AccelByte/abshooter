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
	SelectedRegion_(SelectedRegion),
	PlayerEnteringServerDelay_(PlayerEnteringServerDelay),
	GameReleaseVersion_(GameReleaseVersion),
	SdkVersion_(SdkVersion),
	StatisticCodeKill_(StatisticCodeKill),
	StatisticCodeMatch_(StatisticCodeMatch),
	StatisticCodeDeath_(StatisticCodeDeath),
	StatisticCodeMVP_(StatisticCodeMVP),
	ItemImageSetAs_(ItemImageSetAs),
	MessageNotificationTopic_(MessageNotificationTopic),
	TelemetryEvents_(TelemetryEvents),
	TelemetryHeartbeatInterval_(TelemetryHeartbeatInterval)
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

	FString ACCELBYTE_CONFIG_VERSION_SECTION = "/Script/ShooterGame.AccelByteConfig.Versions";
	GConfig->GetString(*ACCELBYTE_CONFIG_VERSION_SECTION, TEXT("GameReleaseVersion"), GameReleaseVersion, GGameIni);
	GConfig->GetString(*ACCELBYTE_CONFIG_VERSION_SECTION, TEXT("SdkVersion"), SdkVersion, GGameIni);

	FString ACCELBYTE_CONFIG_ANALYTICS_SECTION = "/Script/ShooterGame.AccelByteConfig.Analytics";
	GConfig->GetString(*ACCELBYTE_CONFIG_ANALYTICS_SECTION, TEXT("event_player_logged_in"), TelemetryEvents.LoggedIn, GGameIni);
	GConfig->GetString(*ACCELBYTE_CONFIG_ANALYTICS_SECTION, TEXT("event_player_logged_out"), TelemetryEvents.LoggedOut, GGameIni);
	GConfig->GetString(*ACCELBYTE_CONFIG_ANALYTICS_SECTION, TEXT("event_player_match_start"), TelemetryEvents.MatchStart, GGameIni);
	GConfig->GetString(*ACCELBYTE_CONFIG_ANALYTICS_SECTION, TEXT("event_player_match_end"), TelemetryEvents.MatchEnd, GGameIni);
	GConfig->GetString(*ACCELBYTE_CONFIG_ANALYTICS_SECTION, TEXT("event_player_heartbeat"), TelemetryEvents.Heartbeat, GGameIni);
	GConfig->GetString(*ACCELBYTE_CONFIG_ANALYTICS_SECTION, TEXT("event_player_item_equip"), TelemetryEvents.ItemEquip, GGameIni);
	GConfig->GetFloat(*ACCELBYTE_CONFIG_ANALYTICS_SECTION, TEXT("heartbeat_interval"), TelemetryHeartbeatInterval, GGameIni);

	PlayerEnteringServerDelay = ServerHeartbeatInterval + 4.0f;
}

void ShooterGameConfig::SetServerLatencies(TArray<TPair<FString, float>> value)
{
	ServerLatencies = value;
}

void ShooterGameConfig::SelectRegion(TPair<FString, float> value)
{
	SelectedRegion = TArray<TPair<FString, float>>{ value };
}