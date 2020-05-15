// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "BaseMenuUI.h"
#include "GameProfileMenuUI.h"
#include "MainMenuUI.generated.h"

/**
 * Main menu UI widget.
 */
UCLASS()
class UMainMenuUI : public UBaseMenuUI
{
	GENERATED_BODY()

public:
	/**
	* @brief Set player's display name field.
	*
	* @param DisplayName Player's display name.
	*/
	void SetDisplayName(FString DisplayName);

	/**
	* @brief Set player's avatar image.
	*
	* @param AvatarImage Player's avatar image.
	*/
	void SetAvatarImage(FSlateBrush AvatarImage);

	/** Get Game Profile menu widget. */
	UGameProfileMenuUI* GetGameProfileMenu();

protected:
	/** Initilize menu widget. */
	virtual bool Initialize();

	/** Handle on key pressed. */
	FReply NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

	/** Player's display name field. */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite)
	class UTextBlock* DisplayNameField;

private:
	/** Open main menu. */
	UFUNCTION()
	void OpenMainMenu();

	/** Open Game profile sub-menu. */
	UFUNCTION()
	void OpenGameProfileMenu();

	/** Quit game. */
	UFUNCTION()
	void QuitGame();

	/** Back to main menu shortcut key. */
	FKey BackToMainMenuKey;

	/** Player's avatar. */
	UPROPERTY(meta = (BindWidget))
	class UImage* AvatarImage;

	/** Quit button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* GameProfileButton;

	/** Quit button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	/** Quit button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* EscButton;

	/** Menu switcher. */
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	/** Main menu widget. */
	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	/** Game profile sub-menu widget. */
	UPROPERTY(meta = (BindWidget))
	class UWidget* GameProfileMenu;

	/** Back to main menu box widget. */
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* BackToMainMenuBox;

	/** Game Profile menu widget. */
	UPROPERTY(meta = (BindWidget))
	UGameProfileMenuUI* WB_GameProfileMenu;
};
