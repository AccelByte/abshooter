
#include "ShooterGame.h"
#include "SShooterInventory.h"
#include "ShooterStyle.h"
#include "ShooterUIHelpers.h"
#include "SShooterInventoryItem.h"
#include "ShooterGameViewportClient.h"
#include "ShooterGameInstance.h"
#include "SShooterConfirmationDialog.h"

SShooterInventory::SShooterInventory()
	: ConfirmationBackgroundBrush(FLinearColor(0, 0, 0, 0.8f))
{
}

void SShooterInventory::Construct(const FArguments& InArgs)
{
	PlayerOwner = InArgs._PlayerOwner;
	OwnerWidget = InArgs._OwnerWidget;
	const int32 TileWidth = 288;
	const int32 TileHeight = 200;
	const int32 TileColumn = 2;
	const int32 TileRow = 2;

	ChildSlot
	.VAlign(VAlign_Top)
	.HAlign(HAlign_Right)
	[
		SNew(SBox)
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		.Padding(0)
		.WidthOverride(TileWidth * TileColumn)
		.HeightOverride(TileHeight * TileRow + 4 )
		[
			SAssignNew(InventoryListWidget, STileView< TSharedPtr<FInventoryEntry> >)
			.ItemWidth(TileWidth)
			.ItemHeight(TileHeight)
			.ListItemsSource(&InventoryList)
			.ScrollbarVisibility(EVisibility::Collapsed)
			.OnSelectionChanged(this, &SShooterInventory::EntrySelectionChanged)
			.OnGenerateTile(this, &SShooterInventory::OnGenerateWidgetForTileView)
			.OnMouseButtonClick(this, &SShooterInventory::OnInventoryMouseClick)
			.SelectionMode(ESelectionMode::Single)
		]
	];
	BuildInventoryItem();
}

void SShooterInventory::BuildInventoryItem()
{
	InventoryList.Empty();

	//Dummy data
	InventoryList.Add(MakeShareable(new FInventoryEntry{ "WPUNTORCH", "Slate/Images/SubmachineGun.png", 2000, false, true, EItemType::WEAPON }));
	InventoryList.Add(MakeShareable(new FInventoryEntry{ "Bullet 20mm", "Slate/Images/Bullet.png", 100, true, true, EItemType::AMMO, 100 }));
	InventoryList.Add(MakeShareable(new FInventoryEntry{ "TRONIX-3900", "Slate/Images/Phaser.png", 1500, false, false, EItemType::WEAPON }));
	InventoryList.Add(MakeShareable(new FInventoryEntry{ "Beam 11XZ", "Slate/Images/LaserBeam.png", 200, true, true, EItemType::AMMO, 5 }));

	InventoryListWidget->RequestListRefresh();																																																																						   
}

TSharedRef<ITableRow> SShooterInventory::OnGenerateWidgetForTileView(TSharedPtr<FInventoryEntry> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(SShooterInventoryItem, OwnerTable, PlayerOwner, Item);
}

void SShooterInventory::EntrySelectionChanged(TSharedPtr<FInventoryEntry> InItem, ESelectInfo::Type SelectInfo)
{
	SelectedItem = InItem;
}

void SShooterInventory::OnInventoryMouseClick(TSharedPtr<FInventoryEntry> InItem)
{
	// Only able to buy when item already selected
	if (SelectedItem == InItem && InItem->Consumable)
	{
		ShowBuyConfirmationDialog(InItem);
	}
}

void SShooterInventory::ShowBuyConfirmationDialog(TSharedPtr<FInventoryEntry> InItem)
{
	SAssignNew(DialogWidget, SOverlay)
	+ SOverlay::Slot()
	[
		SNew(SImage)
		.Image(&ConfirmationBackgroundBrush)
	]
	+ SOverlay::Slot()
	[
		SNew(SShooterConfirmationDialog).PlayerOwner(PlayerOwner)
		.MessageText(FText::FromString(FString::Printf(TEXT("Buy %s \nusing %d Coins ?"), *InItem->Name, InItem->Price)))
		.ConfirmText(FText::FromString("Yes"))
		.CancelText(FText::FromString("No"))
		.OnConfirmClicked(FOnClicked::CreateRaw(this, &SShooterInventory::OnBuyConfirm))
		.OnCancelClicked(FOnClicked::CreateRaw(this, &SShooterInventory::OnBuyCancel))
	];

	GEngine->GameViewport->AddViewportWidgetContent(DialogWidget.ToSharedRef());
	FSlateApplication::Get().SetKeyboardFocus(DialogWidget);
}

void SShooterInventory::CloseConfirmationDialog()
{
	if (DialogWidget.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(DialogWidget.ToSharedRef());
		DialogWidget.Reset();
	}
}

FReply SShooterInventory::OnBuyConfirm()
{
	CloseConfirmationDialog();
	return FReply::Handled();
}

FReply SShooterInventory::OnBuyCancel()
{
	CloseConfirmationDialog();
	return FReply::Handled();
}