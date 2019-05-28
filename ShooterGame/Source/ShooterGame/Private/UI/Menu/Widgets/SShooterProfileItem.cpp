// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "ShooterGame.h"
#include "SShooterProfileItem.h"
#include "ShooterStyle.h"
#include "ShooterInventoryWidgetStyle.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"
#include "GameProfileWidgetStyle.h"

#define LOCTEXT_NAMESPACE "SShooterProfileItem"

void SShooterProfileItem::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TWeakObjectPtr<class ULocalPlayer> InPlayerOwner, TSharedPtr<FAchievementEntry> InItem)
{
	Item = InItem;
	PlayerOwner = InPlayerOwner;

	STableRow< TSharedPtr<FAchievementEntry> >::Construct(STableRow::FArguments().ShowSelection(false).Padding(FMargin(5.0f)), InOwnerTable);

	if (Item.IsValid())
	{
		InventoryStyle = &FShooterStyle::Get().GetWidgetStyle<FShooterInventoryStyle>("DefaultShooterInventoryStyle");
		TSharedPtr<FAchievementEntry> item = Item.Pin();

		if (item->ImageURL.StartsWith("http"))
		{
			// image placeholder
			ImageBrush = MakeShareable(new FSlateImageBrush(FPaths::ProjectContentDir() / "Slate/Images/ImageIcon.png", FVector2D(96, 96)));

			FShooterImageUtils::GetImage(item->ImageURL, FOnImageReceived::CreateSP(this, &SShooterProfileItem::OnReceivedImage));
		}
		else
		{
			FString ImagePath = FPaths::ProjectContentDir() / item->ImageURL;
			FName BrushName = FName(*ImagePath);
			ImageBrush = MakeShareable(new FSlateDynamicImageBrush(BrushName, FVector2D(310, 191)));
		}

		ChildSlot
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				.VAlign(VAlign_Fill)
				.HAlign(HAlign_Fill) // Background
				[
					SNew(SImage)
					.Image(&InventoryStyle->BackgroundBrush)
				]
				+ SOverlay::Slot()
				.VAlign(VAlign_Fill)
				.HAlign(HAlign_Fill) // Background
				[
					SNew(SImage)
					.Image(this, &SShooterProfileItem::GetBackgroundBrush)
					.ColorAndOpacity(this, &SShooterProfileItem::GetButtonBgColor)
				]
				+ SOverlay::Slot()
				[
					SNew(SScaleBox)
					.VAlign(VAlign_Fill)
					.HAlign(HAlign_Center)
					.Stretch(EStretch::ScaleToFitY)
					[
						SNew(SImage)
						.Image(this, &SShooterProfileItem::GetImage)
					]
				]
				+ SOverlay::Slot()
				[
					SNew(SOverlay)
					+ SOverlay::Slot() // Name
					.VAlign(VAlign_Bottom)
					.HAlign(HAlign_Center)
					.Padding(0,0,0,15)
					[
						SNew(STextBlock)
						.TextStyle(FShooterStyle::Get(),"ShooterGame.ProfileAchieveNameTextStyle")
						.Text(FText::FromString(item->Name))
					]
				]
			];
	}
}

const FSlateBrush* SShooterProfileItem::GetImage() const
{
	return ImageBrush.Get();
}

FSlateColor SShooterProfileItem::GetButtonBgColor() const
{
	const float MinAlpha = 0.1f;
	const float MaxAlpha = 1.f;
	const float AnimSpeedModifier = 1.5f;

	float AnimPercent = 0.f;
	ULocalPlayer* const Player = PlayerOwner.Get();
	if (Player)
	{
		// @fixme, need a world get delta time?
		UWorld* const World = Player->GetWorld();
		if (World)
		{
			const float GameTime = World->GetRealTimeSeconds();
			AnimPercent = FMath::Abs(FMath::Sin(GameTime*AnimSpeedModifier));
		}
	}

	const float BgAlpha = IsSelected() ? FMath::Lerp(MinAlpha, MaxAlpha, AnimPercent) : 0.0f;
	return FLinearColor(1.f, 1.f, 1.f, BgAlpha);
}

FSlateColor SShooterProfileItem::GetTypeTextColor() const
{
	return /*IsSelected() ? FLinearColor(0.216f, 0.486f, 0.506f) : */FLinearColor(0.061f, 0.144f, 0.161f);
}

const FSlateBrush* SShooterProfileItem::GetBackgroundBrush() const
{
	return IsSelected() ? &InventoryStyle->BackgroundSelectedBrush : &InventoryStyle->BackgroundBrush;
}

const FSlateBrush* SShooterProfileItem::GetTypeBackgroundBrush() const
{
	return IsSelected() ? &InventoryStyle->TypeSelectedBackgroundBrush : &InventoryStyle->TypeBackgroundBrush;
}

FSlateColor SShooterProfileItem::GetTypeBackgroundColor() const
{
	return FLinearColor(0.439f, 0.91f, 1.0f);
}

void SShooterProfileItem::OnReceivedImage(FCacheBrush Image)
{
	ImageBrush = Image;
}

#undef LOCTEXT_NAMESPACE