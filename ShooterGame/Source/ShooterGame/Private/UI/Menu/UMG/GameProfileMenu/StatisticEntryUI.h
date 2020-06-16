// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatisticEntryUI.generated.h"

/**
 * Statistic entry UI widget.
 */
UCLASS()
class UStatisticEntryUI : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Statistic's name. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	/** Statistic's image. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSlateBrush Image;

	/** Statistic's value. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Value;
	
protected:
	/** Initialize widget. */
	virtual bool Initialize();
};
