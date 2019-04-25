// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "AvengersMicroProfile.h"
#include "Engine.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformDriver.h"
#include "Core/AvengersRegistry.h"
#include "Core/AvengersSettings.h"
#include "Core/AvengersAsyncTaskManager.h"
#include "Core/AvengersHTTP.h"
#include "Models/AvengersClientDesc.h"
#include "Models/AvengersMPConfigs.h"
#include "ThirdParty/MicroProfile/microprofile.h"

extern void MicroProfileInstrumentWithoutSymbols(const char** pModules, const char** pSymbols, uint32_t nNumSymbols);

FAvengersMicroProfile::FAvengersMicroProfile()
{
    OnlineAsyncTaskThread = nullptr;
    OnlineAsyncTaskThreadRunnable = nullptr;
    bIsDumpReady = true;
    RenderTimeThreshold = 0.05; // 50 ms  ( if frame time longer than 50ms, it will start to capture )
    bIsFirstFrametimeDrop = true;
    FrametimeDropInterval = 0;
    DumpingIntervalTh = 60;
    FrametimeDropIntervalTh = 10;
    LastDump = 0;
    bIsStillHasPendingRequestSessionID = false;
}

FAvengersMicroProfile::~FAvengersMicroProfile()
{
    if (OnlineAsyncTaskThread)
    {
        // Destroy the online async task thread
        delete OnlineAsyncTaskThread;
        OnlineAsyncTaskThread = nullptr;
    }

    if (OnlineAsyncTaskThreadRunnable)
    {
        delete OnlineAsyncTaskThreadRunnable;
        OnlineAsyncTaskThreadRunnable = nullptr;
    }

    if (GEngine) FTicker::GetCoreTicker().RemoveTicker(SendTickDelegateHandle);
    MicroProfileShutdown();
}

void FAvengersMicroProfile::BeginPlay(APlayerController* PlayerController)
{
    // Online task manager for future use
#if 0
    OnlineAsyncTaskThreadRunnable = new FAsyncTaskManagerJustice();
    check(OnlineAsyncTaskThreadRunnable);
    OnlineAsyncTaskThread = FRunnableThread::Create(OnlineAsyncTaskThreadRunnable, TEXT("AvengersOnlineAsyncTaskThreadSteam"), 128 * 1024, TPri_Normal);
    check(OnlineAsyncTaskThread);
#endif

    // MicroProfile initialization
    MicroProfileSetWebServerEnable(AccelByte::FAvengersRegistry::Settings.bEnableProfilerWebServer);
    NewSession();
    MicroProfileSetEnableAllGroups(true);
    bIsStillHasPendingRequestSessionID = false;

    SendTickDelegate = FTickerDelegate::CreateRaw(this, &FAvengersMicroProfile::SendTick);
    SendTickDelegateHandle = FTicker::GetCoreTicker().AddTicker(SendTickDelegate, 10);
}

void FAvengersMicroProfile::EndPlay()
{
    if (GEngine) FTicker::GetCoreTicker().RemoveTicker(SendTickDelegateHandle);    
}

void FAvengersMicroProfile::Tick(const float &DeltaTime)
{
    // Game Tick
    if (bIsDumpReady)
    {
        if (DeltaTime > RenderTimeThreshold && !bIsFirstFrametimeDrop)
        {
            FrametimeDropInterval++;
            if (FrametimeDropInterval >= FrametimeDropIntervalTh)
            {
                CaptureDump();
                bIsDumpReady = false;
                LastDump = FPlatformTime::Seconds();
                FrametimeDropInterval = 0;
            }
        }
        else
        {
            FrametimeDropInterval = 0;
            bIsFirstFrametimeDrop = false;
        }
    }
    else
    {
        double CurrentDump = FPlatformTime::Seconds();
        double DumpInterval = CurrentDump - LastDump;
        if (DumpInterval >= (double)DumpingIntervalTh)
        {
            bIsDumpReady = true;
        }
    }
}

