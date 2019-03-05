// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "CrashTrackerPrivate.h"
#include "CoreMinimal.h"
#include "Engine/GameEngine.h"
#include "EngineBuildSettings.h"
#include "GameFramework/GameModeBase.h"
#include "GenericPlatform/GenericPlatformCrashContext.h"
#include "Windows/WindowsPlatformCrashContext.h"

DEFINE_LOG_CATEGORY(LogCrashTracker);

void FCrashTrackerModule::StartupModule()
{
    SharedMemoryHandle = nullptr;
    StagingTexture = nullptr;
    PlayerController = nullptr;
    SharedData = nullptr;

    if (FSlateApplication::IsInitialized())
    {
        FSlateRenderer::FOnBackBufferReadyToPresent OnBackBufferReadyDelegate;
        OnBackBufferReadyDelegate.BindRaw(this, &FCrashTrackerModule::OnBackBufferReady_RenderThread);
        FSlateApplication::Get().GetRenderer()->OnBackBufferReadyToPresent() = OnBackBufferReadyDelegate;
        FSlateApplication::Get().GetRenderer()->OnPreResizeWindowBackBuffer().AddRaw(this, &FCrashTrackerModule::OnPreResizeWindowBackbuffer);
    }
    FGameModeEvents::GameModePostLoginEvent.AddRaw(this, &FCrashTrackerModule::OnGameModePostLogin);
}


