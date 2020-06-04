// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "MainMenuUI.h"
#include "GameProfileMenuUI.h"
#include "GalleryMenuUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "Components/HorizontalBox.h"

bool UMainMenuUI::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(GameProfileButton != nullptr)) return false;
	GameProfileButton->OnClicked.AddDynamic(this, &UMainMenuUI::OpenGameProfileMenu);

	if (!ensure(GalleryButton != nullptr)) return false;
	GalleryButton->OnClicked.AddDynamic(this, &UMainMenuUI::OpenGalleryMenu);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UMainMenuUI::QuitGame);

	if (!ensure(EscButton != nullptr)) return false;
	EscButton->OnClicked.AddDynamic(this, &UMainMenuUI::OpenMainMenu);

	if (!ensure(BackToMainMenuBox != nullptr)) return false;
	BackToMainMenuBox->SetVisibility(ESlateVisibility::Collapsed);

	if (!ensure(DisplayNameField != nullptr)) return false;
	if (!ensure(AvatarImage != nullptr)) return false;
	if (!ensure(MenuSwitcher != nullptr)) return false;
	if (!ensure(MainMenu != nullptr)) return false;
	if (!ensure(GameProfileMenu != nullptr)) return false;
	if (!ensure(GalleryMenu != nullptr)) return false;
	if (!ensure(BackToMainMenuBox != nullptr)) return false;
	if (!ensure(WB_GameProfileMenu != nullptr)) return false;
	if (!ensure(WB_GalleryMenu != nullptr)) return false;
	
	UWorld* const World = GetWorld();
	if (World->IsPlayInEditor())
	{
		BackToMainMenuKey = EKeys::F1; // By UE Editor default, if Esc is pressed in Editor, it will close the game.
	}
	else
	{
		BackToMainMenuKey = EKeys::Escape;
	}

	return true;
}

FReply UMainMenuUI::NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Result = FReply::Unhandled();
	const FKey Key = InKeyEvent.GetKey();
	if (Key == BackToMainMenuKey)
	{
		OpenMainMenu();
		Result = FReply::Handled();
	}
	return Result;
}

void UMainMenuUI::SetDisplayName(FString DisplayName)
{
	DisplayNameField->SetText(FText::FromString(DisplayName));
	WB_GameProfileMenu->SetDisplayName(DisplayName);
}

void UMainMenuUI::SetAvatarImage(FSlateBrush Image)
{
	AvatarImage->SetBrush(Image);
	WB_GameProfileMenu->SetAvatarImage(Image);
}

UGameProfileMenuUI* UMainMenuUI::GetGameProfileMenu()
{
	return WB_GameProfileMenu;
}

UGalleryMenuUI* UMainMenuUI::GetGalleryMenu()
{
	return WB_GalleryMenu;
}

#pragma region Button callback
void UMainMenuUI::OpenMainMenu()
{
	MenuSwitcher->SetActiveWidget(MainMenu);
	BackToMainMenuBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UMainMenuUI::OpenGameProfileMenu()
{
	MenuSwitcher->SetActiveWidget(GameProfileMenu);
	BackToMainMenuBox->SetVisibility(ESlateVisibility::Visible);
}

void UMainMenuUI::OpenGalleryMenu()
{
	WB_GalleryMenu->ClearSelection();
	MenuSwitcher->SetActiveWidget(GalleryMenu);
	BackToMainMenuBox->SetVisibility(ESlateVisibility::Visible);
}

void UMainMenuUI::QuitGame()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}
#pragma endregion Button callback
