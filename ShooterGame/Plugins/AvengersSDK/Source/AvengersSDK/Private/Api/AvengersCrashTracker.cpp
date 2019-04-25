// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.

#include "AvengersCrashTracker.h"

UAvengersCrashTracker::UAvengersCrashTracker()
{
    SharedMemoryHandle = nullptr;
    StagingTexture = nullptr;
    PlayerController = nullptr;
    SharedData = nullptr;
    bInitialized = true;
    bIsKeyNameReady = false;
    bSubProccessRunning = false;
    SessionID = TEXT("");
}

UAvengersCrashTracker::~UAvengersCrashTracker()
{
    if (FSlateApplication::IsInitialized())
    {
        FSlateApplication::Get().GetRenderer()->OnPreResizeWindowBackBuffer().RemoveAll(this);
    }

    if (SharedData != nullptr)
    {
        UnmapViewOfFile(SharedData);
    }

    if (SharedMemoryHandle != nullptr)
    {
        CloseHandle(SharedMemoryHandle);
    }

    if (StagingTexture != nullptr)
    {
        StagingTexture->Release();
    }
}


void UAvengersCrashTracker::WorldCreated(UWorld* world)
{
	CurrentWorld = world;
	//Potentially Replace BP 
}

void UAvengersCrashTracker::WorldDestroyed(UWorld* world)
{
    PlayerController = nullptr;
    CurrentWorld = nullptr;
	ActionMaps.Empty();
	AxisMaps.Empty();
	bKeyrecordingInit = false;
}

void UAvengersCrashTracker::Tick(const float &DeltaTime)
{
    // called on Game thread tick
	if (!PlayerController->IsValidLowLevel() && CurrentWorld != 0)
	{
		for (TActorIterator<APlayerController> ActorItr(CurrentWorld); ActorItr; ++ActorItr)
		{
			PlayerController = *ActorItr;
			InitializeKeyrecording();
			break;
		}
	}
}

void UAvengersCrashTracker::InitializeKeyrecording()
{
	ActionMaps = PlayerController->PlayerInput->ActionMappings;
	AxisMaps = PlayerController->PlayerInput->AxisMappings;
	bKeyrecordingInit = true;

    KeyNames.Add(EKeys::LeftShift);
    KeyNames.Add(EKeys::RightShift);
    KeyNames.Add(EKeys::LeftAlt);
    KeyNames.Add(EKeys::RightAlt);
    KeyNames.Add(EKeys::LeftControl);
    KeyNames.Add(EKeys::RightControl);
    ActionNames.Add(TEXT("Shift Modifier"));
    ActionNames.Add(TEXT("Shift Modifier"));
    ActionNames.Add(TEXT("Alt Modifier"));
    ActionNames.Add(TEXT("Alt Modifier"));
    ActionNames.Add(TEXT("Ctrl Modifier"));
    ActionNames.Add(TEXT("Ctrl Modifier"));
   
    for (auto& map : AxisMaps)
	{
        KeyNames.Add(map.Key);
        ActionNames.Add(FString::Printf(TEXT("%s (%+.2f)"), *map.AxisName.ToString(), map.Scale));
        if (ActionNames.Num() == 64) // we currently only support 64 bit key mapping
        {
            break;
        }
	}
	for (auto& map : ActionMaps)
	{
        if (ActionNames.Num() == 64) // we currently only support 64 bit key mapping
        {
            break;
        }
        KeyNames.Add(map.Key);
        ActionNames.Add(map.ActionName.ToString());
	}
    bIsKeyNameReady = true;
}


void UAvengersCrashTracker::InitializeSharedMemory(HANDLE TextureHandle)
{
    SharedMemoryHandle = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(SharedMemoryData), "hendra-shared");
    if (SharedMemoryHandle != NULL)
    {
        SharedData = (SharedMemoryData*)MapViewOfFile(SharedMemoryHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedMemoryData));
        if (SharedData != NULL)
        {
            SharedData->SharedTexture = TextureHandle;
            SharedData->KeyState = 0;
            SharedData->NumKey = 0;
        }
    }
    else
    {
        UE_LOG(LogAvengers, Log, TEXT("Error: Cannot create shared memory"));
    }
}

void UAvengersCrashTracker::StartHelperProcess()
{
    FString PluginDir = FPaths::ProjectPluginsDir();
    FString HelperExePath = PluginDir / +"AvengersSDK/Binaries/Win64/CrashClientHelper.exe";

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
    uint32 pId = FWindowsPlatformProcess::GetCurrentProcessId();
    FString ProcessArgs = FString::Printf(TEXT("-o \"%s\" -c \"%s\" -p %u -s \"%s\""), *NextCrashFolder, *CrashConfigFile, pId, *SessionID);

    UE_LOG(LogAvengers, Log, TEXT("Process Args: %s"), *ProcessArgs);
    UE_LOG(LogAvengers, Log, TEXT("NextCrashFolder: %s"), *NextCrashFolder);
    UE_LOG(LogAvengers, Log, TEXT("Crash Client Config: %s"), *CrashConfigFile);
    UE_LOG(LogAvengers, Log, TEXT("Start the helper process %s"), *HelperExePath);
    FProcHandle Proc = FPlatformProcess::CreateProc(*HelperExePath, *ProcessArgs, true, false, false, nullptr, 0, nullptr, nullptr);
    if (!Proc.IsValid())
    {
        UE_LOG(LogAvengers, Log, TEXT("Opening file (%s) at a specific line failed."), *HelperExePath);
        FPlatformProcess::CloseProc(Proc);
    }
}

