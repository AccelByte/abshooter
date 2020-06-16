// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GalleryEntryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGalleryEntryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for the UMG gallery entry widget.
 */
class IGalleryEntryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	* @brief Preview gallery image.
	*
	* @param Image Gallery image.
	*/
	virtual void PreviewImage(FSlateBrush Image) = 0;

	/**
	* @brief Edit gallery image's label.
	*
	* @param SlotId Gallery image's slot id.
	* @param Label Gallery image's label.
	*/
	virtual void EditLabel(FString SlotId, FString Label) = 0;

	/**
	* @brief Delete gallery image.
	*
	* @param SlotId Gallery screenshot's slot id.
	*/
	virtual void DeleteImage(FString SlotId) = 0;
};
