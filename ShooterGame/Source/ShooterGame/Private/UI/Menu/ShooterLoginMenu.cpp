// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "ShooterLoginMenu.h"
#include "ShooterGameInstance.h"
#include "UMG/LoginMenuUI.h"
// AccelByte
#include "Core/AccelByteRegistry.h"
#include "Core/AccelByteHttpRetryScheduler.h"
#include "Api/AccelByteUserApi.h"

FShooterLoginMenu::FShooterLoginMenu(TWeakObjectPtr<UShooterGameInstance> _GameInstance)
	: GameInstance(_GameInstance)
{}

void FShooterLoginMenu::Construct()
{
	UE_LOG(LogTemp, Log, TEXT("[FShooterLoginMenu] Construct"));

	check(GameInstance.IsValid());

	// Load login menu widget
	if (!ensure(GameInstance->LoginMenuClass.IsValid())) return;

	LoginMenuUI = MakeWeakObjectPtr<ULoginMenuUI>(CreateWidget<ULoginMenuUI>(GameInstance.Get(), *GameInstance->LoginMenuClass.Get()));
	if (!ensure(LoginMenuUI != nullptr))
	{
		UE_LOG(LogTemp, Log, TEXT("[FShooterLoginMenu] LoginMenuUI is null"));
		return;
	}

	// Add the widget to viewport
	UE_LOG(LogTemp, Log, TEXT("[FShooterLoginMenu] Setup LoginMenuUI to viewport"));
	LoginMenuUI->Setup();
	LoginMenuUI->SetInterface(this);
}

void FShooterLoginMenu::Teardown()
{
	if (LoginMenuUI.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("[FShooterLoginMenu] Teardown LoginMenuUI"));
		LoginMenuUI->Teardown();
		LoginMenuUI.Reset();
	}
}

#pragma region Override Login Menu Interface
void FShooterLoginMenu::LoginWithUsername(FString Username, FString Password)
{
	UE_LOG(LogTemp, Log, TEXT("[FShooterLoginMenu] Login with username"));
	bool bHasDone = false;
	FString ErrorMessage = TEXT("");
	AccelByte::FVoidHandler OnLoginSuccess = AccelByte::FVoidHandler::CreateLambda([&bHasDone]()
	{
		UE_LOG(LogTemp, Log, TEXT("[FShooterLoginMenu] Login with username success"));
		bHasDone = true;
	});
	AccelByte::FErrorHandler OnLoginError = AccelByte::FErrorHandler::CreateLambda([&ErrorMessage, &bHasDone](int32 Code, FString Message)
	{
		UE_LOG(LogTemp, Log, TEXT("[FShooterLoginMenu] Login with username error: %s"), *Message);
		ErrorMessage = TEXT("Failed to Login");
		bHasDone = true;
	});
	AccelByte::FRegistry::User.LoginWithUsername(Username, Password, OnLoginSuccess, OnLoginError);

	// Blocking here
	double LastTime = FPlatformTime::Seconds();
	while (!bHasDone)
	{
		const double AppTime = FPlatformTime::Seconds();
		FHttpModule::Get().GetHttpManager().Tick(AppTime - LastTime);
		AccelByte::FRegistry::HttpRetryScheduler.PollRetry(FPlatformTime::Seconds(), FRegistry::Credentials);
		LastTime = AppTime;
		FPlatformProcess::Sleep(0.5f);
	}

	if (ErrorMessage.IsEmpty())
	{
		GameInstance->SetupUser();
	}
	else
	{
		LoginMenuUI->SetErrorLoginMessage(ErrorMessage);
	}
}
#pragma endregion Override Login Menu Interface
