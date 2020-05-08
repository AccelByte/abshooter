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

public:
	/**
	* @brief Set display name field.
	*
	* @param DisplayName Player's display name.
	*/
	void SetDisplayName(FString DisplayName);

	/**
	* @brief Set player's avatar.
	*
	* @param AvatarImage Player's avatar image.
	*/
	void SetAvatarImage(FSlateBrush AvatarImage);

protected:
	/** Initilize menu widget. */
	virtual bool Initialize();

	/** Player display name field. */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite)
	class UTextBlock* DisplayNameField;

private:
	/** Quit game. */
	UFUNCTION()
	void QuitGame();

	/** Quit button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	/** Player's avatar. */
	UPROPERTY(meta = (BindWidget))
	class UImage* PlayerAvatarImage;
};
