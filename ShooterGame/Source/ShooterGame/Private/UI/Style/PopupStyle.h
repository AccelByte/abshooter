// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SlateWidgetStyleContainerBase.h"
#include "PopupStyle.generated.h"

/**
 * Represents the appearance of an FShooterStore
 */
USTRUCT()
struct FPopupStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FPopupStyle();
	virtual ~FPopupStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FPopupStyle& GetDefault();

	UPROPERTY(EditAnywhere, Category = Popup)
		FSlateBrush OuterBorder;
	UPROPERTY(EditAnywhere, Category = Popup)
		FSlateBrush InnerBox;
	UPROPERTY(EditAnywhere, Category = Popup)
		FButtonStyle ConfirmButtonStyle;
	UPROPERTY(EditAnywhere, Category = Popup)
		FButtonStyle CancelButtonStyle;
	UPROPERTY(EditAnywhere, Category = Text)
		FTextBlockStyle MessageStyle;
	UPROPERTY(EditAnywhere, Category = Text)
		FTextBlockStyle ButtonText;
};


/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UPopupWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_UCLASS_BODY()

public:
	/** The actual data describing the tile's appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FPopupStyle StoreStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &StoreStyle);
	}
};
