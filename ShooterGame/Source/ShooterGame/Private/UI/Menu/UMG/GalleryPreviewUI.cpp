// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "GalleryPreviewUI.h"
#include "Components/Button.h"
#include "Components/Image.h"

bool UGalleryPreviewUI::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(CloseButton != nullptr)) return false;
	CloseButton->OnClicked.AddDynamic(this, &UGalleryPreviewUI::CloseImage);

	if (!ensure(GalleryImage != nullptr)) return false;

	return true;
}

void UGalleryPreviewUI::PreviewImage(FSlateBrush Image)
{
	GalleryImage->SetBrush(Image);
	this->AddToPlayerScreen();
}

#pragma region Button callback
void UGalleryPreviewUI::CloseImage()
{
	this->RemoveFromViewport();
}
#pragma endregion Button callback
