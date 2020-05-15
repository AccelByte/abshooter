// Copyright (c) 2019 - 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "ShooterGameProfleModels.h"
#include "UMG/AchievementEntryUI.h"
#include "UMG/StatisticEntryUI.h"
#include "Utils/ImageUtils.h"

namespace ShooterGameStatisticName
{
	extern const FString MVP;
	extern const FString TotalKills;
	extern const FString TotalDeath;
	extern const FString TotalMatch;
}

/** Handle Game Profile stuffs. */
class ShooterGameProfile
{
public:
	/**
	* @brief Default Constructor.
	*
	* @param _GameInstance The instance of the game.
	*/
	ShooterGameProfile(TWeakObjectPtr<class UShooterGameInstance> _GameInstance);

	/**
	* @brief Add achievement entry.
	*
	* @param Name The name of the achievement.
	* @param ImagePath The image path of the achievement.
	*/
	void AddAchievementEntry(FString Name, FString ImagePath);

	/**
	* @brief Add statistic entry.
	*
	* @param Name The name of the statistic.
	* @param Value The value of the statistic.
	* @param ImagePath The image path of the statistic.
	*/
	void AddStatisticEntry(FString Name, int32, FString ImagePath);

	/** Update statistic list. */
	void UpdateStatisticList();

	/** Player's statistic. */
	static FShooterStatistic Statistic;

	/** Player's profile name. */
	FString ProfileName;

	/** Player's avatar url. */
	FString AvatarURL;

	/** Player's avatar slate image. */
	FCacheBrush ThumbnailBrush;

	/** Player's achievement list. */
	TArray<UAchievementEntryUI*> AchievementList;

	/** Player's statistic list. */
	TArray<UStatisticEntryUI*> StatisticList;

private:
	/** Owning game instance. */
	TWeakObjectPtr<class UShooterGameInstance> GameInstance;
};
