// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ShooterStoreStyle.h"
#include "ShooterGame.h"

FShooterStoreStyle::FShooterStoreStyle()
{
}

FShooterStoreStyle::~FShooterStoreStyle()
{
}

const FName FShooterStoreStyle::TypeName(TEXT("FShooterStoreStyle"));

const FShooterStoreStyle& FShooterStoreStyle::GetDefault()
{
	static FShooterStoreStyle Default;
	return Default;
}

void FShooterStoreStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
}


UShooterStoreWidgetStyle::UShooterStoreWidgetStyle( const FObjectInitializer& ObjectInitializer )
	: Super(ObjectInitializer)
{
	
}
