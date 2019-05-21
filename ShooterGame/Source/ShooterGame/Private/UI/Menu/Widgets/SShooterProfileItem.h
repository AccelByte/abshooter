// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.
#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "SShooterGameProfile.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Http.h"
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "Utils/ImageUtils.h"

//class declare
class SShooterProfileItem : public STableRow< TSharedPtr<FAchievementEntry> >
{
public:
	SLATE_BEGIN_ARGS(SShooterProfileItem)
	{}
	/** end of slate attributes definition */
	SLATE_END_ARGS()

		/** needed for every widget */
		void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TWeakObjectPtr<class ULocalPlayer> PlayerOwner, TSharedPtr<FAchievementEntry> InItem);

protected:

private:
	/** pointer to Item */
	TWeakPtr<struct FAchievementEntry> Item;

	/** pointer to our owner PC */
	TWeakObjectPtr<class ULocalPlayer> PlayerOwner;

	FCacheBrush ImageBrush = nullptr;

	/** style for the inventory */
	const struct FShooterInventoryStyle *InventoryStyle;

	/** get content image*/
	const FSlateBrush* GetImage() const;

	/** getter for tile item background color */
	FSlateColor GetButtonBgColor() const;

	/** getter for tile item background color */
	FSlateColor GetTypeTextColor() const;

	/** getter for tile item background color */
	const FSlateBrush* GetBackgroundBrush() const;

	/** getter for tile item background color */
	const FSlateBrush* GetTypeBackgroundBrush() const;
	FSlateColor GetTypeBackgroundColor() const;

	void OnReceivedImage(FCacheBrush Image);
};
