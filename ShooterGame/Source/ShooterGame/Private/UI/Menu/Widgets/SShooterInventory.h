// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "ShooterGame.h"

/** item type*/
UENUM()
enum class EItemType : uint8
{
	WEAPON UMETA(DisplayName = "Weapon"),
	AMMO UMETA(DisplayName = "Ammo")
};

/** inventory display information */
struct FInventoryEntry
{
	/** item name*/
	FString Name;

	/** item image URL*/
	FString ImageURL;

	/** item price*/
	int32 Price;

	/** item consumable flag*/
	bool Consumable;

	/** item owned flag*/
	bool Owned;

	/** item type*/
	EItemType Type;

	/** item amount*/
	int32 Amount = 1;
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

	void ShowBuyConfirmationDialog(TSharedPtr<FInventoryEntry> InItem);
	void CloseConfirmationDialog();

	FReply OnBuyConfirm();
	FReply OnBuyCancel();

};


