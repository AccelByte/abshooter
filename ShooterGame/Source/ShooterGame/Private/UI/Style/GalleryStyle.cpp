// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "ShooterGame.h"
#include "GalleryStyle.h"

FGalleryStyle::FGalleryStyle()
{
}

FGalleryStyle::~FGalleryStyle()
{
}

const FName FGalleryStyle::TypeName(TEXT("FGalleryStyle"));

const FGalleryStyle& FGalleryStyle::GetDefault()
{
	static FGalleryStyle Default;
	return Default;
}

UGalleryStyleWidgetStyle::UGalleryStyleWidgetStyle(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}
