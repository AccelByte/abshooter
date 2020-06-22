// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "UMG/BaseMenuUI.h"
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
	void SetAvatarImage(FSlateBrush Image);

	/** Get Game Profile sub-menu widget. */
	class UGameProfileMenuUI* GetGameProfileMenu();

	/** Get Lobby sub-menu widget. */
	class ULobbyMenuUI* GetLobbyMenu();

	/** Get Gallery sub-menu widget. */
	class UGalleryMenuUI* GetGalleryMenu();

protected:
	/** Handle on key pressed. */
	FReply NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

	/** Player's display name field. */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite)
	class UTextBlock* DisplayNameField;

private:
	/** Initialize widget. */
	virtual bool Initialize();

	/** Open main menu. */
	UFUNCTION()
	void OpenMainMenu();

	/** Open Game Profile sub-menu. */
	UFUNCTION()
	void OpenGameProfileMenu();

	/** Open Lobby sub-menu. */
	UFUNCTION()
	void OpenLobbyMenu();

	/** Open Gallery sub-menu. */
	UFUNCTION()
	void OpenGalleryMenu();

	/** Quit game. */
	UFUNCTION()
	void QuitGame();

	/** Back to main menu shortcut key. */
	FKey BackToMainMenuKey;

	/** Player's avatar. */
	UPROPERTY(meta = (BindWidget))
	class UImage* AvatarImage;

	/** Game Profile button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* GameProfileButton;

	/** Lobby button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* LobbyButton;

	/** Gallery button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* GalleryButton;

	/** Quit button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	/** Back to main menu button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* EscButton;

	/** Menu switcher. */
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	/** Main menu widget. */
	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	/** Game Profile sub-menu widget. */
	UPROPERTY(meta = (BindWidget))
	class UWidget* GameProfileMenu;

	/** Lobby sub-menu widget. */
	UPROPERTY(meta = (BindWidget))
	class UWidget* LobbyMenu;

	/** Gallery sub-menu widget. */
	UPROPERTY(meta = (BindWidget))
	class UWidget* GalleryMenu;

	/** Back to main menu box widget. */
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* BackToMainMenuBox;

	/** Game Profile sub-menu widget. */
	UPROPERTY(meta = (BindWidget))
	class UGameProfileMenuUI* WB_GameProfileMenu;

	/** Lobby sub-menu widget. */
	UPROPERTY(meta = (BindWidget))
	class ULobbyMenuUI* WB_LobbyMenu;

	/** Gallery sub-menu widget. */
	UPROPERTY(meta = (BindWidget))
	class UGalleryMenuUI* WB_GalleryMenu;
};
