// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "UMG/LoginMenu/LoginMenuInterface.h"

class FShooterLoginMenu : public ILoginMenuInterface
{
public:
	/**
	* @brief Default Constructor.
	*
	* @param _GameInstance The instance of the game.
	*/
	FShooterLoginMenu(TWeakObjectPtr<class UShooterGameInstance> _GameInstance);

	/** Construct menu. */
	void Construct();

	/** Teardown menu. */
	void Teardown();

private:
	#pragma region Override Login Menu Interface
	/**
	* @brief Login with username and password.
	*
	* @param Username The login username of the player.
	* @param Password The login password of the player.
	*/
	void LoginWithUsername(FString Username, FString Password) override;
	#pragma endregion Override Login Menu Interface
	
	/** Owning game instance. */
	TWeakObjectPtr<class UShooterGameInstance> GameInstance;

	/** Login Menu UI widget. */
	TWeakObjectPtr<class ULoginMenuUI> LoginMenuUI;
};
