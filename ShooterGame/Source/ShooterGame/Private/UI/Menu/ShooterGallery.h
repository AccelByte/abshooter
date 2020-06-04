// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "UMG/GalleryEntryUI.h"
#include "UMG/GalleryEditUI.h"
#include "Utils/ImageUtils.h"
// AccelByte
#include "Models/AccelByteCloudStorageModels.h"

/** Handle Gallery stuffs. */
class ShooterGallery : public IGalleryEntryInterface, public IGalleryEditInterface
{
public:
	/**
	* @brief Default Constructor.
	*
	* @param _GameInstance The instance of the game.
	* @param _GameProfileMenuUI Game profile menu ui container.
	*/
	ShooterGallery(TWeakObjectPtr<class UShooterGameInstance> _GameInstance, TWeakObjectPtr<class UGalleryMenuUI> _GalleryMenuUI);

	/** Initialize menu. */
	void Initialize();

private:
	/** Get player cloudstorage slots. */
	void GetSlots();

	/**
	* @brief Add gallery entry with default empty image.
	*
	* @param Slot Gallery entry slot.
	*/
	void AddEmptyGalleryEntry(FAccelByteModelsSlot Slot);

	/**
	* @brief Add gallery entry from saved metadata.
	*
	* @param Slot Gallery entry slot.
	*/
	void AddSavedGalleryEntry(FAccelByteModelsSlot Slot);

	/** Update gallery list. */
	void UpdateGalleryList();

	/**
	* @brief Get player slot based on the its id.
	*
	* @param Slot The cloudstorage slot.
	*/
	void GetSlot(FAccelByteModelsSlot Slot);

	/**
	* @brief Handle slot image receiving.
	*
	* @param Slot The cloudstorage slot.
	* @param Result The binary image of the slot.
	*/
	void OnReceiveSlotImage(FAccelByteModelsSlot Slot, const TArray<uint8>& Result);

	/**
	* @brief Save local screenshot image.
	*
	* @param Filename The filename of the image.
	* @param Binary The binary of the screenshot image.
	* @return Full path of the screenshot image.
	*/
	FString SaveLocalScreenshotImage(FString Filename, const TArray<uint8>& Binary);

	/**
	* @brief Get screenshot directory.
	*
	* @return Full path of the screenshot directory.
	*/
	FString GetScreenshotsDir();

	/**
	* @brief Get user screenshots directory.
	*
	* @return Full path of the user screenshots directory.
	*/
	FString GetUserScreenshotsDir();

	/** Save screenshot metadata. */
	void SaveScreenshotMetadata();

	/** Load screenshots from metadata. */
	void LoadScreenshotFromMetadata();

	/**
	* @brief Delete screenshot image.
	*
	* @param Filename The image's filename.
	*/
	void DeleteScreenshotImage(FString SlotId);

	#pragma region Override Gallery Entry Interface
	/**
	* @brief Preview gallery image.
	*
	* @param Image Gallery image.
	*/
	void PreviewImage(FSlateBrush Image) override;

	/**
	* @brief Edit gallery image's label.
	*
	* @param SlotId Gallery image's slot id.
	* @param Label Gallery image's label.
	*/
	void EditLabel(FString SlotId, FString Label) override;

	/**
	* @brief Delete gallery image.
	*
	* @param SlotId Gallery screenshot's slot id.
	*/
	void DeleteImage(FString SlotId) override;
	#pragma endregion Override Gallery Entry Interface

	#pragma region Override Gallery Edit Interface
	/**
	* @brief Save gallery image's label.
	*
	* @param SlotId Gallery image's slot id.
	* @param Label Gallery image's label.
	*/
	void SaveCaption(FString SlotId, FString Label) override;
	#pragma endregion Override Gallery Edit Interface

	/** Owning game instance. */
	TWeakObjectPtr<class UShooterGameInstance> GameInstance;

	/** Gallery sub-menu UI. */
	TWeakObjectPtr<class UGalleryMenuUI> GalleryMenuUI;

	/** Gallery preview UI widget. */
	TWeakObjectPtr<class UGalleryPreviewUI> GalleryPreviewUI;

	/** Gallery edit UI widget. */
	TWeakObjectPtr<class UGalleryEditUI> GalleryEditUI;

	/** Gallery list. */
	TArray<UGalleryEntryUI*> GalleryList;

	/** Local screenshot data. */
	FScreenshotMetadata ScreenshotMetadata;
};
