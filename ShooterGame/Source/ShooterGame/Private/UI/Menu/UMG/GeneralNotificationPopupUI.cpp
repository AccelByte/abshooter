// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "GeneralNotificationPopupUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

bool UGeneralNotificationPopupUI::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(CloseButton != nullptr)) return false;
	CloseButton->OnClicked.AddDynamic(this, &UGeneralNotificationPopupUI::ClosePopup);

	if (!ensure(MessageText != nullptr)) return false;

	return true;
}

void UGeneralNotificationPopupUI::Show(ENotificationType Type, FString Message)
{
	switch (Type)
	{
	case ENotificationType::WARNING:
		MessageText->SetColorAndOpacity(FLinearColor::Yellow);
		break;
	case ENotificationType::ERROR:
		MessageText->SetColorAndOpacity(FLinearColor::Red);
		break;
	default:
		break;
	}
	MessageText->SetText(FText::FromString(Message));
	this->AddToPlayerScreen();
}

#pragma region Button Callback
void UGeneralNotificationPopupUI::ClosePopup()
{
	this->RemoveFromViewport();
}
#pragma endregion Button Callback
