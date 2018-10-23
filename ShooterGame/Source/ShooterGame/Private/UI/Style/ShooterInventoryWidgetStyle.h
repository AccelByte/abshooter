// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SlateWidgetStyleContainerBase.h"
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
	 * The brush used for the item background
	 */	
	UPROPERTY(EditAnywhere, Category=Appearance)
	FSlateBrush BackgroundBrush;
	FShooterInventoryStyle& SetBackgroundBrush(const FSlateBrush& InBackgroundBrush) { BackgroundBrush = InBackgroundBrush; return *this; }

    /**
     * The brush used for the item background
     */
    UPROPERTY(EditAnywhere, Category = Appearance)
        FSlateBrush TypeBackgroundBrush;
    FShooterInventoryStyle& SetTypeBackgroundBrush(const FSlateBrush& InTypeBackgroundBrush) { TypeBackgroundBrush = InTypeBackgroundBrush; return *this; }

    /**
     * The brush used for the item background
     */
    UPROPERTY(EditAnywhere, Category = Appearance)
        FSlateBrush CoinImage;
    FShooterInventoryStyle& SetCoinImage(const FSlateBrush& InCoinImage) { CoinImage = InCoinImage; return *this; }

    /**
     * The type text style
     */
    UPROPERTY(EditAnywhere, Category = Text)
        FTextBlockStyle TypeTextStyle;
    FShooterInventoryStyle& SetTypeTextStyle(const FTextBlockStyle& InTypeTextStyle) { TypeTextStyle = InTypeTextStyle; return *this; }

    /**
     * The amount text style
     */
    UPROPERTY(EditAnywhere, Category = Text)
        FTextBlockStyle AmountTextStyle;
    FShooterInventoryStyle& SetAmountTextStyle(const FTextBlockStyle& InAmountTextStyle) { AmountTextStyle = InAmountTextStyle; return *this; }

    /**
     * The name text style
     */
    UPROPERTY(EditAnywhere, Category = Text)
        FTextBlockStyle NameTextStyle;
    FShooterInventoryStyle& SetNameTextStyle(const FTextBlockStyle& InNameTextStyle) { NameTextStyle = InNameTextStyle; return *this; }

    /**
     * The price text style
     */
    UPROPERTY(EditAnywhere, Category = Text)
        FTextBlockStyle PriceTextStyle;
    FShooterInventoryStyle& SetPriceTextStyle(const FTextBlockStyle& InPriceTextStyle) { PriceTextStyle = InPriceTextStyle; return *this; }

    /**
     * The owned text style
     */
    UPROPERTY(EditAnywhere, Category = Text)
        FTextBlockStyle OwnedTextStyle;
    FShooterInventoryStyle& SetOwnedTextStyle(const FTextBlockStyle& InOwnedTextStyle) { OwnedTextStyle = InOwnedTextStyle; return *this; }
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
