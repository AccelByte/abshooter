// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GalleryEditPopupInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGalleryEditPopupInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for the UMG gallery edit popup widget.
 */
class IGalleryEditPopupInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	* @brief Save gallery image's label.
	*
	* @param SlotId Gallery image's slot id.
	* @param Label Gallery image's label.
	*/
	virtual void SaveCaption(FString SlotId, FString Label) = 0;
};
