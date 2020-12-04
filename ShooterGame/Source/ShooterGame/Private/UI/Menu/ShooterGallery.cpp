// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "ShooterGallery.h"
#include "ShooterGameInstance.h"
#include "UMG/GalleryMenu/GalleryMenuUI.h"
#include "UMG/GalleryMenu/GalleryPreviewPopupUI.h"
#include "UMG/GalleryMenu/GalleryEditPopupUI.h"
// AccelByte
#include "Core/AccelByteRegistry.h"
#include "Api/AccelByteCloudStorageApi.h"

FCriticalSection ShooterGalleryMutex;

ShooterGallery::ShooterGallery(TWeakObjectPtr<UShooterGameInstance> _GameInstance, TWeakObjectPtr<UGalleryMenuUI> _GalleryMenuUI)
	: GameInstance(_GameInstance)
	, GalleryMenuUI(_GalleryMenuUI)
{}

void ShooterGallery::Initialize()
{
	LoadScreenshotFromMetadata();
	GetSlots();
}

void ShooterGallery::GetSlots()
{
	AccelByte::FRegistry::CloudStorage.GetAllSlots(
		AccelByte::THandler<TArray<FAccelByteModelsSlot>>::CreateLambda([&](const TArray<FAccelByteModelsSlot>& Result)
			{
				// Clear unsync saved screenshot.
				for (int i = 0; i < ScreenshotMetadata.Screenshots.Num(); i++)
				{
					if (ScreenshotMetadata.Screenshots.IsValidIndex(i)) continue;
					FAccelByteModelsSlot LocalSlot = ScreenshotMetadata.Screenshots[i];
					int32 Index = Result.IndexOfByPredicate([LocalSlot](FAccelByteModelsSlot Slot) {
						return Slot.SlotId == LocalSlot.SlotId && Slot.Checksum == LocalSlot.Checksum;
					});
					if (Index == INDEX_NONE)
					{
						DeleteScreenshotImage(LocalSlot.SlotId);
					}
				}

				for (int i = 0; i < Result.Num(); i++)
				{
					FAccelByteModelsSlot SlotResult = Result[i];
					UE_LOG(LogTemp, Log, TEXT("[ShooterGallery] Response from cloud. SlotId: %s"), *SlotResult.SlotId);

					int32 Index = ScreenshotMetadata.Screenshots.IndexOfByPredicate([SlotResult](FAccelByteModelsSlot Slot) {
						return Slot.SlotId == SlotResult.SlotId && Slot.Checksum == SlotResult.Checksum;
					});
					if (Index == INDEX_NONE)
					{
						AddEmptyGalleryEntry(SlotResult);
						GetSlot(SlotResult);
					}
					else if(Index != INDEX_NONE && SlotResult.DateModified.ToUnixTimestamp() > ScreenshotMetadata.Screenshots[Index].DateModified.ToUnixTimestamp())
					{
						DeleteScreenshotImage(SlotResult.SlotId);
						AddEmptyGalleryEntry(SlotResult);
						GetSlot(SlotResult);
					}
				}
			}
		),
		AccelByte::FErrorHandler::CreateLambda([](int32 ErrorCode, FString ErrorString)
			{
				UE_LOG(LogTemp, Warning, TEXT("[ShooterGallery] AccelByte::FRegistry::CloudStorage.GetAllSlot Failed! Code: %d, Message: %s."), ErrorCode, *ErrorString);
			}
		)
	);
}

