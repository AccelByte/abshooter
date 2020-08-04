// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "GeneralNotificationPopupUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

bool UGeneralNotificationPopupUI::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(CloseButton != nullptr)) return false;
	CloseButton->OnClicked.AddDynamic(this, &UGeneralNotificationPopupUI::CloseButtonClicked);

	if (!ensure(MessageText != nullptr)) return false;

	if (!ensure(NotificationSwitcher != nullptr)) return false;

	if (!ensure(NotificationButton != nullptr)) return false;
	NotificationButton->OnClicked.AddDynamic(this, &UGeneralNotificationPopupUI::NotificationButtonClicked);

	return true;
}

void UGeneralNotificationPopupUI::Show(ENotificationType Type, FString Message)
{
	switch (Type)
	{
	case ENotificationType::WARNING:
		NotificationSwitcher->SetActiveWidget(MessageText);
		MessageText->SetColorAndOpacity(FLinearColor::Yellow);
		MessageText->SetText(FText::FromString(Message));
		break;
	case ENotificationType::ERROR:
		NotificationSwitcher->SetActiveWidget(MessageText);
		MessageText->SetColorAndOpacity(FLinearColor::Red);
		MessageText->SetText(FText::FromString(Message));
		break;
	case ENotificationType::BUTTON:
		NotificationSwitcher->SetActiveWidget(NotificationButton);
		ButtonText->SetText(FText::FromString(Message));
		break;
	
	/* Notification Type. */
	default:
		MessageText->SetText(FText::FromString(Message));
		break;
	}
	this->AddToPlayerScreen();
}

void UGeneralNotificationPopupUI::Show(ENotificationType Type, FString Message, FOnNotificationButtonClicked OnButtonClickedDelegate, FOnNotificationCloseButtonClicked OnCloseButtonClickedDelegate)
{
	switch (Type)
	{
	case ENotificationType::WARNING:
		NotificationSwitcher->SetActiveWidget(MessageText);
		MessageText->SetColorAndOpacity(FLinearColor::Yellow);
		MessageText->SetText(FText::FromString(Message));
		break;
	case ENotificationType::ERROR:
		NotificationSwitcher->SetActiveWidget(MessageText);
		MessageText->SetColorAndOpacity(FLinearColor::Red);
		MessageText->SetText(FText::FromString(Message));
		break;
	case ENotificationType::BUTTON:
		NotificationSwitcher->SetActiveWidget(NotificationButton);
		if (OnButtonClickedDelegate.IsBound())
		{
			OnNotificationButtonClicked = OnButtonClickedDelegate;
		}
		ButtonText->SetText(FText::FromString(Message));
		break;

		/* Notification Type. */
	default:
		MessageText->SetText(FText::FromString(Message));
		break;
	}
	if (OnCloseButtonClickedDelegate.IsBound())
	{
		OnCloseButtonClicked = OnCloseButtonClickedDelegate;
	}
	this->AddToPlayerScreen();
}

#pragma region Button Callback
void UGeneralNotificationPopupUI::ClosePopup()
{
	this->RemoveFromViewport();
}
void UGeneralNotificationPopupUI::CloseButtonClicked()
{
	OnCloseButtonClicked.ExecuteIfBound();
	ClosePopup();
}
void UGeneralNotificationPopupUI::NotificationButtonClicked()
{
	OnNotificationButtonClicked.ExecuteIfBound();
}
#pragma endregion Button Callback