void FCrashTrackerModule::UpdateViewport(FSceneViewport* Viewport)
{

}
void FCrashTrackerModule::OnBackBufferReady_RenderThread(const FTexture2DRHIRef& BackBuffer)
{   
    check(IsInRenderingThread());
    if (GIsEditor)
        return;

    ID3D11Texture2D* ResolvedBackBufferDX11 = (ID3D11Texture2D*)(GetD3D11TextureFromRHITexture(BackBuffer)->GetResource());
    ID3D11Device* d3dDevice = nullptr;
    if (ResolvedBackBufferDX11 != nullptr)
    {
        HRESULT hr;

        // First verify that we can map the texture
        D3D11_TEXTURE2D_DESC desc;
        ResolvedBackBufferDX11->GetDesc(&desc);
        ResolvedBackBufferDX11->GetDevice(&d3dDevice);
        ID3D11DeviceContext* d3dContext;
        d3dDevice->GetImmediateContext(&d3dContext);

        if (StagingTexture == nullptr) 
        {
            D3D11_TEXTURE2D_DESC desc2;
            desc2.Width = desc.Width;
            desc2.Height = desc.Height;
            desc2.MipLevels = desc.MipLevels;
            desc2.ArraySize = desc.ArraySize;
            desc2.Format = desc.Format;
            desc2.SampleDesc = desc.SampleDesc;
            desc2.Usage = D3D11_USAGE_DEFAULT;
            desc2.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            desc2.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
            desc2.MiscFlags = D3D11_RESOURCE_MISC_SHARED;

            hr = d3dDevice->CreateTexture2D(&desc2, nullptr, &StagingTexture);
            if (FAILED(hr)) {
                //throw MyException::Make(hr, L"Failed to create staging texture");
                UE_LOG(LogCrashTracker, Log, TEXT("Failed to create staging texture"));
            }

            IDXGIResource* pOtherResource(NULL);
            hr = StagingTexture->QueryInterface(__uuidof(IDXGIResource), (void**)&pOtherResource);
            HANDLE TextureSharedHandle;
            pOtherResource->GetSharedHandle(&TextureSharedHandle);

            // share the address
            if (SharedMemoryHandle == nullptr)
            {
                SharedMemoryHandle = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(SharedMemoryData), "hendra-shared");
                if (SharedMemoryHandle != NULL)
                {
                    SharedData = (SharedMemoryData*)MapViewOfFile(SharedMemoryHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedMemoryData));
                    if (SharedData != NULL)
                    {
                        SharedData->SharedTexture = TextureSharedHandle;
                        SharedData->KeyState = 0;

                        // start the process
                        FString PluginDir = FPaths::ProjectPluginsDir();
                        FString HelperExePath = PluginDir /  + "CrashTracker/Binaries/Win64/CrashClientHelper.exe";

                        FWindowsPlatformCrashContext CrashContext; // this will increment the last 5 digit
                        TCHAR CrashGUID[FGenericCrashContext::CrashGUIDLength];
                        CrashContext.GetUniqueCrashName(CrashGUID, FGenericCrashContext::CrashGUIDLength);
                        const FString AppName = CrashContext.GetCrashGameName();
                        FString CrashFolder = FPaths::Combine(*FPaths::ProjectSavedDir(), TEXT("Crashes"), CrashGUID);
                        FString CrashFolderAbsolute = IFileManager::Get().ConvertToAbsolutePathForExternalAppForWrite(*CrashFolder);
                        

                        // The code above will return something like:
                        // WindowsNoEditor\AccelMania\Saved\Crashes\UE4CC-Windows-D117B9D14577F0061372F582D74764A4_0000
                        // but the actual crash will be saved on 
                        // WindowsNoEditor\AccelMania\Saved\Crashes\UE4CC-Windows-D117B9D14577F0061372F582D74764A4_0001
                        // we need the GUID and increment the counter number after _

                        // Hackish, there is no proper way to get absoute crash folder, without incrementing folder name
                        FString BaseFolder = CrashFolderAbsolute.Left(CrashFolderAbsolute.Len() - 5);
                        FString Number = CrashFolderAbsolute.Right(4);
                        int NextNumber = FCString::Atoi(*Number) + 1;

                        FString NextCrashFolder = FString::Printf(TEXT("%s_%04i"), *BaseFolder, NextNumber);
                        FString CrashConfigFile = IFileManager::Get().ConvertToAbsolutePathForExternalAppForWrite(CrashContext.GetCrashConfigFilePath());
                        FString ProcessArgs = FString::Printf(TEXT("-o \"%s\" -c \"%s\""), *NextCrashFolder, *CrashConfigFile);

                        UE_LOG(LogCrashTracker, Log, TEXT("NextCrashFolder: %s"), *NextCrashFolder);
                        UE_LOG(LogCrashTracker, Log, TEXT("Crash Client Config: %s"), *CrashConfigFile);
                        UE_LOG(LogCrashTracker, Log, TEXT("Start the helper process %s"), *HelperExePath);
                        FProcHandle Proc = FPlatformProcess::CreateProc(*HelperExePath, *ProcessArgs, true, false, false, nullptr, 0, nullptr, nullptr);
                        if (!Proc.IsValid())
                        {
                            UE_LOG(LogCrashTracker, Log, TEXT("Opening file (%s) at a specific line failed."), *HelperExePath);
                            FPlatformProcess::CloseProc(Proc);
                        }
                    }
                }
            }
        }

        // check for all key down, pooling method
        if (PlayerController != nullptr && PlayerController->IsValidLowLevel())
        {
            if (PlayerController->IsInputKeyDown(EKeys::W)) // 1
            {
                SharedData->KeyState |= 1UL << 0;
            }
            else
            {
                SharedData->KeyState &= ~(1UL << 0);
            }

            if (PlayerController->IsInputKeyDown(EKeys::A))  // 2
            {
                SharedData->KeyState |= 1UL << 1;
            }
            else
            {
                SharedData->KeyState &= ~(1UL << 1);
            }

            if (PlayerController->IsInputKeyDown(EKeys::S)) // 4
            {
                SharedData->KeyState |= 1UL << 2;
            }
            else
            {
                SharedData->KeyState &= ~(1UL << 2);
            }


            if (PlayerController->IsInputKeyDown(EKeys::D)) //8
            {
                SharedData->KeyState |= 1UL << 3;
            }
            else
            {
                SharedData->KeyState &= ~(1UL << 3);
            }

            if (PlayerController->IsInputKeyDown(EKeys::SpaceBar))  // 16
            {
                SharedData->KeyState |= 1UL << 4;
            }
            else
            {
                SharedData->KeyState &= ~(1UL << 4);
            }

            if (PlayerController->IsInputKeyDown(EKeys::LeftMouseButton))   //32
            {
                SharedData->KeyState |= 1UL << 5;
            }
            else
            {
                SharedData->KeyState &= ~(1UL << 5);
            }

            if (PlayerController->IsInputKeyDown(EKeys::MiddleMouseButton))   //64
            {
                SharedData->KeyState |= 1UL << 6;
            }
            else
            {
                SharedData->KeyState &= ~(1UL << 6);
            }

            if (PlayerController->IsInputKeyDown(EKeys::RightMouseButton))   //128
            {
                SharedData->KeyState |= 1UL << 7;
            }
            else
            {
                SharedData->KeyState &= ~(1UL << 7);
            }
        }
		else
		{
			//if (GEngine->GetWorld()->IsValidLowLevel())
			//{
			//	PlayerController = GEngine->GetFirstLocalPlayerController(GEngine->GetWorld());
			//}
		}

        SharedData->Tick = GetTickCount();
        // copy the texture to a staging resource
        d3dContext->CopyResource(StagingTexture, ResolvedBackBufferDX11);       
    }
}
void FCrashTrackerModule::OnPreResizeWindowBackbuffer(void* BackBuffer)
{
}
void FCrashTrackerModule::OnPreResizeWindowBackbuffer_RenderThread()
{
}
void FCrashTrackerModule::OnGameModePostLogin(AGameModeBase* GameMode, APlayerController* NewPlayer)
{
	if (PlayerController == nullptr)
	{
		PlayerController = NewPlayer;


		if (!PlayerController->IsValidLowLevel())
		{
			if (GEngine->GetWorld()->IsValidLowLevel())
			{
				PlayerController = GEngine->GetFirstLocalPlayerController(GEngine->GetWorld());
			}
		}



	}
}

void FCrashTrackerModule::ShutdownModule()
{
    if (FSlateApplication::IsInitialized())
    {
        FSlateApplication::Get().GetRenderer()->OnBackBufferReadyToPresent().Unbind();
        FSlateApplication::Get().GetRenderer()->OnPreResizeWindowBackBuffer().RemoveAll(this);
    }

    if(SharedData != nullptr)
        UnmapViewOfFile(SharedData);

    if(SharedMemoryHandle !=nullptr)
        CloseHandle(SharedMemoryHandle);

    if(StagingTexture != nullptr)
        StagingTexture->Release();
}

IMPLEMENT_MODULE(FCrashTrackerModule, CrashTracker);