void ShooterGallery::AddEmptyGalleryEntry(FAccelByteModelsSlot Slot)
{
	if (!GameInstance.IsValid()) return;

	FScopeLock Lock(&ShooterGalleryMutex);

	TWeakObjectPtr<UGalleryEntryUI> GalleryEntry = MakeWeakObjectPtr<UGalleryEntryUI>(CreateWidget<UGalleryEntryUI>(GameInstance.Get(), *GameInstance->GalleryEntryClass.Get()));
	FString ImagePath = FString::Printf(TEXT("%s\\Content\\Slate\\Images\\Gallery\\GallerySlotEmptyBackground.png"), *FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()));
	if (IFileManager::Get().FileExists(*ImagePath))
	{
		TArray<uint8> ImageData;
		if (FFileHelper::LoadFileToArray(ImageData, *ImagePath))
		{
			TSharedPtr<FSlateDynamicImageBrush> GalleryImage = FShooterImageUtils::CreateBrush(FPaths::GetExtension(ImagePath), FName(*ImagePath), ImageData);
			if (GalleryImage.IsValid())
			{
				GalleryEntry->Image = *GalleryImage.Get();
			}
		}
	}
	GalleryEntry->SlotId = Slot.SlotId;
	GalleryEntry->Label = Slot.Label;
	GalleryEntry->State = EGalleryState::NONE;
	GalleryList.Add(GalleryEntry.Get());
	UpdateGalleryList();
}

void ShooterGallery::AddSavedGalleryEntry(FAccelByteModelsSlot Slot)
{
	if (!GameInstance.IsValid()) return;

	TWeakObjectPtr<UGalleryEntryUI> GalleryEntry = MakeWeakObjectPtr<UGalleryEntryUI>(CreateWidget<UGalleryEntryUI>(GameInstance.Get(), *GameInstance->GalleryEntryClass.Get()));
	FString ImagePath = GetUserScreenshotsDir() / Slot.SlotId + ".png";
	if (IFileManager::Get().FileExists(*ImagePath))
	{
		TArray<uint8> ImageData;
		if (FFileHelper::LoadFileToArray(ImageData, *ImagePath))
		{
			FString LocalChecksum = FShooterImageUtils::MD5HashArray(ImageData);
			if (LocalChecksum == Slot.Checksum)
			{
				TSharedPtr<FSlateDynamicImageBrush> GalleryImage = FShooterImageUtils::CreateBrush(FPaths::GetExtension(ImagePath), FName(*ImagePath), ImageData);
				if (GalleryImage.IsValid())
				{
					FScopeLock Lock(&ShooterGalleryMutex);

					GalleryEntry->Image = *GalleryImage.Get();
					GalleryEntry->State = EGalleryState::DONE;
					GalleryEntry->SlotId = Slot.SlotId;
					GalleryEntry->Label = Slot.Label;
					GalleryEntry->SetInterface(this);
					GalleryList.Add(GalleryEntry.Get());
					UpdateGalleryList();

					ScreenshotMetadata.Screenshots.Add(Slot);
					return;
				}
			}
		}
		DeleteScreenshotImage(Slot.SlotId);
	}
}

void ShooterGallery::UpdateGalleryList()
{
	GalleryMenuUI->UpdateGalleryList(GalleryList);
}

void ShooterGallery::GetSlot(FAccelByteModelsSlot Slot)
{
	FScopeLock Lock(&ShooterGalleryMutex);

	int32 Index = GalleryList.IndexOfByPredicate([Slot](UGalleryEntryUI* Entry) {
		return Entry->SlotId == Slot.SlotId;
	});
	if(Index != INDEX_NONE)
	{
		GalleryList[Index]->State = EGalleryState::DOWNLOADING;
		UpdateGalleryList();
		AccelByte::FRegistry::CloudStorage.GetSlot(
			Slot.SlotId,
			AccelByte::THandler<TArray<uint8>>::CreateLambda([this, Slot](const TArray<uint8>& Result)
				{
					UE_LOG(LogTemp, Log, TEXT("[ShooterGallery] AccelByte::FRegistry::CloudStorage.GetSlot SlotId: %s. Success."), *Slot.SlotId);
					OnReceiveSlotImage(Slot, Result);
				}
			),		
			AccelByte::FErrorHandler::CreateLambda([this, Slot](int32 ErrorCode, FString ErrorString)
				{
					UE_LOG(LogTemp, Warning, TEXT("[ShooterGallery] AccelByte::FRegistry::CloudStorage.GetSlot Failed SlotId: %s! Code: %d, Message: %s."), *Slot.SlotId, ErrorCode, *ErrorString);
					FScopeLock Lock(&ShooterGalleryMutex);

					int32 Index = GalleryList.IndexOfByPredicate([Slot](UGalleryEntryUI* Entry) {
						return Entry->SlotId == Slot.SlotId;
					});
					if (Index != INDEX_NONE)
					{
						GalleryList[Index]->State = EGalleryState::ERROR_UNKNOWN;
						UpdateGalleryList();
					}
				}
			)
		);
	}
}

