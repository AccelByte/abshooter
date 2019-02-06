
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
#include "AccelByteEntitlementApi.h"
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
	OnBuyItemFinished = InArgs._OnBuyItemFinished;
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

	Item::GetItemsByCriteria(GI->UserProfileInfo.Language, Locale, 
		"/item", EAccelByteItemType::INGAMEITEM, EAccelByteItemStatus::ACTIVE, 0, 20, 
		Item::FGetItemsByCriteriaSuccess::CreateSP(this, &SShooterInventory::OnGetItemsByCriteria), 
		AccelByte::FErrorHandler::CreateSP(this, &SShooterInventory::OnGetItemsByCriteriaError));
	Item::GetItemsByCriteria(GI->UserProfileInfo.Language, Locale, 
		"/coin", EAccelByteItemType::COINS, EAccelByteItemStatus::ACTIVE, 0, 20, 
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
	if (SelectedItem == InItem && InItem->Purchasable)
	{
		ShowBuyConfirmationDialog(InItem);
	}
}

void SShooterInventory::ShowBuyConfirmationDialog(TSharedPtr<FInventoryEntry> InItem)
{
	float Price = (InItem->CurrencyType == TEXT("REAL") ? InItem->Price/100.00f : InItem->Price/1.f);
	FString PriceString = FString::SanitizeFloat(Price, InItem->CurrencyType == TEXT("REAL")? 2 : 0);

	SAssignNew(DialogWidget, SOverlay)
	+ SOverlay::Slot()
	[
		SNew(SImage)
		.Image(&ConfirmationBackgroundBrush)
	]
	+ SOverlay::Slot()
	[
		SNew(SShooterConfirmationDialog).PlayerOwner(PlayerOwner)
		.MessageText(FText::FromString(FString::Printf(TEXT("Buy %s \nusing %s %s?"), *InItem->Name, *PriceString, *InItem->CurrencyCode)))
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

	AccelByte::Api::Order::CreateNewOrder(OrderCreate, Order::FCreateNewOrderSuccess::CreateLambda([&](const FAccelByteModelsOrderInfo& OrderInfo) {
		CloseLoadingDialog(); 
		if (!OrderInfo.PaymentStationUrl.IsEmpty())
		{
			FPlatformProcess::LaunchURL(*OrderInfo.PaymentStationUrl, nullptr, nullptr);
			OnBackFromPaymentBrowser(OrderInfo.PaymentStationUrl);
		}
		else 
		{
			ShowMessageDialog(TEXT("Order Success"));
			BuildInventoryItem();
			OnBuyItemFinished.ExecuteIfBound();
		}
	}), AccelByte::FErrorHandler::CreateLambda([&](int ErrorCode, FString Message) {
		CloseLoadingDialog();

		OnBuyItemFinished.ExecuteIfBound();
		ShowMessageDialog(FString::Printf(TEXT("Purchase failed %s"), *Message));
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
		Inventory->Quantity = 0;
		Inventory->ImageURL = ItemInfo.ThumbnailImage.ImageUrl;

		for (int j = 0; j < ItemInfo.RegionData.Num(); j++)
		{
			if (ItemInfo.RegionData[j].CurrencyType == "VIRTUAL" || ItemInfo.RegionData[j].CurrencyType == "REAL")
			{
				Inventory->CurrencyCode = ItemInfo.RegionData[j].CurrencyCode;
				Inventory->Price = ItemInfo.RegionData[j].Price;
				Inventory->DiscountedPrice = ItemInfo.RegionData[j].DiscountedPrice;
				Inventory->CurrencyType = ItemInfo.RegionData[j].CurrencyType;
				break;
			}
		}

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
			else if (ItemInfo.Tags[j] == "coin")
			{
				Inventory->Type = EInventoryItemType::COIN;
				break;
			}
		}

		Inventory->Purchasable = Inventory->Type != EInventoryItemType::WEAPON;

		InventoryList.Add(Inventory);
	}
	GetItemRequestCount.Decrement();

	if (GetItemRequestCount.GetValue() == 0)
	{
		GetUserEntitlements();
	}
}

void SShooterInventory::OnGetItemsByCriteriaError(int32 Code, const FString& Message)
{
	GetItemRequestCount.Decrement();
	UE_LOG(LogTemp, Display, TEXT("GetItem Error: code: %d, message: %s"), Code, *Message)
}

void SShooterInventory::GetUserEntitlements() 
{
	Entitlement::QueryUserEntitlement("", "", 0, 100, Entitlement::FQueryUserEntitlementSuccess::CreateLambda([&](FAccelByteModelsEntitlementPagingSlicedResult Result)
	{
		TMap<FString, int> Quantities;
		for (int i = 0; i < Result.Data.Num(); i++)
		{
            if (Result.Data[i].Type == EAccelByteEntitlementType::DURABLE)
            {
                Quantities[Result.Data[i].ItemId] = Quantities.FindOrAdd(Result.Data[i].ItemId) + 1;
            }
            else
            {
                Quantities[Result.Data[i].ItemId] = Quantities.FindOrAdd(Result.Data[i].ItemId) + Result.Data[i].UseCount;
            }			
		}

		for (TSharedPtr<FInventoryEntry> entry : InventoryList)
		{
            int* Quantity = Quantities.Find(entry->ItemId);
            if (Quantity != nullptr)
            {                
                entry->Quantity = (*Quantity > 0) ? *Quantity : 1;
                entry->Owned = true;
            }
            else
            {
                entry->Quantity = 0;
                entry->Owned = false;
            }
		}
		InventoryListWidget->RequestListRefresh();
	}), AccelByte::FErrorHandler::CreateLambda([&](int32 Code, FString Message)
	{
		UE_LOG(LogTemp, Display, TEXT("Query entitlement failed: code: %d, message: %s"), Code, *Message)
	}), EAccelByteEntitlementClass::ENTITLEMENT, EAccelByteAppType::NONE);
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

void SShooterInventory::OnBackFromPaymentBrowser(FString PaymentUrl)
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
		.MessageText(FText::FromString("Are your payment is completed already?"))
		.ConfirmText(FText::FromString("Yes!"))
		.OnConfirmClicked(FOnClicked::CreateLambda([&]() -> FReply {
			CloseMessageDialog();
			BuildInventoryItem();
			OnBuyItemFinished.ExecuteIfBound();
			return FReply::Handled();
		}))
	];

	GEngine->GameViewport->AddViewportWidgetContent(MessageDialogWidget.ToSharedRef());
	FSlateApplication::Get().SetKeyboardFocus(MessageDialogWidget);
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