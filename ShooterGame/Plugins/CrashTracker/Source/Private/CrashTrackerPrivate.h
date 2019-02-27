// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CrashTracker.h"

/* Private dependencies
 *****************************************************************************/

#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "RenderCore.h"
#include "RenderResource.h"
#include "SlateBasics.h"

/* Private includes
 *****************************************************************************/
DECLARE_LOG_CATEGORY_EXTERN(LogCrashTracker, Log, All);

#if defined PLATFORM_WINDOWS
 // Disable macro redefinition warning for compatibility with Windows SDK 8+
#	pragma warning(push)
#		pragma warning(disable : 4005)	// macro redefinition
#		include "Windows/AllowWindowsPlatformTypes.h"
//#       include <wrl.h>
#			include <d3d11.h>
#			include "D3D11State.h"
#			include "D3D11Resources.h"
#		include "Windows/HideWindowsPlatformTypes.h"
#	pragma warning(pop)
#endif

 /*-----------------------------------------------------------------------------
     Stat declarations.
 -----------------------------------------------------------------------------*/
DECLARE_STATS_GROUP(TEXT("Video capture stat"), STATGROUP_CrashTracker, STATCAT_Advance);
DECLARE_CYCLE_STAT(TEXT("Total Time"), STAT_TotalTime, STATGROUP_CrashTracker);
DECLARE_CYCLE_STAT(TEXT("Send Frame To Compressor"), STAT_SendFrameToCompressor, STATGROUP_CrashTracker);
DECLARE_CYCLE_STAT(TEXT("Wait For Previous Frame To Compress"), STAT_WaitForPreviousFrameToCompress, STATGROUP_CrashTracker);
DECLARE_CYCLE_STAT(TEXT("Map Staging Buffer"), STAT_MapStagingBuffer, STATGROUP_CrashTracker);
DECLARE_CYCLE_STAT(TEXT("Generate Capture Buffer"), STAT_GenerateCaptureBuffer, STATGROUP_CrashTracker);
DECLARE_CYCLE_STAT(TEXT("Unmap Staging Buffer"), STAT_UnmapStagingBuffer, STATGROUP_CrashTracker);

struct SharedMemoryData
{
    DWORD Tick;
    HANDLE SharedTexture;
    UINT8 KeyState;
};

class CRASHTRACKER_API FCrashTrackerModule
	: public ICrashTrackerModule
{
public:

	// IModuleInterface interface

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

public:



private:
    HANDLE SharedMemoryHandle;
    ID3D11Texture2D* StagingTexture;
    APlayerController* PlayerController;
    SharedMemoryData* SharedData;

    void UpdateViewport(FSceneViewport* Viewport);
    void OnBackBufferReady_RenderThread(const FTexture2DRHIRef& BackBuffer);
    void OnPreResizeWindowBackbuffer(void* BackBuffer);
    void OnPreResizeWindowBackbuffer_RenderThread();
    void OnGameModePostLogin(AGameModeBase* GameMode, APlayerController* NewPlayer);
    void OnGameModeLogout(AGameModeBase* GameMode, AController* Exiting);


};