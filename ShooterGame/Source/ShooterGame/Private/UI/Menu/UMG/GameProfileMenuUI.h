// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AchievementEntryUI.h"
#include "StatisticEntryUI.h"
#include "GameProfileMenuUI.generated.h"

/**
 * Game Profile menu UI widget.
 */
UCLASS()
class UGameProfileMenuUI : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	* @brief Set payer's display name field.
	*
	* @param DisplayName Player's display name.
	*/
	void SetDisplayName(FString DisplayName);

	/**
	* @brief Set player's avatar image.
	*
	* @param AvatarImage Player's avatar image.
	*/
	void SetAvatarImage(FSlateBrush AvatarImage);

	/**
	* @brief Update player's achievement list.
	*
	* @param AchievementList Player's achievement list.
	*/
	void UpdateGameProfileAchievement(TArray<UAchievementEntryUI*> AchievementList);

	/**
	* @brief Update player's statistic list.
	*
	* @param StatisticList Player's statistic list.
	*/
	void UpdateGameProfileStatistic(TArray<UStatisticEntryUI*> StatisticList);

protected:
	/** Initilize menu widget. */
	virtual bool Initialize();

	/** Player's achievement list view. */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite)
	class UTileView* AchievementTileView;

	/** Player's statistic list view. */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite)
	class UTileView* StatisticTileView;

private:
	/** Player's avatar. */
	UPROPERTY(meta = (BindWidget))
	class UImage* AvatarImage;

	/** Player's display name field. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DisplayNameField;

	/** Achievement "Empty" text. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AchievementEmptyText;

	/** Statistic "Empty" text. */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StatisticEmptyText;
};
