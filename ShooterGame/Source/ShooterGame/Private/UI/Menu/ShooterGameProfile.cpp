// Copyright (c) 2019 - 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "ShooterGameProfile.h"
#include "ShooterGameInstance.h"
#include "UMG/GameProfileMenu/GameProfileMenuUI.h"
#include "ShooterGameConfig.h"
// AccelByte
#include "Core/AccelByteRegistry.h"
#include "Api/AccelByteStatisticApi.h"

FCriticalSection ShooterGameProfileMutex;

namespace ShooterGameStatisticName
{
	const FString MVP = TEXT("MVP");
	const FString TotalKills = TEXT("TOTAL KILLS");
	const FString TotalDeath = TEXT("TOTAL DEATHS");
	const FString TotalMatch = TEXT("TOTAL MATCH");
}

ShooterGameProfile::ShooterGameProfile(TWeakObjectPtr<UShooterGameInstance> _GameInstance, TWeakObjectPtr<UGameProfileMenuUI> _GameProfileMenuUI)
	: GameInstance(_GameInstance)
	, GameProfileMenuUI(_GameProfileMenuUI)
{}

void ShooterGameProfile::Initialize()
{
	InitStatisticItems();
	GetStatisticItems();
	GetAchievements();
}

void ShooterGameProfile::InitStatisticItems()
{
	AddStatisticEntry(ShooterGameStatisticName::MVP, ShooterGameProfile::Statistic.MVPScore, TEXT("Slate/Images/icon-stats-mvp.png"));
	AddStatisticEntry(ShooterGameStatisticName::TotalKills, ShooterGameProfile::Statistic.TotalKillsScore, TEXT("Slate/Images/icon-stats-totalkills.png"));
	AddStatisticEntry(ShooterGameStatisticName::TotalDeath, ShooterGameProfile::Statistic.TotalDeathsScore, TEXT("Slate/Images/icon-stats-totaldeaths.png"));
	AddStatisticEntry(ShooterGameStatisticName::TotalMatch, ShooterGameProfile::Statistic.TotalMatch, TEXT("Slate/Images/icon-stats-totalassits.png"));
	GameProfileMenuUI->UpdateStatisticList(StatisticList);
}

void ShooterGameProfile::AddStatisticEntry(FString Name, int32 Value, FString ImagePath)
{
	if (!GameInstance.IsValid()) return;

	FScopeLock Lock(&ShooterGameProfileMutex);

	TWeakObjectPtr<UStatisticEntryUI> StatisticEntry = MakeWeakObjectPtr<UStatisticEntryUI>(CreateWidget<UStatisticEntryUI>(GameInstance.Get(), *GameInstance->StatisticEntryClass.Get()));
	FString ImageFullPath = FPaths::ProjectContentDir() / ImagePath;
	if (IFileManager::Get().FileExists(*ImageFullPath))
	{
		TArray<uint8> ImageData;
		if (FFileHelper::LoadFileToArray(ImageData, *ImageFullPath))
		{
			TSharedPtr<FSlateDynamicImageBrush> StatisticImage = FShooterImageUtils::CreateBrush(FPaths::GetExtension(ImageFullPath), FName(*ImageFullPath), ImageData);
			if (StatisticImage.IsValid())
			{
				StatisticEntry->Image = *StatisticImage.Get();
			}
		}
	}
	StatisticEntry->Name = Name;
	StatisticEntry->Value = Value;
	StatisticList.Add(StatisticEntry.Get());
}

void ShooterGameProfile::GetStatisticItems()
{
	TArray<FString> StatCodes =
	{
		ShooterGameConfig::Get().StatisticCodeMVP_,
		ShooterGameConfig::Get().StatisticCodeMatch_,
		ShooterGameConfig::Get().StatisticCodeDeath_,
		ShooterGameConfig::Get().StatisticCodeKill_
	};
	AccelByte::FRegistry::Statistic.GetUserStatItems(StatCodes, {}, THandler<FAccelByteModelsUserStatItemPagingSlicedResult>::CreateLambda([this, StatCodes](const FAccelByteModelsUserStatItemPagingSlicedResult& Result)
	{
		UE_LOG(LogTemp, Log, TEXT("[ShooterGameProfile] Get StatItems Success!"));
		if (Result.Data.Num() != 0)
		{
			for (FAccelByteModelsUserStatItemInfo item : Result.Data)
			{
				if (item.StatCode == StatCodes[0])
				{
					Statistic.MVPScore = item.Value;
				}
				else if (item.StatCode == StatCodes[1])
				{
					Statistic.TotalMatch = item.Value;
				}
				else if (item.StatCode == StatCodes[2])
				{
					Statistic.TotalDeathsScore = item.Value;
				}
				else if (item.StatCode == StatCodes[3])
				{
					Statistic.TotalKillsScore = item.Value;
				}
			}
			UpdateStatisticList();
		}
	}), FErrorHandler::CreateLambda([](int32 Code, FString Message)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ShooterGameProfile] AccelByte::FRegistry::Statistic.GetUserStatItems Failed! Code: %d, Message: %s."), Code, *Message);
	}));
}

