// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "UMG/BaseMenuUI.h"
#include "LoginMenuInterface.h"
#include "LoginMenuUI.generated.h"

/**
 * Login menu UI widget.
 */
UCLASS(config = game)
class ULoginMenuUI : public UBaseMenuUI
{
	GENERATED_BODY()

public:
	/**
	* @brief Set message into error field.
	*
	* @param Message Error message should be displayed.
	*/
	void SetErrorLoginMessage(FString Message);

	/**
	* @brief Set login menu interface.
	*
	* @param MenuInterface The menu interface for the widget.
	*/
	void SetInterface(ILoginMenuInterface* MenuInterface);

private:
	/** Initialize widget. */
	virtual bool Initialize();

private:

	UPROPERTY(config)
	FString SavedUsername;

	UPROPERTY(config)
	FString SavedPassword;

	/** Login with username and password */
	UFUNCTION()
	void LoginWithUsername();

	/** Quit game. */
	UFUNCTION()
	void QuitGame();

	/** Login button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* LoginWithUsernameButton;

	/** Quit button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitGameButton;

	/** Username input field. */
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* UsernameField;

	/** Password input field. */
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* PasswordField;

	/** Error message output field. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ErrorField;

	/** Login menu interface. */
	ILoginMenuInterface* LoginMenuInterface;
};
