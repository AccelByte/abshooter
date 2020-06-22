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
	ERROR
};

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

private:
	/** Initialize widget. */
	virtual bool Initialize();

	/** Close popup. */
	UFUNCTION()
	void ClosePopup();

	/** Close button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* CloseButton;

	/** Notification message text. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MessageText;
};