void ShooterGameProfile::UpdateStatisticList()
{
	for (int i = 0; i < StatisticList.Num(); i++)
	{
		if (StatisticList[i]->Name == ShooterGameStatisticName::MVP)
		{
			StatisticList[i]->Value = ShooterGameProfile::Statistic.MVPScore;
		}
		else if (StatisticList[i]->Name == ShooterGameStatisticName::TotalKills)
		{
			StatisticList[i]->Value = ShooterGameProfile::Statistic.TotalKillsScore;
		}
		else if (StatisticList[i]->Name == ShooterGameStatisticName::TotalDeath)
		{
			StatisticList[i]->Value = ShooterGameProfile::Statistic.TotalDeathsScore;
		}
		else if (StatisticList[i]->Name == ShooterGameStatisticName::TotalMatch)
		{
			StatisticList[i]->Value = ShooterGameProfile::Statistic.TotalMatch;
		}
	}
	GameProfileMenuUI->UpdateStatisticList(StatisticList);
}

void ShooterGameProfile::GetAchievements()
{
	UE_LOG(LogTemp, Log, TEXT("[ShooterGameProfile] GetAchievements"));

	// Mock UP
	AddAchievementEntry(TEXT("MASTER SHOOTER"), TEXT("Slate/Images/icon-achievement-1.png")); // 1
	AddAchievementEntry(TEXT("COMMANDER EXPERT"), TEXT("Slate/Images/icon-achievement-2.png")); // 2
	AddAchievementEntry(TEXT("THE BEAST KILLER"), TEXT("Slate/Images/icon-achievement-3.png")); // 3
	AddAchievementEntry(TEXT("GOD OF WAR"), TEXT("Slate/Images/icon-achievement-4.png")); // 4
	AddAchievementEntry(TEXT("ONE MAN ARMY"), TEXT("Slate/Images/icon-achievement-2.png")); // 5
	AddAchievementEntry(TEXT("FORGOTTEN LEGEND"), TEXT("Slate/Images/icon-achievement-2.png")); // 6
	AddAchievementEntry(TEXT("MAN WHO TOOK DOWN AN EMPIRE"), TEXT("Slate/Images/icon-achievement-4.png")); // 7
	AddAchievementEntry(TEXT("HARPSHOOTER"), TEXT("Slate/Images/icon-achievement-1.png")); // 8
	AddAchievementEntry(TEXT("LIVING LEGEND"), TEXT("Slate/Images/icon-achievement-3.png")); // 9
	AddAchievementEntry(TEXT("ONE HIT KILL"), TEXT("Slate/Images/icon-achievement-3.png")); // 10
	UpdateAchievementList();
}

void ShooterGameProfile::AddAchievementEntry(FString Name, FString ImagePath)
{
	if (!GameInstance.IsValid()) return;

	FScopeLock Lock(&ShooterGameProfileMutex);

	TWeakObjectPtr<UAchievementEntryUI> AchievementEntry = MakeWeakObjectPtr<UAchievementEntryUI>(CreateWidget<UAchievementEntryUI>(GameInstance.Get(), *GameInstance->AchievementEntryClass.Get()));
	FString ImageFullPath = FPaths::ProjectContentDir() / ImagePath;
	if (IFileManager::Get().FileExists(*ImageFullPath))
	{
		TArray<uint8> ImageData;
		if (FFileHelper::LoadFileToArray(ImageData, *ImageFullPath))
		{
			TSharedPtr<FSlateDynamicImageBrush> AchievementImage = FShooterImageUtils::CreateBrush(FPaths::GetExtension(ImageFullPath), FName(*ImageFullPath), ImageData);
			if (AchievementImage.IsValid())
			{
				AchievementEntry->Image = *AchievementImage.Get();
			}
		}
	}
	AchievementEntry->Name = Name;
	AchievementList.Add(AchievementEntry.Get());
}

void ShooterGameProfile::UpdateAchievementList()
{
	GameProfileMenuUI->UpdateAchievementList(AchievementList);
}
