#include "ShooterGame.h"
#include "SShooterStoreItem.h"
#include "ShooterStyle.h"
#include "ShooterInventoryWidgetStyle.h"
#include "ShooterStoreStyle.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"
#include "Utils/ImageUtils.h"

#define LOCTEXT_NAMESPACE "SShooterStoreItem"

SShooterStoreItem::~SShooterStoreItem()
{
}

void SShooterStoreItem::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TWeakObjectPtr<class ULocalPlayer> InPlayerOwner, TSharedPtr<FInventoryEntry> InItem)
{
	Item = InItem;
	PlayerOwner = InPlayerOwner;
	OnBuyItem = InArgs._OnBuyItem;

	STableRow< TSharedPtr<FInventoryEntry> >::Construct(STableRow::FArguments().ShowSelection(false).Padding(FMargin(0, 4.0f)), InOwnerTable);

	if (Item.IsValid()) 
	{
		InventoryStyle = &FShooterStyle::Get().GetWidgetStyle<FShooterInventoryStyle>("DefaultShooterInventoryStyle");
		StoreStyle = &FShooterStyle::Get().GetWidgetStyle<FShooterStoreStyle>("DefaultShooterStoreStyle");
		TSharedPtr<FInventoryEntry> item = Item.Pin();

		if (item->ImageURL.StartsWith("http")) 
		{
			// image placeholder
			ImageBrush = MakeShareable(new FSlateImageBrush(FPaths::ProjectContentDir() / "Slate/Images/ImageIcon.png", FVector2D(96, 96)));
			FShooterImageUtils::GetImage(item->ImageURL, FOnImageReceived::CreateSP(this, &SShooterStoreItem::OnReceivedImage));
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
				.Image(this, &SShooterStoreItem::GetBackgroundBrush)
				.ColorAndOpacity(this, &SShooterStoreItem::GetButtonBgColor)
			]
			+ SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			.Padding(16.0f, 16.0f)
			[
				SNew(SHorizontalBox)
#pragma region LeftBox
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.AutoWidth()
				[
					GetLeftWidget(Item.Pin().Get())
				]
#pragma endregion LeftBox
				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				[
					SNew(SScaleBox)
					.VAlign(VAlign_Fill)
					.HAlign(HAlign_Center)
					.Stretch(EStretch::ScaleToFit)
					[
						SNew(SImage)
						.Image(this, &SShooterStoreItem::GetImage)
					]
				]
			]
		];
	}
}

void SShooterStoreItem::OnReceivedImage(TSharedPtr<const FSlateBrush> Image)
{
	if (Image.IsValid())
	{
		ImageBrush = Image;
	}
}

TSharedRef<SWidget> SShooterStoreItem::GetPriceWidget(const FInventoryEntry* item) const
{
	if (!item->Purchasable && item->Owned)
	{
		return SNew(SBox);
	}
	else
	{
		// construct the price in string format, different format for REAL and VIRTUAL currency
		float Price = (item->CurrencyType == TEXT("REAL") ? item->Price / 100.00f : item->Price / 1.f);
		FString PriceString;
		PriceString.Append(item->CurrencyType == TEXT("REAL") ? item->CurrencyCode + TEXT("\n") : TEXT(""));
		PriceString.Append(FString::SanitizeFloat(Price, item->CurrencyType == TEXT("REAL") ? 2 : 0));

		return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		.AutoWidth()
		[
			item->CurrencyType != TEXT("REAL") // if VIRTUAL currency then show the coin image
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

TSharedRef<SWidget> SShooterStoreItem::GetLeftWidget(const FInventoryEntry* item) const
{
	if (item->Type == EInventoryItemType::COIN)
	{
		return SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Left)
			.AutoHeight()
			[
				SNew(STextBlock)
				.Margin(FMargin(5, 0))
				.TextStyle(&StoreStyle->RealCurrencyTextStyle)
				.Text(FText::FromString(GetPriceString(item)))
			]
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Left)
			.AutoHeight()
			[
				SNew(SButton)
				.ButtonStyle(&StoreStyle->BuyButtonStyle)
				.OnClicked(this, &SShooterStoreItem::OnBuyItemClick)
			];
	}
	else
	{
		return SNew(SVerticalBox)
			+ SVerticalBox::Slot()
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
						.Image(this, &SShooterStoreItem::GetTypeBackgroundBrush)
						.ColorAndOpacity(this, &SShooterStoreItem::GetTypeBackgroundColor)
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
					.ColorAndOpacity(this, &SShooterStoreItem::GetTypeTextColor)
				]
			]
			+ SVerticalBox::Slot() // Name
			.AutoHeight()
			[
				SNew(STextBlock)
				.TextStyle(&InventoryStyle->NameTextStyle)
				.Text(FText::FromString(item->Name))
			]
			+ SVerticalBox::Slot() // Price
			.AutoHeight()
			[
				SNew(STextBlock)
				.TextStyle(&InventoryStyle->PriceTextStyle)
				.Text(FText::FromString(GetPriceString(item)))
			]
			+ SVerticalBox::Slot() // Price
			.HAlign(HAlign_Left)
			.AutoHeight()
			[
				SNew(SButton)
				.ButtonStyle(&StoreStyle->BuyButtonWithIconStyle)
				.OnClicked(this, &SShooterStoreItem::OnBuyItemClick)
			];
	}
}

FString SShooterStoreItem::GetPriceString(const FInventoryEntry* item) const
{
	float Price = (item->CurrencyType == TEXT("REAL") ? item->Price / 100.00f : item->Price / 1.f);
	FString PriceString;
	if (item->CurrencyType == TEXT("REAL"))
	{
		PriceString.Append(item->CurrencyCode);
	}
	else
	{
		PriceString.Append("VC");
	}
	PriceString.Append(" ");
	PriceString.Append(FString::SanitizeFloat(Price, item->CurrencyType == TEXT("REAL") ? 2 : 0));
	return PriceString;
}

const FSlateBrush* SShooterStoreItem::GetImage() const
{
	return ImageBrush.Get();
}

FSlateColor SShooterStoreItem::GetButtonBgColor() const
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

FSlateColor SShooterStoreItem::GetTypeTextColor() const
{
	return /*IsSelected() ? FLinearColor(0.216f, 0.486f, 0.506f) : */FLinearColor(0.061f, 0.144f, 0.161f);
}

const FSlateBrush* SShooterStoreItem::GetBackgroundBrush() const
{
	return IsSelected() ? &InventoryStyle->BackgroundSelectedBrush : &InventoryStyle->BackgroundBrush;
}

const FSlateBrush* SShooterStoreItem::GetTypeBackgroundBrush() const
{
	return IsSelected() ? &InventoryStyle->TypeSelectedBackgroundBrush : &InventoryStyle->TypeBackgroundBrush;
}

FSlateColor SShooterStoreItem::GetTypeBackgroundColor() const
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

EVisibility SShooterStoreItem::GetCartIconVisibility() const
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

FReply SShooterStoreItem::OnBuyItemClick() const
{
	if (Item.IsValid())
	{
		OnBuyItem.ExecuteIfBound(Item.Pin());
	}
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE