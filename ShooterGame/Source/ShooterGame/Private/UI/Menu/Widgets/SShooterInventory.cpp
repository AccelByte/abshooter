
#include "ShooterGame.h"
#include "SShooterInventory.h"
#include "ShooterStyle.h"
#include "ShooterUIHelpers.h"
#include "SShooterInventoryItem.h"
#include "ShooterGameViewportClient.h"
#include "ShooterGameInstance.h"
#include "SShooterConfirmationDialog.h"
#include "AccelByteOrderApi.h"
#include "AccelByteItemApi.h"
#include "AccelByteError.h"

using namespace AccelByte::Api;

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
}

void SShooterInventory::BuildInventoryItem()
{
	if (GetItemRequestCount.GetValue() > 0)
	{
		return;
	}

	InventoryList.Empty();

	UShooterGameInstance* const GI = Cast<UShooterGameInstance>(PlayerOwner->GetGameInstance());
	
#if PLATFORM_WINDOWS
	FString Locale = FWindowsPlatformMisc::GetDefaultLocale();
#elif PLATFORM_MAC
	FString Locale = FMacPlatformMisc::GetDefaultLocale();
#elif PLATFORM_LINUX
	FString Locale = FLinuxPlatformMisc::GetDefaultLocale();
#endif

	GetItemRequestCount.Set(2);

	Item::GetItemsByCriteriaEasy(GI->UserProfileInfo.Language, Locale, 
		"/all/ammo", EItemType::INGAMEITEM, EItemStatus::ACTIVE, 0, 100, 
		Item::FGetItemsByCriteriaSuccess::CreateSP(this, &SShooterInventory::OnGetItemsByCriteria), 
		AccelByte::FErrorHandler::CreateSP(this, &SShooterInventory::OnGetItemsByCriteriaError));

	Item::GetItemsByCriteriaEasy(GI->UserProfileInfo.Language, Locale,
		"/all/weapon", EItemType::INGAMEITEM, EItemStatus::ACTIVE, 0, 100,
		Item::FGetItemsByCriteriaSuccess::CreateSP(this, &SShooterInventory::OnGetItemsByCriteria),
		AccelByte::FErrorHandler::CreateSP(this, &SShooterInventory::OnGetItemsByCriteriaError));
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
		.OnConfirmClicked(FOnClicked::CreateSP(this, &SShooterInventory::OnBuyConfirm))
		.OnCancelClicked(FOnClicked::CreateSP(this, &SShooterInventory::OnBuyCancel))
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
	FAccelByteModelsOrderCreate OrderCreate;
	OrderCreate.ItemId = SelectedItem->ItemId;
	OrderCreate.CurrencyCode = SelectedItem->CurrencyCode;
	OrderCreate.Price = SelectedItem->Price;
	OrderCreate.DiscountedPrice = SelectedItem->DiscountedPrice;
	OrderCreate.Quantity = 1;
	OrderCreate.ReturnUrl = TEXT("https://sdk.example.com");

	CloseConfirmationDialog();
	ShowLoadingDialog();

	AccelByte::Api::Order::CreateNewOrderEasy(OrderCreate, Order::FCreateNewOrderSuccess::CreateLambda([&](const FAccelByteModelsOrderInfo& OrderInfo) {
		CloseLoadingDialog();
		ShowMessageDialog(TEXT("Order Success"));
	}), AccelByte::FErrorHandler::CreateLambda([&](int ErrorCode, FString Message) {
		CloseLoadingDialog();

		ShowMessageDialog(TEXT("Purchase failed %s"));
		UE_LOG(LogTemp, Display, TEXT("Purchase failed: code: %d, message: %s"), ErrorCode, *Message)
	}));
	return FReply::Handled();
}

FReply SShooterInventory::OnBuyCancel()
{
	CloseConfirmationDialog();
	return FReply::Handled();
}