void FAvengersMicroProfile::NewSession()
{
    FAvengersClientDesc Desc;
    Desc.ClientID = TEXT("6414faca-cee8-4de4-90a9-140d79fd480d"); // this will be deprecated
    Desc.Country = TEXT("ID");
    Desc.CPU = FWindowsPlatformMisc::GetCPUBrand();
    Desc.GameVersionID = AccelByte::FAvengersRegistry::Settings.GameVersionID;
    Desc.GPU = FWindowsPlatformMisc::GetPrimaryGPUBrand();
    Desc.GPUDriver = FWindowsPlatformMisc::GetGPUDriverInfo(GRHIAdapterName).UserDriverVersion;
    Desc.IPAddress = TEXT("127.0.0.1"); // this will be deprecated
    Desc.Locale = TEXT("en-us");
    Desc.Memory = 3000;
    Desc.OperatingSystem = FWindowsPlatformMisc::GetOSVersion();
    Desc.OperatingVersion = FWindowsPlatformMisc::GetOSVersion();
    Desc.Renderer = TEXT("MockRenderer");
    Desc.SessionStartedAt = FDateTime::UtcNow().ToIso8601();
#if _WIN64
    Desc.SystemArchitecture = TEXT("64-Bit");
#elif _WIN32
    Desc.SystemArchitecture = TEXT("32-Bit");
#endif

    bIsStillHasPendingRequestSessionID = true; // state that we still have one pending request to create new session
    AccelByte::FAvengersHTTP::NewSession(Desc, AccelByte::THandler<FAvengersMPConfigs>::CreateLambda([this](const FAvengersMPConfigs& Result)
    {
        UE_LOG(LogAvengers, Log, TEXT("FAvengersMicroProfile: SessionID: %s"), *Result.SessionID);
        if (!Result.SessionID.IsEmpty())
        {
            bIsReady = true;
            bIsStillHasPendingRequestSessionID = false; // save to create new request for session
            SessionID = Result.SessionID;
            OnSessionIDReady.ExecuteIfBound(SessionID);
        }

        // check if the config contains dynamic instrumentation
        for (int i = 0; i < Result.GameSymbols.Num(); i++)
        {
            FAvengersGameSymbol GameSymbol = Result.GameSymbols[i];
            UE_LOG(LogAvengers, 
                Log, 
                TEXT("FAvengersMicroProfile: GameSymbol: %s -> %s"), 
                *Result.GameSymbols[i].module_id,
                *Result.GameSymbols[i].symbol_name);

            MicroProfileInstrumentWithoutSymbols2(
                TCHAR_TO_ANSI(*GameSymbol.module_id), 
                TCHAR_TO_ANSI(*GameSymbol.symbol_name));
            bEnableDynamicIntrument = true;
        }
    }), AccelByte::FErrorHandler::CreateLambda([this](int32 ErrorCode, const FString& ErrorMessage)
    {
        bIsReady = false;
        bIsStillHasPendingRequestSessionID = false; // save to create new request for session
        UE_LOG(LogAvengers, Log, TEXT("Cannot create new session: Code %d, Message: %s"), ErrorCode, *ErrorMessage);
    }));

}

void FAvengersMicroProfile::RenderTick()
{
    if (bIsReady)
    {
        MicroProfileFlip(nullptr);
    }
}

bool FAvengersMicroProfile::SendTick(float DeltaTime)
{
    FAvengersFrametimeData FrametimeData;
    FrametimeData.timestamp_start = FDateTime::UtcNow().ToIso8601();
    if (bIsReady)
    {
        UE_LOG(LogAvengers, Log, TEXT("FAvengersMicroProfile: Sending frametime."));
        float fTime;
        float fTimeDI;
        TArray<FAvengersFrametime> Data;        
        FAvengersFrametime Frametime;
        FAvengersDITime DITime;
        while (MicroProfileJusticeBufferGet(&fTime, &fTimeDI))
        {
            Frametime.frametime = (int)fTime;
            Data.Push(Frametime);
        }
        // sending Frametime
        FrametimeData.session_id = SessionID;
        FrametimeData.payload = Data;

        AccelByte::FAvengersHTTP::SendFrametime(FrametimeData, AccelByte::FVoidHandler::CreateLambda([this]() {
            UE_LOG(LogAvengers, Log, TEXT("Frametime telemetry sent."));
        }), AccelByte::FErrorHandler::CreateLambda([this](int32 ErrorCode, const FString& ErrorMessage)
        {            
            UE_LOG(LogAvengers, Log, TEXT("Cannot send frametime telemetry: Code %d, Message: %s"), ErrorCode, *ErrorMessage);
        }));
    }
    else 
    {
        if (!bIsStillHasPendingRequestSessionID)
        {
            UE_LOG(LogAvengers, Log, TEXT("Retry to create new session..."));
            NewSession();
        }
    }
    return true;
}

void FAvengersMicroProfile::CaptureDump()
{
    FString HtmlDump;
    auto MicroProfileWriteBuffer = [&HtmlDump](void* Handle, size_t nSize, const char* pData)
    {
        HtmlDump.Append(UTF8_TO_TCHAR(pData));
    };
    HtmlDump.Empty();
    MicroProfileDumpHtml2(MicroProfileWriteBuffer, nullptr, MICROPROFILE_WEBSERVER_MAXFRAMES, nullptr);

    FAvengersDumpConfig DumpConfig;
    DumpConfig.FrameCaptured = 30;
    DumpConfig.SessionID = SessionID;

    AccelByte::FAvengersHTTP::RequestUploadDump(DumpConfig, AccelByte::THandler<FAvengersDumpResponse>::CreateLambda([this, &HtmlDump](const FAvengersDumpResponse& Result) {
        // put our html to S3
		AccelByte::FAvengersHTTP::SendHtmlDump(Result.UploadURL, HtmlDump, AccelByte::FVoidHandler::CreateLambda([this]() {
            UE_LOG(LogAvengers, Log, TEXT("Html dump sent."));
        }), AccelByte::FErrorHandler::CreateLambda([this](int32 ErrorCode, const FString& ErrorMessage)
        {
            UE_LOG(LogAvengers, Log, TEXT("Cannot send frametime telemetry: Code %d, Message: %s"), ErrorCode, *ErrorMessage);
        }));

    }), AccelByte::FErrorHandler::CreateLambda([this](int32 ErrorCode, const FString& ErrorMessage)
    {
        UE_LOG(LogAvengers, Log, TEXT("Cannot send frametime telemetry: Code %d, Message: %s"), ErrorCode, *ErrorMessage);
    }));
}