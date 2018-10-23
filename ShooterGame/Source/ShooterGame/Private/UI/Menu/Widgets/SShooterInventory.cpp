
#include "ShooterGame.h"
#include "SShooterInventory.h"
#include "ShooterStyle.h"
#include "ShooterUIHelpers.h"
#include "SShooterInventoryItem.h"
#include "UserWidget.h"

void SShooterInventory::Construct(const FArguments& InArgs)
{
    PlayerOwner = InArgs._PlayerOwner;
    OwnerWidget = InArgs._OwnerWidget;
    const int32 TileSize = 240;
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
        .WidthOverride(TileSize * TileColumn + 16)
        .HeightOverride(TileSize * TileRow + 4 )
        [
            SAssignNew(InventoryListWidget, STileView< TSharedPtr<FInventoryEntry> >)
            .ItemWidth(TileSize)
            .ItemHeight(TileSize)
            .ListItemsSource(&InventoryList)
            .OnSelectionChanged(this, &SShooterInventory::EntrySelectionChanged)
            .OnGenerateTile(this, &SShooterInventory::OnGenerateWidgetForTileView)
            .SelectionMode(ESelectionMode::Single)
        ]
    ];
    BuildInventoryItem();
}

void SShooterInventory::BuildInventoryItem()
{
    InventoryList.Empty();

    FString imageURL = "https://s3-us-west-2.amazonaws.com/justice-platform-service/integration/avatar/442dd73025c74282b14fe8ed3aa5fb7a.jpg";

    //Dummy data
    InventoryList.Add(MakeShareable(new FInventoryEntry{ "Riffle", imageURL, 2000, false, true, EItemType::WEAPON }));
    InventoryList.Add(MakeShareable(new FInventoryEntry{ "Bullet 20mm", imageURL, 100, true, true, EItemType::AMMO, 100 }));
    InventoryList.Add(MakeShareable(new FInventoryEntry{ "Granate Thrower", imageURL, 1500, false, true, EItemType::WEAPON }));
    InventoryList.Add(MakeShareable(new FInventoryEntry{ "Granate", "Slate/Images/SoundCue_SpeakerIcon.png", 200, true, true, EItemType::AMMO, 5 }));

    InventoryListWidget->RequestListRefresh();
}

TSharedRef<ITableRow> SShooterInventory::OnGenerateWidgetForTileView(TSharedPtr<FInventoryEntry> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
    return SNew(SShooterInventoryItem, OwnerTable, PlayerOwner, Item);
}

void SShooterInventory::EntrySelectionChanged(TSharedPtr<FInventoryEntry> InItem, ESelectInfo::Type SelectInfo)
{
}