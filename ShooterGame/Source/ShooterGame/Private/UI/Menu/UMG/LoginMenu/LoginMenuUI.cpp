// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "LoginMenuUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"

bool ULoginMenuUI::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(LoginWithUsernameButton != nullptr)) return false;
	LoginWithUsernameButton->OnClicked.AddDynamic(this, &ULoginMenuUI::LoginWithUsername);

	if (!ensure(QuitGameButton != nullptr)) return false;
	QuitGameButton->OnClicked.AddDynamic(this, &ULoginMenuUI::QuitGame);

	if (!ensure(UsernameField != nullptr)) return false;
	if (!ensure(PasswordField != nullptr)) return false;
	if (!ensure(ErrorField != nullptr)) return false;

	return true;
}

void ULoginMenuUI::SetInterface(ILoginMenuInterface* MenuInterface)
{
	if (MenuInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ULoginMenuUI] MenuInterface is null"));
		return;
	}
	LoginMenuInterface = MenuInterface;
}

void ULoginMenuUI::SetErrorLoginMessage(FString Message)
{
	if (!ensure(ErrorField != nullptr)) return;
	ErrorField->SetText(FText::FromString(Message));
}

#pragma region Button Callback
void ULoginMenuUI::LoginWithUsername()
{
	if (LoginMenuInterface != nullptr)
	{
		if (!ensure(ErrorField != nullptr)) return;
		ErrorField->SetText(FText::FromString(TEXT("")));

		if (!ensure(UsernameField != nullptr)) return;
		FString Username = UsernameField->GetText().ToString();

		if (!ensure(PasswordField != nullptr)) return;
		FString Password = PasswordField->GetText().ToString();

		LoginMenuInterface->LoginWithUsername(Username, Password);
	}
}

void ULoginMenuUI::QuitGame()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}
#pragma endregion Button Callback
