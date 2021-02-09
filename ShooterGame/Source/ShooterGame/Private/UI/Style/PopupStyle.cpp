// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PopupStyle.h"
#include "ShooterGame.h"

FPopupStyle::FPopupStyle()
{
}

FPopupStyle::~FPopupStyle()
{
}

const FName FPopupStyle::TypeName(TEXT("FPopupStyle"));

const FPopupStyle& FPopupStyle::GetDefault()
{
	static FPopupStyle Default;
	return Default;
}

void FPopupStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
}


UPopupWidgetStyle::UPopupWidgetStyle( const FObjectInitializer& ObjectInitializer )
	: Super(ObjectInitializer)
{
	
}
