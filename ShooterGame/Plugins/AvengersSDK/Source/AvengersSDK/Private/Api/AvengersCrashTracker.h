// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "Engine/GameEngine.h"
#include "EngineBuildSettings.h"
#include "GameFramework/GameModeBase.h"
#include "GenericPlatform/GenericPlatformCrashContext.h"
#include "Windows/WindowsPlatformCrashContext.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "RenderCore.h"
#include "RenderResource.h"
#include "SlateBasics.h"
#include "EngineUtils.h"

#include "Core/AvengersLog.h"


#if defined PLATFORM_WINDOWS
// Disable macro redefinition warning for compatibility with Windows SDK 8+
#pragma warning(push)
#pragma warning(disable : 4005)	// macro redefinition
#include "Windows/AllowWindowsPlatformTypes.h"
//#include <wrl.h>
#include <d3d11.h>
#include "Runtime/Windows/D3D11RHI/Public/D3D11State.h"
#include "Runtime/Windows/D3D11RHI/Public/D3D11Resources.h"
#include "Windows/HideWindowsPlatformTypes.h"
#pragma warning(pop)
#endif


#include "AvengersCrashTracker.generated.h"

struct SharedMemoryData
{
	DWORD Tick;
	HANDLE SharedTexture;
	UINT64 KeyState;
    UINT8  NumKey;
    char   KeyNames[64][255]; // need more optimization
};

/**
* @brief Exposes functions for CrashTracker related.
*/

UCLASS(Blueprintable, BlueprintType)
class AVENGERSSDK_API UAvengersCrashTracker: public UObject
{
public:
	GENERATED_BODY()

	UAvengersCrashTracker();
	~UAvengersCrashTracker();

	/** @brief Retrieve BackBuffer. */
	void Tick(const float &DeltaTime);
	void WorldCreated(UWorld* world);
	void WorldDestroyed(UWorld* world);
	void RenderTick();
	void BeginPlay(APlayerController* PlayerController);
    void EndPlay();
    void SetSessionID(FString NewSessionID) { SessionID = NewSessionID; }

private:

	/** @brief Game mode post log in.
	*
	* @param GameMode - Game mode base.
	* @param NewPlayer - Player controller.
	*/


	bool bInitialized;
    bool bSubProccessRunning;

	HANDLE SharedMemoryHandle; /**< Stores the Shared Memory handle. */
	ID3D11Texture2D* StagingTexture; /**< Stores the Staging Texture. */
	APlayerController* PlayerController; /**< Stores the Player Controller. */
	SharedMemoryData* SharedData; /**< Stores the SharedData. */
	UWorld* CurrentWorld = nullptr;
    TArray<FKey> KeyNames;    
    TArray<FString> ActionNames;
    bool bIsKeyNameReady;
    FString SessionID;

	TArray<FInputActionKeyMapping> ActionMaps; /**< The Active Action Maps */
	TArray<FInputAxisKeyMapping> AxisMaps; /**< The Active Axis Maps */
	bool bKeyrecordingInit;
	void InitializeKeyrecording(); /**< Function Fired to init the keyrecorder. */

	void InitializeSharedMemory(HANDLE TextureHandle);
	void StartHelperProcess();
	void SendKeyDataToSharedMemory();
};