void SShooterInventory::OnGetItemsByCriteria(const FAccelByteModelsItemPagingSlicedResult& Result)
{
	for (int i = 0; i < Result.Data.Num(); i++)
	{
		const FAccelByteModelsItemInfo& ItemInfo = Result.Data[i];
		TSharedRef< FInventoryEntry > Inventory = MakeShareable(new FInventoryEntry());
		Inventory->ItemId = ItemInfo.ItemId;
		Inventory->Name = ItemInfo.Title;
		Inventory->Quantity = ItemInfo.UseCount;
		Inventory->ImageURL = ItemInfo.ThumbnailImage.ImageUrl;

		for (int j = 0; j < ItemInfo.RegionData.Num(); j++)
		{
			if (ItemInfo.RegionData[j].CurrencyType == "VIRTUAL")
			{
				Inventory->CurrencyCode = ItemInfo.RegionData[j].CurrencyCode;
				Inventory->Price = ItemInfo.RegionData[j].Price;
				Inventory->DiscountedPrice = ItemInfo.RegionData[j].DiscountedPrice;
				break;
			}
		}

		Inventory->Consumable = ItemInfo.EntitlementType == "CONSUMABLE";
		for (int j = 0; j < ItemInfo.Tags.Num(); j++)
		{
			if (ItemInfo.Tags[j] == "ammo")
			{
				Inventory->Type = EInventoryItemType::AMMO;
				break;
			}
			else if (ItemInfo.Tags[j] == "weapon")
			{
				Inventory->Type = EInventoryItemType::WEAPON;
				break;
			}
		}

		InventoryList.Add(Inventory);
	}
	InventoryListWidget->RequestListRefresh();
	GetItemRequestCount.Decrement();
}

void SShooterInventory::OnGetItemsByCriteriaError(int32 Code, FString Message)
{
	UE_LOG(LogTemp, Display, TEXT("GetItem Error: code: %d, message: %s"), Code, *Message)
}


void SShooterInventory::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	if (LoadingDialogWidget.IsValid())
	{
		

		int DotCount = fmod(InCurrentTime, 5) * 2;
		FString Text = "..";
		for (int i = 0; i < DotCount; i++)
		{
			Text += ".";
		}
		LoadingDialogText->SetText(Text);
	}
}

void SShooterInventory::ShowLoadingDialog()
{
	SAssignNew(LoadingDialogWidget, SOverlay)
	+ SOverlay::Slot()
	[
		SNew(SImage)
		.Image(&ConfirmationBackgroundBrush)
	]
	+ SOverlay::Slot()
	.HAlign(HAlign_Center)
	.VAlign(VAlign_Center)
	[
		SAssignNew(LoadingDialogText, STextBlock)
		.TextStyle(FShooterStyle::Get(), "ShooterGame.MenuHeaderTextStyle")
		.Text(FText::FromString("..."))
	];

	GEngine->GameViewport->AddViewportWidgetContent(LoadingDialogWidget.ToSharedRef());
	FSlateApplication::Get().SetKeyboardFocus(LoadingDialogWidget);
}

void SShooterInventory::CloseLoadingDialog()
{
	if (LoadingDialogWidget.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(LoadingDialogWidget.ToSharedRef());
		LoadingDialogWidget.Reset();
	}
}

void SShooterInventory::ShowMessageDialog(FString Message)
{
	SAssignNew(MessageDialogWidget, SOverlay)
	+ SOverlay::Slot()
	[
		SNew(SImage)
		.Image(&ConfirmationBackgroundBrush)
	]
	+ SOverlay::Slot()
	[
		SNew(SShooterConfirmationDialog).PlayerOwner(PlayerOwner)
		.MessageText(FText::FromString(Message))
		.ConfirmText(FText::FromString("OK"))
		.OnConfirmClicked(FOnClicked::CreateLambda([&]() -> FReply {
			CloseMessageDialog();
			return FReply::Handled();
		}))
	];

	GEngine->GameViewport->AddViewportWidgetContent(MessageDialogWidget.ToSharedRef());
	FSlateApplication::Get().SetKeyboardFocus(MessageDialogWidget);
}

void SShooterInventory::CloseMessageDialog()
{
	if (MessageDialogWidget.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(MessageDialogWidget.ToSharedRef());
		MessageDialogWidget.Reset();
	}
}

void SShooterInventory::OnFocusLost(const FFocusEvent& InFocusEvent)
{
	if (InFocusEvent.GetCause() != EFocusCause::SetDirectly)
	{
		FSlateApplication::Get().SetKeyboardFocus(SharedThis(this));
	}
}

FReply SShooterInventory::OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent)
{
	return FReply::Handled().SetUserFocus(InventoryListWidget.ToSharedRef(), EFocusCause::SetDirectly);
}