 // Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
 // This is licensed software from AccelByte Inc, for limitations
 // and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Utils/ImageUtils.h"
#include "Models/ShooterGalleryModels.h"
#include "GalleryEntryInterface.h"
#include "GalleryEntryUI.generated.h"

/**
 * Gallery entry UI widget.
 */
UCLASS()
class UGalleryEntryUI : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	/**
	* @brief Set interface.
	*
	* @param Interface The interface for the widget.
	*/
	void SetInterface(IGalleryEntryInterface* Interface);

	/** Screenshot cloudstorage's slot id. */
	FString SlotId;

	/** Screenshot state. */
	EGalleryState State = EGalleryState::NONE;

	/** Screenshot label. */
	FString Label;
 
	/** Screenshot image. */
	FSlateBrush Image;

protected:
	/** Initialize widget. */
	virtual bool Initialize();

	// NOTE:
	// Based on the https://docs.unrealengine.com/en-US/API/Runtime/UMG/Blueprint/IUserObjectListEntry/SetListItemObjectInternal/index.html
	// Function below will be deprecated on 4.23 version, and renamed into NativeOnListItemObjectSet.
	void SetListItemObjectInternal(UObject* InObject) override;

	void NativeOnItemSelectionChanged(bool bIsSelected) override;

private:
	/** Preview image. */
	UFUNCTION()
	void PreviewImage();

	/** Edit label. */
	UFUNCTION()
	void EditLabel();

	/** Delete image. */
	UFUNCTION()
	void DeleteImage();

	/** Screenshot Image. */
	UPROPERTY(meta = (BindWidget))
	class UImage* ScreenshotImage;
 
	/** Inactive background Image. */
	UPROPERTY(meta = (BindWidget))
	class UImage* InactiveBackground;

	/** Cloud Image. */
	UPROPERTY(meta = (BindWidget))
	class UImage* CloudImage;

	/** Selected Image. */
	UPROPERTY(meta = (BindWidget))
	class UImage* SelectedImage;

	/** Loading bar. */
	UPROPERTY(meta = (BindWidget))
	class UThrobber* LoadingBar;

	/** Screenshot label field. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LabelField;

	/** Modifying selected box. */
	UPROPERTY(meta = (BindWidget))
	class UWidget* ModifyingBox;

	/** Preview button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* PreviewButton;

	/** Edit button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* EditButton;

	/** Delete button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* DeleteButton;

	/** Cloud Image. */
	FSlateBrush CloudOffIcon;
	FSlateBrush CloudDoneIcon;
	FSlateBrush CloudDownloadIcon;
	FSlateBrush CloudUploadIcon;
	FSlateBrush CloudDeleteIcon;
	FSlateBrush CloudSyncIcon;

	/** Gallery entry interface. */
	IGalleryEntryInterface* GalleryEntryInterface;
};
