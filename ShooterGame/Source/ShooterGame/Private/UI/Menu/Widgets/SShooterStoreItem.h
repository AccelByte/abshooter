#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "SShooterInventory.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Http.h"
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "Utils/ImageUtils.h"

DECLARE_DELEGATE_OneParam(FOnBuyItem, TSharedPtr<FInventoryEntry>);

//class declare
class SShooterStoreItem : public STableRow< TSharedPtr<FInventoryEntry> >
{
public:
	SLATE_BEGIN_ARGS(SShooterStoreItem){}
	/** end of slate attributes definition */
	SLATE_EVENT(FOnBuyItem, OnBuyItem)
	SLATE_END_ARGS()

	~SShooterStoreItem();

	/** needed for every widget */
	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TWeakObjectPtr<class ULocalPlayer> PlayerOwner, TSharedPtr<FInventoryEntry> InItem);

protected:

private:
	/** pointer to Item */
	TWeakPtr<struct FInventoryEntry> Item;

	/** pointer to our owner PC */
	TWeakObjectPtr<class ULocalPlayer> PlayerOwner;

	FCacheBrush ImageBrush = nullptr;

	/** style for the inventory */
	const struct FShooterInventoryStyle *InventoryStyle;
	const struct FShooterStoreStyle *StoreStyle;

	TSharedRef<SWidget> GetPriceWidget(const FInventoryEntry * item) const;

	TSharedRef<SWidget> GetLeftWidget(const FInventoryEntry * item) const;

	FString GetPriceString(const FInventoryEntry * item) const;

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

	/** getter for cart icon visibility */
	EVisibility GetCartIconVisibility() const;

	FOnBuyItem OnBuyItem;

	FReply OnBuyItemClick() const;

	void OnReceivedImage(FCacheBrush Image);
};
