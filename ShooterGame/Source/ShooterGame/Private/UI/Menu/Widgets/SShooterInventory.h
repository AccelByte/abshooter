// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "ShooterGame.h"
#include "Models/ShooterInventory.h"
#include "Models/AccelByteEcommerceModels.h"
#include "UI/Menu/UMG/MainMenu/MainMenuUI.h"

//class declare
class SShooterInventory : public SCompoundWidget
{
public:
	SShooterInventory();

	SLATE_BEGIN_ARGS(SShooterInventory)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<ULocalPlayer >, PlayerOwner)
	SLATE_ARGUMENT(TSharedPtr<SWidget>, OwnerWidget)
	SLATE_ARGUMENT(UMainMenuUI*, UOwnerWidget) //TODO remove this argument after Inventory migrated to UMG completely
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
	UMainMenuUI* UOwnerWidget; //TODO remove this member after Inventory migrated to UMG completely

	FSlateColorBrush ConfirmationBackgroundBrush;

	TSharedPtr<SWidget> DialogWidget;

	TSharedPtr<SWidget> LoadingDialogWidget;
	TSharedPtr<STextBlock> LoadingDialogText;

	TSharedPtr<SWidget> MessageDialogWidget;
	
	/** This is use to reference "Empty" label text */
	TSharedPtr<STextBlock> EmptyText;
	void SetLabelEmpty();

	bool bRequestInventoryList = false;
	

	FSimpleDelegate OnBuyItemFinished;

	void GetUserEntitlements();

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

	TSharedRef< FInventoryEntry > CreateInventoryItem(const struct FAccelByteModelsItemInfo& ItemInfo);

	float GetScreenWidth() const;
	float GetScreenHeight() const;

	FOptionalSize GetTileViewWidth(const TArray<TSharedPtr<FInventoryEntry>>&) const;
	FOptionalSize GetTileViewHeight() const;

	float GetItemWidth() const;
	float GetItemHeight() const;

	int32 TileWidth;
	int32 TileHeight;
	const int32 TileColumn;
	const int32 TileRow;

	TArray<FAccelByteModelsItemInfo> ItemModelList;

	// padding for both sides
	const float TileItemWidthRatio;
	const float TileItemHeightRatio;
	
	const float PaddingTopRatio;

	TSharedPtr<SScrollBar> ItemsScrollBar;
};


