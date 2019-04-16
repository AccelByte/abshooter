// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "GameProfileWidgetStyle.h"

FGameProfileStyle::FGameProfileStyle()
{
}

FGameProfileStyle::~FGameProfileStyle()
{
}

const FName FGameProfileStyle::TypeName(TEXT("FGameProfileStyle"));

const FGameProfileStyle& FGameProfileStyle::GetDefault()
{
	static FGameProfileStyle Default;
	return Default;
}

void FGameProfileStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