void UAvengersCrashTracker::SendKeyDataToSharedMemory()
{
    if (SharedData == nullptr)
    {
        return;
    }

    if (!IsValid(PlayerController))
    {
        return;
    }
    
    if (!bKeyrecordingInit)
    {
        return;
    }

    if (SharedData->NumKey == 0)
    {
        // update the list of keymaps
        SharedData->NumKey = KeyNames.Num();        
        for (UINT64 iKey = 0; iKey < KeyNames.Num(); iKey++)
        {
            memset(SharedData->KeyNames[iKey], 0, 255); // clear string
            char TempString[255];
            // Keyboard name
            //size_t len = wcstombs(TempString, *(KeyNames[iKey].GetDisplayName(false).ToString()), sizeof(TempString));

            // Action Name
            size_t len = wcstombs(TempString, *(ActionNames[iKey]), sizeof(TempString));
                        
            if (len > 0)
            {
                memcpy(SharedData->KeyNames[iKey], TempString, len);
            }
        }
    }

    // check for all key down, pooling method
    for (UINT64 iKey = 0; iKey < KeyNames.Num(); iKey++)
	{
        if (KeyNames[iKey].IsFloatAxis()) // don't record mouse move
        {
            continue; 
        }

		if (PlayerController->IsInputKeyDown(KeyNames[iKey]))
		{
			SharedData->KeyState |= 1ULL << (iKey);
		}
		else
		{
			SharedData->KeyState &= ~(1ULL << (iKey));
		}
	}

    SharedData->Tick = GetTickCount();
}

void UAvengersCrashTracker::RenderTick()
{
    UGameViewportClient* GV = GEngine->GameViewport;
    if (GV == nullptr)
        return;
    
    FViewport* V = GV->Viewport;
    if (V == nullptr)
        return;
    
    const FViewportRHIRef& RHIView = V->GetViewportRHI();
    if (RHIView.IsValid())
    {
        ID3D11Texture2D* ResolvedBackBufferDX11 = (ID3D11Texture2D*)RHIView->GetNativeBackBufferTexture();
        ID3D11Device* d3dDevice = nullptr;
        if (ResolvedBackBufferDX11 != nullptr)
        {
            HRESULT hr;

            // First verify that we can map the texture
            D3D11_TEXTURE2D_DESC BackbufferTextureDesc;
            ResolvedBackBufferDX11->GetDesc(&BackbufferTextureDesc);
            ResolvedBackBufferDX11->GetDevice(&d3dDevice);
            ID3D11DeviceContext* d3dContext;
            d3dDevice->GetImmediateContext(&d3dContext);

            if (StagingTexture == nullptr)
            {
                D3D11_TEXTURE2D_DESC StagingTextureDesc;
                StagingTextureDesc.Width = BackbufferTextureDesc.Width;
                StagingTextureDesc.Height = BackbufferTextureDesc.Height;
                StagingTextureDesc.MipLevels = BackbufferTextureDesc.MipLevels;
                StagingTextureDesc.ArraySize = BackbufferTextureDesc.ArraySize;
                StagingTextureDesc.Format = BackbufferTextureDesc.Format;
                StagingTextureDesc.SampleDesc = BackbufferTextureDesc.SampleDesc;
                StagingTextureDesc.Usage = D3D11_USAGE_DEFAULT;
                StagingTextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
                StagingTextureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
                StagingTextureDesc.MiscFlags = D3D11_RESOURCE_MISC_SHARED;

                hr = d3dDevice->CreateTexture2D(&StagingTextureDesc, nullptr, &StagingTexture);
                if (FAILED(hr)) {
                    //throw MyException::Make(hr, L"Failed to create staging texture");
                    UE_LOG(LogTemp, Log, TEXT("Failed to create staging texture"));
                }

                IDXGIResource* pOtherResource(NULL);
                hr = StagingTexture->QueryInterface(__uuidof(IDXGIResource), (void**)&pOtherResource);
                HANDLE TextureSharedHandle;
                pOtherResource->GetSharedHandle(&TextureSharedHandle);
                
                if (SharedMemoryHandle == nullptr)
                {
                    InitializeSharedMemory(TextureSharedHandle);
                }
            }

            // start the process only if SessionID is ready
            if (SharedMemoryHandle != nullptr && SharedData != nullptr && !SessionID.IsEmpty() && !bSubProccessRunning)
            {
                StartHelperProcess();
                bSubProccessRunning = true;
            }
            


            SendKeyDataToSharedMemory();
            d3dContext->CopyResource(StagingTexture, ResolvedBackBufferDX11);
        }
    }    
}

void UAvengersCrashTracker::BeginPlay(APlayerController* PlayerController)
{
    // called when game is started

}
void UAvengersCrashTracker::EndPlay()
{

}