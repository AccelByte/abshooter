// Copyright (c) 2019 - 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "ShooterGameProfleModels.h"
#include "UMG/StatisticEntryUI.h"
#include "UMG/AchievementEntryUI.h"
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
	* @param _GameProfileMenuUI Game profile menu ui container.
	*/
	ShooterGameProfile(TWeakObjectPtr<class UShooterGameInstance> _GameInstance, TWeakObjectPtr<class UGameProfileMenuUI> _GameProfileMenuUI);

	/** Initialize menu. */
	void Initialize();

	/** Player's profile name. */
	FString ProfileName;

	/** Player's avatar url. */
	FString AvatarURL;

	/** Player's avatar slate image. */
	FCacheBrush ThumbnailBrush;

private:
	/** Initiate statistic items. */
	void InitStatisticItems();

	/**
	* @brief Add statistic entry.
	*
	* @param Name The name of the statistic.
	* @param Value The value of the statistic.
	* @param ImagePath The image path of the statistic.
	*/
	void AddStatisticEntry(FString Name, int32, FString ImagePath);

	/** Get player statistic. */
	void GetStatisticItems();

	/** Update statistic list. */
	void UpdateStatisticList();

	/** Get player achievements. */
	void GetAchievements();

	/**
	* @brief Add achievement entry.
	*
	* @param Name The name of the achievement.
	* @param ImagePath The image path of the achievement.
	*/
	void AddAchievementEntry(FString Name, FString ImagePath);

	/** Update achievement list. */
	void UpdateAchievementList();

	/** Owning game instance. */
	TWeakObjectPtr<class UShooterGameInstance> GameInstance;

	/** Game profile sub-menu UI. */
	TWeakObjectPtr<class UGameProfileMenuUI> GameProfileMenuUI;	

	/** Player's statistic. */
	FShooterStatistic Statistic;

	/** Player's statistic list. */
	TArray<UStatisticEntryUI*> StatisticList;

	/** Player's achievement list. */
	TArray<UAchievementEntryUI*> AchievementList;
};
