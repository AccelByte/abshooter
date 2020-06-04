// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "BaseMenuUI.h"
#include "Kismet/GameplayStatics.h"

void UBaseMenuUI::Setup()
{
	this->AddToPlayerScreen();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	// set input mode to UI only
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
	if (PlayerController == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("[UBaseMenuUI] PlayerController is null"));
		return;
	}

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;

	FReply::Handled().SetUserFocus(this->TakeWidget(), EFocusCause::SetDirectly);
}

void UBaseMenuUI::Teardown()
{
	this->RemoveFromViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
	if (PlayerController == nullptr) return;

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;

	FReply::Handled().ClearUserFocus(true);
}