void ShooterGallery::OnReceiveSlotImage(FAccelByteModelsSlot Slot, const TArray<uint8>& Result)
{
	FString ImagePath = SaveLocalScreenshotImage(Slot.SlotId, Result);
	if (!ImagePath.IsEmpty() && Result.Num() > 0)
	{
		TSharedPtr<FSlateDynamicImageBrush> GalleryImage = FShooterImageUtils::CreateBrush(FPaths::GetExtension(ImagePath), FName(*ImagePath), Result);
		if (GalleryImage.IsValid())
		{
			FScopeLock Lock(&ShooterGalleryMutex);

			int32 Index = GalleryList.IndexOfByPredicate([Slot](UGalleryEntryUI* Entry) {
				return Entry->SlotId == Slot.SlotId;
			});
			if (Index != INDEX_NONE)
			{
				GalleryList[Index]->Image = *GalleryImage.Get();
				GalleryList[Index]->State = EGalleryState::DONE;
				GalleryList[Index]->SetInterface(this);
				UpdateGalleryList();

				ScreenshotMetadata.Screenshots.Add(Slot);
				SaveScreenshotMetadata();
			}
		}
	}
	else
	{
		GalleryList.RemoveAll([Slot](UGalleryEntryUI* Entry) {
			return Entry->SlotId == Slot.SlotId;
		});
		UpdateGalleryList();
	}
}

FString ShooterGallery::SaveLocalScreenshotImage(FString Filename, const TArray<uint8>& Binary)
{
	FString UserScreenshotsDir = GetUserScreenshotsDir();
	if (UserScreenshotsDir.IsEmpty()) return TEXT("");

	FString ImagePath = UserScreenshotsDir / Filename + ".png";
	if (!FFileHelper::SaveArrayToFile(Binary, *ImagePath)) return TEXT("");
	return ImagePath;
}

FString ShooterGallery::GetScreenshotsDir()
{
	FString ScreenshotsDir = FPaths::ProjectSavedDir() / "Screenshots";
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.DirectoryExists(*ScreenshotsDir))
	{
		PlatformFile.CreateDirectory(*ScreenshotsDir);
		if (!PlatformFile.DirectoryExists(*ScreenshotsDir)) return TEXT("");
	}
	return ScreenshotsDir;
}

FString ShooterGallery::GetUserScreenshotsDir()
{
	FString ScreenshotsDir = GetScreenshotsDir();
	if (ScreenshotsDir.IsEmpty()) return TEXT("");
	FString UserScreenshotsDir = ScreenshotsDir / GameInstance->UserProfileInfo.UserId;
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.DirectoryExists(*UserScreenshotsDir))
	{
		PlatformFile.CreateDirectory(*UserScreenshotsDir);
		if (!PlatformFile.DirectoryExists(*UserScreenshotsDir)) return TEXT("");
	}
	return UserScreenshotsDir;
}

void ShooterGallery::SaveScreenshotMetadata()
{
	FString SavePath = GetScreenshotsDir() / GameInstance->UserProfileInfo.UserId + ".json";
	FString MetadataString;
	if (FJsonObjectConverter::UStructToJsonObjectString(ScreenshotMetadata, MetadataString))
	{
		if (FFileHelper::SaveStringToFile(MetadataString, *SavePath))
		{
			UE_LOG(LogTemp, Log, TEXT("[ShooterGallery] File successfullly saved, Path: %s."), *SavePath)
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("[ShooterGallery] File failed to saved, Path: %s."), *SavePath)
		}
	}
}

