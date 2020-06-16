// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "GameProfileMenuUI.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/TileView.h"

FCriticalSection GameProfileMenuUIMutex;

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

void UGameProfileMenuUI::SetAvatarImage(FSlateBrush Image)
{
	AvatarImage->SetBrush(Image);
}

void UGameProfileMenuUI::UpdateAchievementList(TArray<UAchievementEntryUI*> AchievementList)
{
	if (this == NULL) return;

	FScopeLock Lock(&GameProfileMenuUIMutex);

	AchievementTileView->SetListItems(AchievementList);
	if (AchievementList.Num() != 0)
	{
		AchievementEmptyText->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		AchievementEmptyText->SetVisibility(ESlateVisibility::Visible);
	}
}

void UGameProfileMenuUI::UpdateStatisticList(TArray<UStatisticEntryUI*> StatisticList)
{
	FScopeLock Lock(&GameProfileMenuUIMutex);

	StatisticTileView->SetListItems(StatisticList);
	if (StatisticList.Num() != 0)
	{
		StatisticEmptyText->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		StatisticEmptyText->SetVisibility(ESlateVisibility::Visible);
	}
	StatisticTileView->RegenerateAllEntries();
}
