// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Styling/SlateWidgetStyleContainerBase.h"
#include "ShooterInventoryWidgetStyle.generated.h"

/**
 * Represents the appearance of an FShooterInventory
 */
USTRUCT()
struct FShooterInventoryStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FShooterInventoryStyle();
	virtual ~FShooterInventoryStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FShooterInventoryStyle& GetDefault();

	/**
	 * The brush used for the page background
	 */
	UPROPERTY(EditAnywhere, Category = Inventory)
	FSlateBrush PageBackgroundBrush;
	FShooterInventoryStyle& SetPageBackgroundBrush(const FSlateBrush& InBrush) { PageBackgroundBrush = InBrush; return *this; }

	/**
	 * The brush used for the item background
	 */	
	UPROPERTY(EditAnywhere, Category=InventoryItem)
	FSlateBrush BackgroundBrush;
	FShooterInventoryStyle& SetBackgroundBrush(const FSlateBrush& InBrush) { BackgroundBrush = InBrush; return *this; }

	/**
	 * The brush used for the item selected background
	 */
	UPROPERTY(EditAnywhere, Category = InventoryItem)
		FSlateBrush BackgroundSelectedBrush;
	FShooterInventoryStyle& SetBackgroundSelectedBrush(const FSlateBrush& InBrush) { BackgroundSelectedBrush = InBrush; return *this; }

	/**
	 * The brush used for the item background
	 */
	UPROPERTY(EditAnywhere, Category = InventoryItem)
		FSlateBrush TypeBackgroundBrush;
	FShooterInventoryStyle& SetTypeBackgroundBrush(const FSlateBrush& InBrush) { TypeBackgroundBrush = InBrush; return *this; }

	/**
	 * The brush used for the item background
	 */
	UPROPERTY(EditAnywhere, Category = InventoryItem)
		FSlateBrush TypeSelectedBackgroundBrush;
	FShooterInventoryStyle& SetTypeSelectedBackgroundBrush(const FSlateBrush& InBrush) { TypeSelectedBackgroundBrush = InBrush; return *this; }

	/**
	 * The brush used for the item background
	 */
	UPROPERTY(EditAnywhere, Category = InventoryItem)
		FSlateBrush LockedBackgroundBrush;
	FShooterInventoryStyle& SetLockedBackgroundBrush(const FSlateBrush& InBrush) { LockedBackgroundBrush = InBrush; return *this; }

	/**
	 * The brush used for the item background
	 */
	UPROPERTY(EditAnywhere, Category = InventoryItem)
		FSlateBrush BoxOwnedBrush;
	FShooterInventoryStyle& SetBoxOwnedBrush(const FSlateBrush& InBrush) { BoxOwnedBrush = InBrush; return *this; }

	/**
	 * The brush used for the item background
	 */
	UPROPERTY(EditAnywhere, Category = InventoryItem)
		FSlateBrush CoinImage;
	FShooterInventoryStyle& SetCoinImage(const FSlateBrush& InBrush) { CoinImage = InBrush; return *this; }

	/**
	 * The brush used for the item background
	 */
	UPROPERTY(EditAnywhere, Category = InventoryItem)
		FSlateBrush CartImage;
	FShooterInventoryStyle& SetCartImage(const FSlateBrush& InBrush) { CartImage = InBrush; return *this; }

	/**
	 * The type text style
	 */
	UPROPERTY(EditAnywhere, Category = InventoryItemText)
		FTextBlockStyle TypeTextStyle;
	FShooterInventoryStyle& SetTypeTextStyle(const FTextBlockStyle& InTextStyle) { TypeTextStyle = InTextStyle; return *this; }

	/**
	 * The amount text style
	 */
	UPROPERTY(EditAnywhere, Category = InventoryItemText)
		FTextBlockStyle AmountTextStyle;
	FShooterInventoryStyle& SetAmountTextStyle(const FTextBlockStyle& InTextStyle) { AmountTextStyle = InTextStyle; return *this; }

	/**
	 * The name text style
	 */
	UPROPERTY(EditAnywhere, Category = InventoryItemText)
		FTextBlockStyle NameTextStyle;
	FShooterInventoryStyle& SetNameTextStyle(const FTextBlockStyle& InTextStyle) { NameTextStyle = InTextStyle; return *this; }

	/**
	 * The price text style
	 */
	UPROPERTY(EditAnywhere, Category = InventoryItemText)
		FTextBlockStyle PriceTextStyle;
	FShooterInventoryStyle& SetPriceTextStyle(const FTextBlockStyle& InTextStyle) { PriceTextStyle = InTextStyle; return *this; }

	/**
	 * The owned text style
	 */
	UPROPERTY(EditAnywhere, Category = InventoryItemText)
		FTextBlockStyle OwnedTextStyle;
	FShooterInventoryStyle& SetOwnedTextStyle(const FTextBlockStyle& InTextStyle) { OwnedTextStyle = InTextStyle; return *this; }

	UPROPERTY(EditAnywhere, Category = InventoryItem)
	FScrollBarStyle ScrollBarStyle;
};


/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UShooterInventoryWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_UCLASS_BODY()

public:
	/** The actual data describing the tile's appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FShooterInventoryStyle InventoryStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &InventoryStyle);
	}
};
