// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "ShooterGameInstance.h"
#include "UMG/MenuInterface.h"

class FShooterLoginMenu : public ILoginMenuInterface
{
public:
	/**
	* @brief Construct menu.
	*
	* @param _GameInstance Instance of the game.
	* @param LoginMenuClass Blueprint widget class.
	*/
	void Construct(TWeakObjectPtr<UShooterGameInstance> _GameInstance, TSubclassOf<class UUserWidget> LoginMenuClass);

	/** Teardown menu. */
	void Teardown();

private:
	/** Owning game instance. */
	TWeakObjectPtr<UShooterGameInstance> GameInstance;

	/** Login Menu UI widget. */
	TWeakObjectPtr<class ULoginMenuUI> LoginMenuUI;

	#pragma region Override Menu Interface
	/** Login with username and password */
	void LoginWithUsername(FString Username, FString Password) override;
	#pragma endregion Override Menu Interface

};
