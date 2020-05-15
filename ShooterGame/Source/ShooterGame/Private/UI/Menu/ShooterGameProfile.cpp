// Copyright (c) 2019 - 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "ShooterGameProfile.h"
#include "ShooterGameInstance.h"
// AccelByte
#include "Core/AccelByteRegistry.h"

namespace ShooterGameStatisticName
{
	const FString MVP = TEXT("MVP");
	const FString TotalKills = TEXT("TOTAL KILLS");
	const FString TotalDeath = TEXT("TOTAL DEATHS");
	const FString TotalMatch = TEXT("TOTAL MATCH");
}

FShooterStatistic ShooterGameProfile::Statistic = FShooterStatistic();

ShooterGameProfile::ShooterGameProfile(TWeakObjectPtr<UShooterGameInstance> _GameInstance)
	: GameInstance(_GameInstance)
{}

void ShooterGameProfile::AddAchievementEntry(FString Name, FString ImagePath)
{
	TWeakObjectPtr<UAchievementEntryUI> AchievementEntry = MakeWeakObjectPtr<UAchievementEntryUI>(CreateWidget<UAchievementEntryUI>(GameInstance.Get(), *GameInstance->AchievementEntryClass.Get()));
	IFileManager& FileManager = IFileManager::Get();
	FString ImageFullPath = FString::Printf(TEXT("%s\\Content\\%s"), *FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()), *ImagePath);
	if (FileManager.FileExists(*ImageFullPath))
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

void ShooterGameProfile::AddStatisticEntry(FString Name, int32 Value, FString ImagePath)
{
	TWeakObjectPtr<UStatisticEntryUI> StatisticEntry = MakeWeakObjectPtr<UStatisticEntryUI>(CreateWidget<UStatisticEntryUI>(GameInstance.Get(), *GameInstance->StatisticEntryClass.Get()));
	IFileManager& FileManager = IFileManager::Get();
	FString ImageFullPath = FString::Printf(TEXT("%s\\Content\\%s"), *FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()), *ImagePath);
	if (FileManager.FileExists(*ImageFullPath))
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
}