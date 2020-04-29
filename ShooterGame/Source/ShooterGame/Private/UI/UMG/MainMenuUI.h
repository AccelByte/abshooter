// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "BaseMenuUI.h"
#include "MainMenuUI.generated.h"

/**
 * Login menu UI widget.
 */
UCLASS()
class UMainMenuUI : public UBaseMenuUI
{
	GENERATED_BODY()

protected:
	/** Initilize menu widget */
	virtual bool Initialize();

private:
	/** Quit game */
	UFUNCTION()
	void QuitGame();

	/** Quit button */
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;
};
