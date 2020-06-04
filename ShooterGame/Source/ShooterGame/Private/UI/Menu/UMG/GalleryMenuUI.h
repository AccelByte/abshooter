 // Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
 // This is licensed software from AccelByte Inc, for limitations
 // and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GalleryEntryUI.h"
#include "GalleryMenuUI.generated.h"

/**
 * Gallery menu UI widget.
 */
UCLASS()
class UGalleryMenuUI : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	* @brief Update gallery list.
	*
	* @param GalleryList The list of gallery.
	*/
	void UpdateGalleryList(TArray<UGalleryEntryUI*> GalleryList);

	/** Clear any entries selection. */
	void ClearSelection();

protected:
	/** Initialize menu widget. */
	virtual bool Initialize();

private:
	/** Gallery list view. */
	UPROPERTY(meta = (BindWidget))
	class UTileView* GalleryTileView;
	 
	/** "Empty" text. */
 	UPROPERTY(meta = (BindWidget))
 	class UTextBlock* EmptyText;
};