void ShooterGallery::LoadScreenshotFromMetadata()
{
	FString MetadataPath = GetScreenshotsDir() / GameInstance->UserProfileInfo.UserId + ".json";
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if(!PlatformFile.FileExists(*MetadataPath)) return;

	FString SaveString;
	if (!FFileHelper::LoadFileToString(SaveString, *MetadataPath)) return;

	FScreenshotMetadata Metadata;
	if (!FJsonObjectConverter::JsonObjectStringToUStruct(SaveString, &Metadata, 0, 0)) return;
	for (int i = 0; i < Metadata.Screenshots.Num(); i++)
	{
		FAccelByteModelsSlot LocalSlot = Metadata.Screenshots[i];
		int32 Index = ScreenshotMetadata.Screenshots.IndexOfByPredicate([LocalSlot](FAccelByteModelsSlot Slot) {
			return Slot.SlotId == LocalSlot.SlotId;
		});
		if (Index == INDEX_NONE || LocalSlot.DateModified.ToUnixTimestamp() > ScreenshotMetadata.Screenshots[Index].DateModified.ToUnixTimestamp())
		{
			AddSavedGalleryEntry(LocalSlot);
		}
	}
	SaveScreenshotMetadata();
}

void ShooterGallery::DeleteScreenshotImage(FString SlotId)
{
	FString UserScreenshotsDir = GetUserScreenshotsDir();
	FString ImageFullPath = UserScreenshotsDir / SlotId + ".png";
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.DeleteFile(*ImageFullPath))
	{
		FScopeLock Lock(&ShooterGalleryMutex);

		GalleryMenuUI->ClearSelection();
		GalleryList.RemoveAll([SlotId](UGalleryEntryUI* Entry) {
			return Entry->SlotId == SlotId;
		});
		UpdateGalleryList();

		ScreenshotMetadata.Screenshots.RemoveAll([SlotId](FAccelByteModelsSlot Slot) {
			return Slot.SlotId == SlotId;
		});
		SaveScreenshotMetadata();
	}
}

#pragma region Override Gallery Entry Interface
void ShooterGallery::PreviewImage(FSlateBrush Image)
{
	if (!GameInstance.IsValid()) return;

	TWeakObjectPtr<UGalleryPreviewPopupUI> GalleryPreviewPopup = MakeWeakObjectPtr<UGalleryPreviewPopupUI>(CreateWidget<UGalleryPreviewPopupUI>(GameInstance.Get(), *GameInstance->GalleryPreviewPopupClass.Get()));
	GalleryPreviewPopup->PreviewImage(Image);
}

void ShooterGallery::EditLabel(FString SlotId, FString Caption)
{
	if (!GameInstance.IsValid()) return;

	TWeakObjectPtr<UGalleryEditPopupUI> GalleryEditPopup = MakeWeakObjectPtr<UGalleryEditPopupUI>(CreateWidget<UGalleryEditPopupUI>(GameInstance.Get(), *GameInstance->GalleryEditPopupClass.Get()));
	GalleryEditPopup->SetInterface(this);
	GalleryEditPopup->Show(SlotId, Caption);
}

