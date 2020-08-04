 // Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
 // This is licensed software from AccelByte Inc, for limitations
 // and restrictions contact your company contract manager.

 #include "GalleryMenuUI.h"
 #include "Components/TextBlock.h"
 #include "Components/TileView.h"

FCriticalSection GalleryMenuUIMutex;

 bool UGalleryMenuUI::Initialize()
 {
 	bool Success = Super::Initialize();
 	if (!Success) return false;

	if (!ensure(GalleryTileView != nullptr)) return false;
 	if (!ensure(EmptyText != nullptr)) return false;

 	return true;
 }

 void UGalleryMenuUI::UpdateGalleryList(TArray<UGalleryEntryUI*> GalleryList)
 {
	 if (this == NULL) return;

	FScopeLock Lock(&GalleryMenuUIMutex);

 	GalleryTileView->SetListItems(GalleryList);
	if (GalleryList.Num() != 0)
	{
		EmptyText->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		EmptyText->SetVisibility(ESlateVisibility::Visible);
	}
	GalleryTileView->RegenerateAllEntries();
 }

 void UGalleryMenuUI::ClearSelection()
 {
	 GalleryTileView->ClearSelection();
 }
