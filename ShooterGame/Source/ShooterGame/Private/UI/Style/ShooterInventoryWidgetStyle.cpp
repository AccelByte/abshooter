// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ShooterInventoryWidgetStyle.h"
#include "ShooterGame.h"

FShooterInventoryStyle::FShooterInventoryStyle()
{
}

FShooterInventoryStyle::~FShooterInventoryStyle()
{
}

const FName FShooterInventoryStyle::TypeName(TEXT("FShooterInventoryStyle"));

const FShooterInventoryStyle& FShooterInventoryStyle::GetDefault()
{
	static FShooterInventoryStyle Default;
	return Default;
}

void FShooterInventoryStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	OutBrushes.Add(&PageBackgroundBrush);
	OutBrushes.Add(&BackgroundBrush);
	OutBrushes.Add(&TypeBackgroundBrush);
	OutBrushes.Add(&CoinImage);
	OutBrushes.Add(&BoxOwnedBrush);
}


UShooterInventoryWidgetStyle::UShooterInventoryWidgetStyle( const FObjectInitializer& ObjectInitializer )
	: Super(ObjectInitializer)
{
	
}