void ShooterGallery::DeleteImage(FString SlotId)
{
	FScopeLock Lock(&ShooterGalleryMutex);

	int32 Index = GalleryList.IndexOfByPredicate([SlotId](UGalleryEntryUI* Entry) {
		return Entry->SlotId == SlotId;
	});
	if (Index != INDEX_NONE)
	{
		GalleryList[Index]->State = EGalleryState::DELETING;
		UpdateGalleryList();
		AccelByte::FRegistry::CloudStorage.DeleteSlot(SlotId,
			AccelByte::FVoidHandler::CreateLambda([this, SlotId]()
				{
					UE_LOG(LogTemp, Log, TEXT("[ShooterGallery] Delete SlotId: %s. Success."), *SlotId);
					DeleteScreenshotImage(SlotId);
				}
			),
			AccelByte::FErrorHandler::CreateLambda([this, SlotId](int32 ErrorCode, FString ErrorString)
				{
					UE_LOG(LogTemp, Warning, TEXT("[ShooterGallery] AccelByte::FRegistry::CloudStorage.DeleteSlot Failed SlotId: %s! Code: %d, Message: %s."), *SlotId, ErrorCode, *ErrorString);
					int32 Index = GalleryList.IndexOfByPredicate([SlotId](UGalleryEntryUI* Entry) {
						return Entry->SlotId == SlotId;
					});
					if (Index != INDEX_NONE)
					{
						GalleryList[Index]->State = EGalleryState::DONE;
						UpdateGalleryList();
					}
				}
			)
		);
	}
}
#pragma endregion Override Gallery Entry Interface

#pragma region Override Gallery Edit Interface
void ShooterGallery::SaveCaption(FString SlotId, FString Label)
{
	int32 MetadataIndex = ScreenshotMetadata.Screenshots.IndexOfByPredicate([SlotId](FAccelByteModelsSlot Slot) {
		return Slot.SlotId == SlotId;
	});
	
	FScopeLock Lock(&ShooterGalleryMutex);

	int32 GalleryListIndex = GalleryList.IndexOfByPredicate([SlotId](UGalleryEntryUI* Entry) {
		return Entry->SlotId == SlotId;
	});
	if (MetadataIndex != INDEX_NONE && GalleryListIndex != INDEX_NONE)
	{
		GalleryList[GalleryListIndex]->State = EGalleryState::UPDATING;
		UpdateGalleryList();
		AccelByte::FRegistry::CloudStorage.UpdateSlotMetadata(
			ScreenshotMetadata.Screenshots[MetadataIndex].SlotId,
			TEXT(""),
			{ TEXT("") },
			Label,
			TEXT(""),
			AccelByte::THandler<FAccelByteModelsSlot>::CreateLambda([this, SlotId, Label](const FAccelByteModelsSlot& Result)
				{
					UE_LOG(LogTemp, Log, TEXT("[ShooterGallery] AccelByte::FRegistry::CloudStorage.UpdateSlotMetadata SlotId: %s. Success."), *SlotId);
					int32 MetadataIndex = ScreenshotMetadata.Screenshots.IndexOfByPredicate([SlotId](FAccelByteModelsSlot Slot) {
						return Slot.SlotId == SlotId;
					});

					FScopeLock Lock(&ShooterGalleryMutex);

					int32 GalleryListIndex = GalleryList.IndexOfByPredicate([SlotId](UGalleryEntryUI* Entry) {
						return Entry->SlotId == SlotId;
					});
					if (MetadataIndex != INDEX_NONE && GalleryListIndex != INDEX_NONE)
					{
						ScreenshotMetadata.Screenshots[MetadataIndex] = Result;
						SaveScreenshotMetadata();

						GalleryList[GalleryListIndex]->Label = Label;
						GalleryList[GalleryListIndex]->State = EGalleryState::DONE;
						UpdateGalleryList();
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("[ShooterGallery] Cannot update caption of SlotId: %s for the local slot."), *SlotId);
					}
				}
			),
			nullptr,
			AccelByte::FErrorHandler::CreateLambda([SlotId](int32 ErrorCode, FString ErrorString)
				{
					UE_LOG(LogTemp, Warning, TEXT("[ShooterGallery] AccelByte::FRegistry::CloudStorage.UpdateSlotMetadata Failed SlotId: %s! Code: %d, Message: %s."), *SlotId, ErrorCode, *ErrorString);
				}
			)
		);
	}
}
#pragma endregion Override Gallery Edit Interface
