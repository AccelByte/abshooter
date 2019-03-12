// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "ShooterGame.h"
#include "Models/ShooterInventory.h"
#include "Runtime/Networking/Public/Common/TcpListener.h"

//class declare
class SShooterStore : public SCompoundWidget
{
public:
	SShooterStore();

	SLATE_BEGIN_ARGS(SShooterStore)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<ULocalPlayer >, PlayerOwner)
	SLATE_ARGUMENT(TSharedPtr<SWidget>, OwnerWidget)
	SLATE_ARGUMENT(FSimpleDelegate, OnBuyItemFinished)
	SLATE_ARGUMENT(TWeakPtr<class SShooterCoinsWidget>, CoinsWidget)

	SLATE_END_ARGS()

	/** needed for every widget */
	void Construct(const FArguments& InArgs);

	/** if we want to receive focus */
	virtual bool SupportsKeyboardFocus() const override { return true; }

	/** Populates inventory item */
	void BuildInventoryItem();

	/** creates single item widget, called for every list item */
	TSharedRef<ITableRow> OnGenerateWidgetForTileView(TSharedPtr<FInventoryEntry> Item, const TSharedRef<STableViewBase>& OwnerTable);
	TSharedRef<ITableRow> OnGenerateCashWidgetForTileView(TSharedPtr<FInventoryEntry> Item, const TSharedRef<STableViewBase>& OwnerTable);

	void EntrySelectionChanged(TSharedPtr<FInventoryEntry> InItem, ESelectInfo::Type SelectInfo);
	void CashEntrySelectionChanged(TSharedPtr<FInventoryEntry> InItem, ESelectInfo::Type SelectInfo);

	void OnInventoryMouseClick(TSharedPtr<FInventoryEntry> InItem);
	void OnCashInventoryMouseClick(TSharedPtr<FInventoryEntry> InItem);

protected:

	/** action bindings array */
	TArray< TSharedPtr<FInventoryEntry> > InventoryList;
	TArray< TSharedPtr<FInventoryEntry> > CashInventoryList;

	/** action bindings list slate widget */
	TSharedPtr < STileView< TSharedPtr<FInventoryEntry> > > InventoryListWidget;
	TSharedPtr < STileView< TSharedPtr<FInventoryEntry> > > CashInventoryListWidget;

	/** currently selected list item */
	TSharedPtr<FInventoryEntry> SelectedItem;
	TSharedPtr<FInventoryEntry> CashSelectedItem;

	/** pointer to our owner PC */
	TWeakObjectPtr<class ULocalPlayer> PlayerOwner;

	/** pointer to our parent widget */
	TSharedPtr<class SWidget> OwnerWidget;

	TWeakPtr<const class SShooterCoinsWidget> CoinsWidget;

	FSlateColorBrush ConfirmationBackgroundBrush;

	TSharedPtr<SWidget> DialogWidget;

	TSharedPtr<SWidget> LoadingDialogWidget;
	TSharedPtr<STextBlock> LoadingDialogText;

	TSharedPtr<SWidget> MessageDialogWidget;

	bool bRequestInventoryList = false;
	bool bRequestCashInventoryList = false;

	FSimpleDelegate OnBuyItemFinished;

	void GetUserEntitlements();

	void ShowBuyConfirmationDialog(TSharedPtr<FInventoryEntry> InItem);
	void CloseConfirmationDialog();

	FReply OnBuyConfirm();
	FReply OnBuyCancel();

	void OnGetItemsByCriteria(const struct FAccelByteModelsItemPagingSlicedResult& Result);
	void OnGetCashItemsByCriteria(const struct FAccelByteModelsItemPagingSlicedResult& Result);
	void OnGetItemsByCriteriaError(int32 Code, const FString& Message);
	void OnGetCashItemsByCriteriaError(int32 Code, const FString& Message);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	void ShowLoadingDialog();
	void CloseLoadingDialog();

	void ShowMessageDialog(FString Message);
	void CloseMessageDialog();

	void OnBackFromPaymentBrowser(FString PaymentUrl);

	void OnFocusLost(const FFocusEvent& InFocusEvent);
	FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent);

	TSharedRef< FInventoryEntry > CreateInventoryItem(const struct FAccelByteModelsItemInfo& ItemInfo);

	FOptionalSize GetTileViewWidth(const TArray<TSharedPtr<FInventoryEntry>>&) const;
	FOptionalSize GetTileViewHeight() const;

	float GetItemWidth() const;
	float GetItemHeight() const;

	int32 TileWidth;
	int32 TileHeight;
	const int32 TileColumn;
	const int32 TileRow;

	// padding for both sides
	const float HorizontalPaddingRatio;
	const float VerticalPaddingRatio;
	const int32 MarginTop;

	TSharedPtr<SScrollBar> CoinsScrollBar;
	TSharedPtr<SScrollBar> ItemsScrollBar;

private:
	TSharedPtr<FTcpListener> PaymentListener;
};
