// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "ShooterLoginMenu.h"
#include "UMG/LoginMenuUI.h"
// AccelByte
#include "Core/AccelByteRegistry.h"

void FShooterLoginMenu::Construct(TWeakObjectPtr<UShooterGameInstance> _GameInstance, TSubclassOf<UUserWidget> LoginMenuClass)
{
	UE_LOG(LogTemp, Log, TEXT("[FShooterLoginMenu] Construct"));

	check(_GameInstance.IsValid());
	GameInstance = _GameInstance;

	// Load login menu widget
	if (!ensure(LoginMenuClass != nullptr)) return;

	LoginMenuUI = MakeWeakObjectPtr<ULoginMenuUI>(CreateWidget<ULoginMenuUI>(GameInstance.Get(), LoginMenuClass));
	if (!ensure(LoginMenuUI != nullptr))
	{
		UE_LOG(LogTemp, Log, TEXT("[FShooterLoginMenu] LoginMenuUI is null"));
		return;
	}

	// Add the widget to viewport
	UE_LOG(LogTemp, Log, TEXT("[FShooterLoginMenu] Setup LoginMenuUI to viewport"));
	LoginMenuUI->Setup();
	LoginMenuUI->SetLoginMenuInterface(this);
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

#pragma region Override Menu Interface
void FShooterLoginMenu::LoginWithUsername(FString Username, FString Password)
{
	UE_LOG(LogTemp, Log, TEXT("[FShooterLoginMenu] Login with username"));
	bool bHasDone = false;
	FString ErrorMessage = TEXT("");
	FVoidHandler OnLoginSuccess = FVoidHandler::CreateLambda([&bHasDone]()
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
	FRegistry::User.LoginWithUsername(Username, Password, OnLoginSuccess, OnLoginError);

	// Blocking here
	double LastTime = FPlatformTime::Seconds();
	while (!bHasDone)
	{
		const double AppTime = FPlatformTime::Seconds();
		FHttpModule::Get().GetHttpManager().Tick(AppTime - LastTime);
		FRegistry::HttpRetryScheduler.PollRetry(FPlatformTime::Seconds(), FRegistry::Credentials);
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
#pragma endregion Override Menu Interface
