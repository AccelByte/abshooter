// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GeneralNotificationPopupUI.generated.h"

UENUM(BlueprintType)
enum class ENotificationType : uint8
{
	NOTIFICATION = 0,
	WARNING,
	BUTTON,
	ERROR
};

/** Delegate used for when Notification::Button button are pressed. */
DECLARE_DELEGATE(FOnNotificationButtonClicked);

/** Delegate used for when Close Button are pressed pressed. */
DECLARE_DELEGATE(FOnNotificationCloseButtonClicked);

/**
 * General notification popup UI widget.
 */
UCLASS()
class UGeneralNotificationPopupUI : public UUserWidget
{
	GENERATED_BODY()

public:

	/**
	* @brief Show adding friend response popup UI widget.
	*
	* @param Type The type of the notification.
	* @param Message The message of the notification.
	*/
	void Show(ENotificationType Type, FString Message);

	/**
	* @brief Show adding response popup UI widget, attach delegate into the action buttons.
	*
	* @param Type The type of the notification.
	* @param Message The message of the notification.
	* @param OnButtonClickedDelegate Delegate for when main button was pressed.
	* @param OnNotificationCloseButtonClicked Delegate for when Close button was pressed.
	*
	* OnNotificationCloseButtonClicked OnNotificationCloseButton was set as null because it doesn't have to be implemented.
	*
	*/
	void Show(ENotificationType Type, FString Message, const FOnNotificationButtonClicked OnButtonClickedDelegate, const FOnNotificationCloseButtonClicked OnCloseButtonClickedDelegate = NULL);

	/** Close popup. */
	UFUNCTION()
	void ClosePopup();

private:
	/** Initialize widget. */
	virtual bool Initialize();

	UFUNCTION()
	void NotificationButtonClicked();

	UFUNCTION()
	void CloseButtonClicked();

	FOnNotificationButtonClicked OnNotificationButtonClicked;

	FOnNotificationCloseButtonClicked OnCloseButtonClicked;

	/** Close button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* CloseButton;

	/** Filled with Message Text and Notification Button. */
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* NotificationSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UButton* NotificationButton;

	/** NotificationButton's message text. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ButtonText;

	/** Notification message text. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MessageText;
};
