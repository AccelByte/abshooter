// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "MainMenuUI.h"
#include "Components/Button.h"
#include "Components/Image.h"

bool UMainMenuUI::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UMainMenuUI::QuitGame);

	return true;
}

#pragma region Button Callback
void UMainMenuUI::QuitGame()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}
#pragma endregion Button Callback

void UMainMenuUI::SetDisplayName(FString DisplayName)
{
	if (!ensure(DisplayNameField != nullptr)) return;
	DisplayNameField->SetText(FText::FromString(DisplayName));
}

void UMainMenuUI::SetAvatarImage(FSlateBrush AvatarImage)
{
	PlayerAvatarImage->SetBrush(AvatarImage);
}

