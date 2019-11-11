#include "ShooterGame.h"
#include "SShooterInventoryItem.h"
#include "ShooterStyle.h"
#include "ShooterInventoryWidgetStyle.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"

#define LOCTEXT_NAMESPACE "SShooterInventoryItem"

void SShooterInventoryItem::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TWeakObjectPtr<class ULocalPlayer> InPlayerOwner, TSharedPtr<FInventoryEntry> InItem)
{
	Item = InItem;
	PlayerOwner = InPlayerOwner;

	STableRow< TSharedPtr<FInventoryEntry> >::Construct(STableRow::FArguments().ShowSelection(false).Padding(FMargin(5.0f)), InOwnerTable);

	if (Item.IsValid()) 
	{
		InventoryStyle = &FShooterStyle::Get().GetWidgetStyle<FShooterInventoryStyle>("DefaultShooterInventoryStyle");
		TSharedPtr<FInventoryEntry> item = Item.Pin();

		if (item->ImageURL.StartsWith("http")) 
		{
			// image placeholder
			ImageBrush = MakeShareable(new FSlateImageBrush(FPaths::ProjectContentDir() / "Slate/Images/ImageIcon.png", FVector2D(96, 96)));

			FShooterImageUtils::GetImage(item->ImageURL, FOnImageReceived::CreateSP(this, &SShooterInventoryItem::OnReceivedImage));
		}
		else
		{
			ImageBrush = MakeShareable(new FSlateImageBrush(FPaths::ProjectContentDir() / item->ImageURL, FVector2D(96, 96)));
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
				.Image(this, &SShooterInventoryItem::GetBackgroundBrush)
				.ColorAndOpacity(this, &SShooterInventoryItem::GetButtonBgColor)
			]
			+ SOverlay::Slot()
			.Padding(FMargin(20.0f))
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				[
					SNew(SScaleBox)
					.VAlign(VAlign_Fill)
					.HAlign(HAlign_Center)
					.Stretch(EStretch::ScaleToFit)
					[
						SNew(SImage)
						.Image(this, &SShooterInventoryItem::GetImage)
					]
				]
				+ SVerticalBox::Slot() // Type
				.AutoHeight()
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
					.VAlign(VAlign_Top)
					.HAlign(HAlign_Left) // Type background
					[
						SNew(SBox)
						.HAlign(HAlign_Fill)
						.WidthOverride(64)
						[
							SNew(SImage)
							.Image(this, &SShooterInventoryItem::GetTypeBackgroundBrush)
							.ColorAndOpacity(this, &SShooterInventoryItem::GetTypeBackgroundColor)
						]
					]
					+ SOverlay::Slot()
					.VAlign(VAlign_Top)
					.HAlign(HAlign_Left)
					[
						SNew(STextBlock)
						.Margin(FMargin(5, 1, 0, 0))
						.TextStyle(&InventoryStyle->TypeTextStyle)
						.Text(GetItemTypeAsText(item->Type))
						.ColorAndOpacity(this, &SShooterInventoryItem::GetTypeTextColor)
					]
				]
				+ SVerticalBox::Slot() // Name
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Left)
				.AutoHeight()
				[
					SNew(STextBlock)
					.TextStyle(&InventoryStyle->NameTextStyle)
					.Text(FText::FromString(item->Name))
				]
				+ SVerticalBox::Slot() // Owned
				.AutoHeight()
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
					[
						SNew(SImage)
						.Image(&InventoryStyle->BoxOwnedBrush)
					]
					+ SOverlay::Slot()
					.VAlign(VAlign_Center)
					.Padding(FMargin(16.0f, 0, 0, 0))
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.AutoWidth()
						[
							SNew(STextBlock)
							.Text(FText::FromString(TEXT("OWNED: ")))
							.TextStyle(&InventoryStyle->OwnedTextStyle)
						]
						+ SHorizontalBox::Slot()
						.AutoWidth()
						[
							SNew(STextBlock)
							.TextStyle(&InventoryStyle->AmountTextStyle)
							.Text(FText::AsNumber(item->Quantity))
						]
					]
				]
			]
		];
	}
}

TSharedRef<SWidget> SShooterInventoryItem::GetPriceWidget(const FInventoryEntry* item) const
{
	if (!item->Purchasable && item->Owned)
	{
		return SNew(SBox);
	}
	else
	{
		// construct the price in string format, different format for REAL and VIRTUAL currency
		float Price = (item->CurrencyType == EAccelByteItemCurrencyType::REAL ? item->Price / 100.00f : item->Price / 1.f);
		FString PriceString;
		PriceString.Append(item->CurrencyType == EAccelByteItemCurrencyType::REAL ? item->CurrencyCode + TEXT("\n") : TEXT(""));
		PriceString.Append(FString::SanitizeFloat(Price, item->CurrencyType == EAccelByteItemCurrencyType::REAL ? 2 : 0));

		return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		.AutoWidth()
		[
			item->CurrencyType != EAccelByteItemCurrencyType::REAL // if VIRTUAL currency then show the coin image
			?
			SNew(SImage).Image(&InventoryStyle->CoinImage)
			:
			SNew(SImage).Visibility(EVisibility::Collapsed)
		]
		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		.AutoWidth()
		[
			SNew(STextBlock)
			.Margin(FMargin(5, 0))
			.TextStyle(&InventoryStyle->PriceTextStyle)
			.Text(FText::FromString(PriceString))
		];
	}
}

const FSlateBrush* SShooterInventoryItem::GetImage() const
{
	return ImageBrush.Get();
}

FSlateColor SShooterInventoryItem::GetButtonBgColor() const
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

FSlateColor SShooterInventoryItem::GetTypeTextColor() const
{
	return /*IsSelected() ? FLinearColor(0.216f, 0.486f, 0.506f) : */FLinearColor(0.061f, 0.144f, 0.161f);
}

const FSlateBrush* SShooterInventoryItem::GetBackgroundBrush() const
{
	return IsSelected() ? &InventoryStyle->BackgroundSelectedBrush : &InventoryStyle->BackgroundBrush;
}

const FSlateBrush* SShooterInventoryItem::GetTypeBackgroundBrush() const
{
	return IsSelected() ? &InventoryStyle->TypeSelectedBackgroundBrush : &InventoryStyle->TypeBackgroundBrush;
}

FSlateColor SShooterInventoryItem::GetTypeBackgroundColor() const
{
	if (Item.IsValid())
	{
		switch (Item.Pin()->Type)
		{
		case EInventoryItemType::AMMO:
			return FLinearColor(1.0f, 0.706f, 0.004f);
		case EInventoryItemType::WEAPON:
			return FLinearColor(0.439f, 0.91f, 1.0f);
		}
	}
	return FLinearColor(0.439f, 0.91f, 1.0f);
}

EVisibility SShooterInventoryItem::GetCartIconVisibility() const
{
	if (Item.IsValid())
	{
		if (IsSelected() && Item.Pin()->Purchasable)
		{
			return EVisibility::Visible;
		}
	}

	return EVisibility::Collapsed;
}

void SShooterInventoryItem::OnReceivedImage(FCacheBrush Image)
{
	ImageBrush = Image;
}

#undef LOCTEXT_NAMESPACE