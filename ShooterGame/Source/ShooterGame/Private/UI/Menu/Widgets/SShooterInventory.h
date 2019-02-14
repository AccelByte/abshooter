// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "ShooterGame.h"

/** item type*/
UENUM()
enum class EInventoryItemType : uint8
{
	WEAPON UMETA(DisplayName = "Weapon"),
	AMMO UMETA(DisplayName = "Ammo"),
	COIN UMETA(DisplayName = "Coin")
};

/** inventory display information */
struct FInventoryEntry
{
	/** item id*/
	FString ItemId;

	/** item name*/
	FString Name;

	/** item image URL*/
	FString ImageURL;

	/** currency code*/
	FString CurrencyCode;

	/** currency type*/
	FString CurrencyType;

	/** item price*/
	int32 Price;

	/** item price*/
	int32 DiscountedPrice;

	/** item consumable flag*/
	bool Purchasable;

	/** item owned flag*/
	bool Owned = false;

	/** item type*/
	EInventoryItemType Type;

	/** item quantity*/
	int32 Quantity = 1;
};

//class declare
class SShooterInventory : public SCompoundWidget
{
public:
	SShooterInventory();

	SLATE_BEGIN_ARGS(SShooterInventory)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<ULocalPlayer >, PlayerOwner)
	SLATE_ARGUMENT(TSharedPtr<SWidget>, OwnerWidget)
	SLATE_ARGUMENT(FSimpleDelegate, OnBuyItemFinished)

	SLATE_END_ARGS()

	/** needed for every widget */
	void Construct(const FArguments& InArgs);

	/** if we want to receive focus */
	virtual bool SupportsKeyboardFocus() const override { return true; }

	/** Populates inventory item */
	void BuildInventoryItem();

	/** creates single item widget, called for every list item */
	TSharedRef<ITableRow> OnGenerateWidgetForTileView(TSharedPtr<FInventoryEntry> Item, const TSharedRef<STableViewBase>& OwnerTable);

	void EntrySelectionChanged(TSharedPtr<FInventoryEntry> InItem, ESelectInfo::Type SelectInfo);

	void OnInventoryMouseClick(TSharedPtr<FInventoryEntry> InItem);

protected:

	/** action bindings array */
	TArray< TSharedPtr<FInventoryEntry> > InventoryList;

	/** action bindings list slate widget */
	TSharedPtr < STileView< TSharedPtr<FInventoryEntry> > > InventoryListWidget;

	/** currently selected list item */
	TSharedPtr<FInventoryEntry> SelectedItem;

	/** pointer to our owner PC */
	TWeakObjectPtr<class ULocalPlayer> PlayerOwner;

	/** pointer to our parent widget */
	TSharedPtr<class SWidget> OwnerWidget;

	FSlateColorBrush ConfirmationBackgroundBrush;

	TSharedPtr<SWidget> DialogWidget;

	TSharedPtr<SWidget> LoadingDialogWidget;
	TSharedPtr<STextBlock> LoadingDialogText;

	TSharedPtr<SWidget> MessageDialogWidget;

	FThreadSafeCounter GetItemRequestCount = FThreadSafeCounter(0);

	FSimpleDelegate OnBuyItemFinished;

	void GetUserEntitlements();

	void ShowBuyConfirmationDialog(TSharedPtr<FInventoryEntry> InItem);
	void CloseConfirmationDialog();

	FReply OnBuyConfirm();
	FReply OnBuyCancel();

	void OnGetItemsByCriteria(const struct FAccelByteModelsItemPagingSlicedResult& Result);
	void OnGetItemsByCriteriaError(int32 Code, const FString& Message);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	void ShowLoadingDialog();
	void CloseLoadingDialog();

	void ShowMessageDialog(FString Message);
	void CloseMessageDialog();

	void OnBackFromPaymentBrowser(FString PaymentUrl);

	void OnFocusLost(const FFocusEvent& InFocusEvent);
	FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent);
};


