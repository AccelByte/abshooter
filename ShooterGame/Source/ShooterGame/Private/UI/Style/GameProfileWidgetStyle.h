// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"

#include "GameProfileWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct FGameProfileStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FGameProfileStyle();
	virtual ~FGameProfileStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FGameProfileStyle& GetDefault();

	/**
	 * The brush used for the background of profile achievement items
	 */
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush AchievementBackgroundBrush;
	FGameProfileStyle& SetAchievementBackgroundBrush(const FSlateBrush& InAchievementBackgroundBrush){ AchievementBackgroundBrush = InAchievementBackgroundBrush; return *this; }

	/**
	 * The brush used for the background of profile stats items
	 */
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush StatsBackgroundBrush;
	FGameProfileStyle& SetStatsBackgroundBrush(const FSlateBrush& InStatsBackgroundBrush)
	{
		StatsBackgroundBrush = InStatsBackgroundBrush; return *this;
	}

	/**
	 * The brush used for the background of profile avatar items
	 */
	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateBrush AvatarBackgroundBrush;
	FGameProfileStyle& SetAvatarBackgroundBrush(const FSlateBrush& InAvatarBackgroundBrush)
	{
		AvatarBackgroundBrush = InAvatarBackgroundBrush; return *this;
	}

	UPROPERTY(EditAnywhere, Category = StoreItem)
	FSlateBrush HeaderProfileName;

	UPROPERTY(EditAnywhere, Category = StoreItem)
	FSlateBrush HeaderStats;

	UPROPERTY(EditAnywhere, Category = StoreItem)
	FSlateBrush HeaderAchievement;

	UPROPERTY(EditAnywhere, Category = StoreItem)
	FSlateBrush IconMVP;

	UPROPERTY(EditAnywhere, Category = StoreItem)
	FSlateBrush IconMatchPlayed;

	UPROPERTY(EditAnywhere, Category = StoreItem)
	FSlateBrush IconKills;

	UPROPERTY(EditAnywhere, Category = StoreItem)
	FSlateBrush IconDeaths;

	UPROPERTY(EditAnywhere, Category = StoreItem)
	FSlateBrush Achievement1;

	UPROPERTY(EditAnywhere, Category = StoreItem)
	FSlateBrush Achievement2;

	UPROPERTY(EditAnywhere, Category = StoreItem)
	FSlateBrush Achievement3;

	UPROPERTY(EditAnywhere, Category = StoreItem)
	FSlateBrush Achievement4;

};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UGameProfileWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FGameProfileStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
