// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "BaseMenuUI.generated.h"

/**
 * Base menu UI widget.
 */
UCLASS()
class UBaseMenuUI : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Setup widget */
	void Setup();

	/** Teardown widget */
	void Teardown();

	/**
	* Set menu interface
	*
	* @param MenuInterface The menu interface for the widget
	*/
	void SetMenuInterface(IMenuInterface* MenuInterface);

protected:
	/** Menu interface */
	IMenuInterface* MenuInterface;
};
