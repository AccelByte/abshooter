// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ShooterGame.h"
#include "ShooterInventoryWidgetStyle.h"

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
	OutBrushes.Add(&BackgroundBrush);
	OutBrushes.Add(&TypeBackgroundBrush);
	OutBrushes.Add(&CoinImage);
}


UShooterInventoryWidgetStyle::UShooterInventoryWidgetStyle( const FObjectInitializer& ObjectInitializer )
	: Super(ObjectInitializer)
{
	
}
