// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AchievementEntryUI.generated.h"

/**
 * Achievement Entry UI widget.
 */
UCLASS()
class UAchievementEntryUI : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Achievement's name. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	/** Achievement's image. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSlateBrush Image;

protected:
	/** Initialize menu widget. */
	virtual bool Initialize();
};
