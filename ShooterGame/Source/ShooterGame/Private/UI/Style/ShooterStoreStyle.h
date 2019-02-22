// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SlateWidgetStyleContainerBase.h"
#include "ShooterStoreStyle.generated.h"

/**
 * Represents the appearance of an FShooterStore
 */
USTRUCT()
struct FShooterStoreStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FShooterStoreStyle();
	virtual ~FShooterStoreStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FShooterStoreStyle& GetDefault();

	UPROPERTY(EditAnywhere, Category = StoreItem)
		FSlateBrush HeaderItems;
	UPROPERTY(EditAnywhere, Category = StoreItem)
		FSlateBrush HeaderVirtualCoins;

	/**
	 * The text style
	 */
	UPROPERTY(EditAnywhere, Category = StoreItemText)
	FTextBlockStyle RealCurrencyTextStyle;

	UPROPERTY(EditAnywhere, Category = StoreButton)
	FButtonStyle BuyButtonStyle;

	UPROPERTY(EditAnywhere, Category = StoreButton)
	FButtonStyle BuyButtonWithIconStyle;
};


/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UShooterStoreWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_UCLASS_BODY()

public:
	/** The actual data describing the tile's appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FShooterStoreStyle StoreStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &StoreStyle);
	}
};
