// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "AvengersSDKModule.h"
#include "Runtime/Core/Public/Misc/CoreDelegates.h"

#include "Core/AvengersRegistry.h"
#include "Core/AvengersSettings.h"
#include "Api/AvengersMicroProfile.h"
#include "Api/AvengersCrashTracker.h"

#if WITH_EDITOR
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#endif

#define LOCTEXT_NAMESPACE "FAccelbyteSDK"

class FAccelByteAvengersSDKModule : public IAccelByteAvengersSDKModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    // For registering settings in UE4 editor
    void RegisterSettings();
    void UnregisterSettings();
    bool LoadSettingsFromConfigUobject();
    void OnEndFrameRT();
    void WorldCreated(UWorld* world);
    void WorldDestroyed(UWorld* world);
    void UpdateSessionID(FString SessionID);

    virtual void Tick(float DeltaTime);
    virtual void BeginPlay(APlayerController* PlayerController);
    virtual void EndPlay();


private:
    FAvengersMicroProfile* MicroProfile;
    UAvengersCrashTracker* CrashTracker;
};

void FAccelByteAvengersSDKModule::StartupModule()
{
    RegisterSettings();
    LoadSettingsFromConfigUobject();

    MicroProfile = new FAvengersMicroProfile();
    CrashTracker = NewObject<UAvengersCrashTracker>();

    FCoreDelegates::OnEndFrameRT.AddRaw(this, &FAccelByteAvengersSDKModule::OnEndFrameRT);
    FWorldDelegates::OnPostWorldCreation.AddRaw(this, &FAccelByteAvengersSDKModule::WorldCreated);
    FWorldDelegates::OnPreWorldFinishDestroy.AddRaw(this, &FAccelByteAvengersSDKModule::WorldDestroyed);

    MicroProfile->OnSessionIDReady.BindLambda([&](const FString& SessionID) {
        this->UpdateSessionID(SessionID);
    });
}

void FAccelByteAvengersSDKModule::ShutdownModule()
{
    delete MicroProfile;
    // does not need to delete CrashTracker, CrashTracker is UObject, GC
    UnregisterSettings();
}

void FAccelByteAvengersSDKModule::RegisterSettings()
{
#if WITH_EDITOR
    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings(TEXT("Project"), TEXT("Plugins"), TEXT("AccelByte Avengers SDK"),
            FText::FromName(TEXT("AccelByte Avengers SDK")),
            FText::FromName(TEXT("Setup your plugin.")),
            GetMutableDefault<UAvengersSettings>()
        );
        if (SettingsSection.IsValid())
        {
            SettingsSection->OnModified().BindRaw(this, &FAccelByteAvengersSDKModule::LoadSettingsFromConfigUobject);
        }
    }
#endif
}

void FAccelByteAvengersSDKModule::UnregisterSettings()
{
#if WITH_EDITOR
    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        SettingsModule->UnregisterSettings(TEXT("Project"), TEXT("Plugins"), TEXT("AccelByte Avengers SDK"));
    }
#endif
}

void FAccelByteAvengersSDKModule::OnEndFrameRT()
{
    if (AccelByte::FAvengersRegistry::Settings.bEnableProfiler)
    {
        MicroProfile->RenderTick();
    }

    if (AccelByte::FAvengersRegistry::Settings.bEnableCrashTracker)
    {
        CrashTracker->RenderTick();
    }
}

void FAccelByteAvengersSDKModule::WorldCreated(UWorld* world)
{
    if (AccelByte::FAvengersRegistry::Settings.bEnableCrashTracker)
    {
        CrashTracker->WorldCreated(world);
    }
}
void FAccelByteAvengersSDKModule::WorldDestroyed(UWorld* world)
{
    if (AccelByte::FAvengersRegistry::Settings.bEnableCrashTracker)
    {
        CrashTracker->WorldDestroyed(world);
    }
}

void FAccelByteAvengersSDKModule::UpdateSessionID(FString SessionID)
{
    CrashTracker->SetSessionID(SessionID);
}

bool FAccelByteAvengersSDKModule::LoadSettingsFromConfigUobject()
{
	AccelByte::FAvengersRegistry::Settings.BaseURL = GetDefault<UAvengersSettings>()->BaseURL;
	AccelByte::FAvengersRegistry::Settings.GameVersionID = GetDefault<UAvengersSettings>()->GameVersionID;
	AccelByte::FAvengersRegistry::Settings.Namespace = GetDefault<UAvengersSettings>()->Namespace;
	AccelByte::FAvengersRegistry::Settings.bEnableCrashTracker = GetDefault<UAvengersSettings>()->bEnableCrashTracker;
	AccelByte::FAvengersRegistry::Settings.bEnableProfiler = GetDefault<UAvengersSettings>()->bEnableProfiler;
	AccelByte::FAvengersRegistry::Settings.bEnableProfilerWebServer = GetDefault<UAvengersSettings>()->bEnableProfilerWebServer;

    if (!GConfig->GetString(TEXT("/Script/EngineSettings.GeneralProjectSettings"), 
        TEXT("ProjectID"), 
		AccelByte::FAvengersRegistry::Settings.ProjectID,
        GGameIni))
    {
        UE_LOG(LogAvengers, Error, TEXT("FAvengersSDK: Missing ProjectID= in [/Script/EngineSettings.GeneralProjectSettings] of DefaultGame.ini"));
        return false;
    }
    return true;
}

void FAccelByteAvengersSDKModule::Tick(float DeltaTime)
{
    if (AccelByte::FAvengersRegistry::Settings.bEnableProfiler)
    {
        MicroProfile->Tick(DeltaTime);
    }

    if (AccelByte::FAvengersRegistry::Settings.bEnableCrashTracker)
    {
        CrashTracker->Tick(DeltaTime);
    }
}

void FAccelByteAvengersSDKModule::BeginPlay(APlayerController* PlayerController)
{
    if (AccelByte::FAvengersRegistry::Settings.bEnableProfiler)
    {
        // microprofile still has an issue if being played on the editor
        MicroProfile->BeginPlay(PlayerController);
    }

    if (AccelByte::FAvengersRegistry::Settings.bEnableCrashTracker)
    {
        CrashTracker->BeginPlay(PlayerController);
    }
}
void FAccelByteAvengersSDKModule::EndPlay()
{
    if (AccelByte::FAvengersRegistry::Settings.bEnableProfiler)
    {
        MicroProfile->EndPlay();
    }

    if (AccelByte::FAvengersRegistry::Settings.bEnableCrashTracker)
    {
        CrashTracker->EndPlay();
    }
}


#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FAccelByteAvengersSDKModule, AvengersSDK)
