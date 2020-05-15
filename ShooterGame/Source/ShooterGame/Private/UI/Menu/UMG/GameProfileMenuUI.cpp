// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "GameProfileMenuUI.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/TileView.h"

bool UGameProfileMenuUI::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(DisplayNameField != nullptr)) return false;
	if (!ensure(AvatarImage != nullptr)) return false;
	if (!ensure(StatisticTileView != nullptr)) return false;
	if (!ensure(AchievementTileView != nullptr)) return false;
	if (!ensure(StatisticEmptyText != nullptr)) return false;
	if (!ensure(AchievementEmptyText != nullptr)) return false;

	return true;
}

void UGameProfileMenuUI::SetDisplayName(FString DisplayName)
{
	DisplayNameField->SetText(FText::FromString(DisplayName));
}

void UGameProfileMenuUI::SetAvatarImage(FSlateBrush AvatarImage)
{
	this->AvatarImage->SetBrush(AvatarImage);
}

void UGameProfileMenuUI::UpdateGameProfileAchievement(TArray<UAchievementEntryUI*> AchievementList)
{
	if (AchievementList.Num() != 0)
	{
		AchievementTileView->SetListItems(AchievementList);
		AchievementTileView->SetVisibility(ESlateVisibility::Visible);
		AchievementEmptyText->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		AchievementTileView->SetVisibility(ESlateVisibility::Collapsed);
		AchievementEmptyText->SetVisibility(ESlateVisibility::Visible);
	}
}

void UGameProfileMenuUI::UpdateGameProfileStatistic(TArray<UStatisticEntryUI*> StatisticList)
{
	if (StatisticList.Num() != 0)
	{
		StatisticTileView->SetListItems(StatisticList);
		StatisticTileView->SetVisibility(ESlateVisibility::Visible);
		StatisticEmptyText->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		StatisticTileView->SetVisibility(ESlateVisibility::Collapsed);
		StatisticEmptyText->SetVisibility(ESlateVisibility::Visible);
	}
}
