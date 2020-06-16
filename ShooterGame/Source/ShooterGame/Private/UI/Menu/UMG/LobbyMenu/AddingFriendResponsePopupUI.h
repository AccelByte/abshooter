// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "AddingFriendResponsePopupUI.generated.h"

/**
 * Adding friend response popup UI widget.
 */
UCLASS()
class UAddingFriendResponsePopupUI : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Show adding friend response popup UI widget. */
	void Show();

protected:
	/** Initialize widget. */
	virtual bool Initialize();

private:
	/** Close popup. */
	UFUNCTION()
	void ClosePopup();

	/** Close button. */
	UPROPERTY(meta = (BindWidget))
	class UButton* CloseButton;
};
