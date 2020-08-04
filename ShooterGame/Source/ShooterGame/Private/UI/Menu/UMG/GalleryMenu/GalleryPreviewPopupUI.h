// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "GalleryPreviewPopupUI.generated.h"

/**
 * Gallery preview UI widget.
 */
UCLASS()
class UGalleryPreviewPopupUI : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	* @brief Preview gallery image.
	*
	* @param Image Gallery image.
	*/
	void PreviewImage(FSlateBrush Image);

private:
	/** Initialize widget. */
	virtual bool Initialize();

	/** Close preview image. */
	UFUNCTION()
	void CloseImage();

	/** Close button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* CloseButton;

	/** Preview image. */
	UPROPERTY(meta = (BindWidget))
	class UImage* GalleryImage;
};
