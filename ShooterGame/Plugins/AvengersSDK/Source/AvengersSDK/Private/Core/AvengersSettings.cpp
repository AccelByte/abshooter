// Copyright (c) 2018 - 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "Core/AvengersSettings.h"
#include "Core/AvengersRegistry.h"

UAvengersSettings::UAvengersSettings()
{
}

FString UAvengersBlueprintsSettings::GetBaseURL()
{
	return AccelByte::FAvengersRegistry::Settings.BaseURL;
}

FString UAvengersBlueprintsSettings::GetGameVersionID()
{
	return AccelByte::FAvengersRegistry::Settings.GameVersionID;
}

FString UAvengersBlueprintsSettings::GetNamespace()
{
	return AccelByte::FAvengersRegistry::Settings.Namespace;
}

bool UAvengersBlueprintsSettings::GetEnableProfiler()
{
	return AccelByte::FAvengersRegistry::Settings.bEnableProfiler;
}

bool UAvengersBlueprintsSettings::GetEnableCrashTracker()
{
	return AccelByte::FAvengersRegistry::Settings.bEnableCrashTracker;
}

bool UAvengersBlueprintsSettings::GetEnableProfilerWebServer()
{
	return AccelByte::FAvengersRegistry::Settings.bEnableProfilerWebServer;
}

void UAvengersBlueprintsSettings::SetBaseURL(const FString& BaseURL)
{
	AccelByte::FAvengersRegistry::Settings.BaseURL = BaseURL;
}

void UAvengersBlueprintsSettings::SetGameVersionID(const FString& GameVersionID)
{
	AccelByte::FAvengersRegistry::Settings.GameVersionID = GameVersionID;
}

void UAvengersBlueprintsSettings::SetNamespace(const FString& Namespace)
{
	AccelByte::FAvengersRegistry::Settings.Namespace = Namespace;
}

void UAvengersBlueprintsSettings::SetEnableProfiler(const bool& Enable)
{
	AccelByte::FAvengersRegistry::Settings.bEnableProfiler = Enable;
}

void UAvengersBlueprintsSettings::SetEnableCrashTracker(const bool& Enable)
{
	AccelByte::FAvengersRegistry::Settings.bEnableCrashTracker = Enable;
}

void UAvengersBlueprintsSettings::SetEnableProfilerWebServer(const bool& Enable)
{
	AccelByte::FAvengersRegistry::Settings.bEnableProfilerWebServer = Enable;
}

