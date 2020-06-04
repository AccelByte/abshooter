// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "GalleryEntryUI.h"
#include "GalleryPreviewUI.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Throbber.h"
#include "Components/HorizontalBox.h"
#include "Components/Button.h"

bool UGalleryEntryUI::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(PreviewButton != nullptr)) return false;
	PreviewButton->OnClicked.AddDynamic(this, &UGalleryEntryUI::PreviewImage);

	if (!ensure(EditButton != nullptr)) return false;
	EditButton->OnClicked.AddDynamic(this, &UGalleryEntryUI::EditLabel);

	if (!ensure(DeleteButton != nullptr)) return false;
	DeleteButton->OnClicked.AddDynamic(this, &UGalleryEntryUI::DeleteImage);

	if (!ensure(ScreenshotImage != nullptr)) return false;
	if (!ensure(InactiveBackground != nullptr)) return false;
	if (!ensure(CloudImage != nullptr)) return false;
	if (!ensure(SelectedImage != nullptr)) return false;
	if (!ensure(LoadingBar != nullptr)) return false;
	if (!ensure(LabelField != nullptr)) return false;
	if (!ensure(ModifyingBox != nullptr)) return false;

	FString ImagesGalleryDir = FPaths::ProjectContentDir() / "UMG\\GalleryMenu\\Images";
	
	// CloudOff icon
	FString ImagePath = ImagesGalleryDir / "CloudOffFilled.png";
	if (IFileManager::Get().FileExists(*ImagePath))
	{
		TArray<uint8> ImageData;
		if (FFileHelper::LoadFileToArray(ImageData, *ImagePath))
		{
			CloudOffIcon = *FShooterImageUtils::CreateBrush(FPaths::GetExtension(ImagePath), FName(*ImagePath), ImageData).Get();
		}
	}

	// CloudDone icon
	ImagePath = ImagesGalleryDir / "CloudDoneFilled.png";
	if (IFileManager::Get().FileExists(*ImagePath))
	{
		TArray<uint8> ImageData;
		if (FFileHelper::LoadFileToArray(ImageData, *ImagePath))
		{
			CloudDoneIcon = *FShooterImageUtils::CreateBrush(FPaths::GetExtension(ImagePath), FName(*ImagePath), ImageData).Get();
		}
	}

	// CloudDownload icon
	ImagePath = ImagesGalleryDir / "CloudDownloadFilled.png";
	if (IFileManager::Get().FileExists(*ImagePath))
	{
		TArray<uint8> ImageData;
		if (FFileHelper::LoadFileToArray(ImageData, *ImagePath))
		{
			CloudDownloadIcon = *FShooterImageUtils::CreateBrush(FPaths::GetExtension(ImagePath), FName(*ImagePath), ImageData).Get();
		}
	}

	// CloudUpload icon
	ImagePath = ImagesGalleryDir / "CloudUploadFilled.png";
	if (IFileManager::Get().FileExists(*ImagePath))
	{
		TArray<uint8> ImageData;
		if (FFileHelper::LoadFileToArray(ImageData, *ImagePath))
		{
			CloudUploadIcon = *FShooterImageUtils::CreateBrush(FPaths::GetExtension(ImagePath), FName(*ImagePath), ImageData).Get();
		}
	}

	// CloudDelete icon
	ImagePath = ImagesGalleryDir / "CloudDeleteFilled.png";
	if (IFileManager::Get().FileExists(*ImagePath))
	{
		TArray<uint8> ImageData;
		if (FFileHelper::LoadFileToArray(ImageData, *ImagePath))
		{
			CloudDeleteIcon = *FShooterImageUtils::CreateBrush(FPaths::GetExtension(ImagePath), FName(*ImagePath), ImageData).Get();
		}
	}

	// CloudSync icon
	ImagePath = ImagesGalleryDir / "CloudSync.png";
	if (IFileManager::Get().FileExists(*ImagePath))
	{
		TArray<uint8> ImageData;
		if (FFileHelper::LoadFileToArray(ImageData, *ImagePath))
		{
			CloudSyncIcon = *FShooterImageUtils::CreateBrush(FPaths::GetExtension(ImagePath), FName(*ImagePath), ImageData).Get();
		}
	}

	return true;
}

void UGalleryEntryUI::SetListItemObjectInternal(UObject* InObject)
{
	UGalleryEntryUI* Entry = Cast<UGalleryEntryUI>(InObject);

	SlotId = Entry->SlotId;

	Image = Entry->Image;
	ScreenshotImage->SetBrush(Entry->Image);

	State = Entry->State;
	if (Entry->State > EGalleryState::DONE)
	{
		InactiveBackground->SetVisibility(ESlateVisibility::Visible);
		LoadingBar->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		InactiveBackground->SetVisibility(ESlateVisibility::Hidden);
		LoadingBar->SetVisibility(ESlateVisibility::Hidden);
	}

	if (Entry->State == EGalleryState::NONE)
	{
		CloudImage->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		CloudImage->SetVisibility(ESlateVisibility::Visible);
		switch (Entry->State)
		{
		case EGalleryState::ERROR:
			CloudImage->SetBrush(Entry->CloudOffIcon);
			break;
		case EGalleryState::DONE:
			CloudImage->SetBrush(Entry->CloudDoneIcon);
			break;
		case EGalleryState::DOWNLOADING:
			CloudImage->SetBrush(Entry->CloudDownloadIcon);
			break;
		case EGalleryState::UPLOADING:
			CloudImage->SetBrush(Entry->CloudUploadIcon);
			break;
		case EGalleryState::DELETING:
			CloudImage->SetBrush(Entry->CloudDeleteIcon);
			break;
		case EGalleryState::UPDATING:
			CloudImage->SetBrush(Entry->CloudSyncIcon);
			break;
		default:
			CloudImage->SetBrush(Entry->CloudOffIcon);
		}
	}

	Label = Entry->Label;
	LabelField->SetText(FText::FromString(Entry->Label));

	GalleryEntryInterface = Entry->GalleryEntryInterface;

	SelectedImage->SetVisibility(ESlateVisibility::Collapsed);
	ModifyingBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UGalleryEntryUI::NativeOnItemSelectionChanged(bool bIsSelected)
{
	if (bIsSelected && State <= EGalleryState::DONE && GalleryEntryInterface != nullptr)
	{
		SelectedImage->SetVisibility(ESlateVisibility::Visible);
		ModifyingBox->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SelectedImage->SetVisibility(ESlateVisibility::Collapsed);
		ModifyingBox->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UGalleryEntryUI::SetInterface(IGalleryEntryInterface* Interface)
{
	if (Interface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UGalleryEntryUI] Interface is null"));
		return;
	}
	GalleryEntryInterface = Interface;
}

#pragma region Button callback
void UGalleryEntryUI::PreviewImage()
{
	if (State == EGalleryState::DELETING) return;

	if (GalleryEntryInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UGalleryEntryUI] Interface is null"));
		return;
	}
	GalleryEntryInterface->PreviewImage(Image);
}

void UGalleryEntryUI::EditLabel()
{
	if (State == EGalleryState::DELETING) return;

	if (GalleryEntryInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UGalleryEntryUI] Interface is null"));
		return;
	}
	GalleryEntryInterface->EditLabel(SlotId, Label);
}

void UGalleryEntryUI::DeleteImage()
{
	if (State == EGalleryState::DELETING) return;

	if (GalleryEntryInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UGalleryEntryUI] Interface is null"));
		return;
	}
	GalleryEntryInterface->DeleteImage(SlotId);
}
#pragma endregion Button callback
