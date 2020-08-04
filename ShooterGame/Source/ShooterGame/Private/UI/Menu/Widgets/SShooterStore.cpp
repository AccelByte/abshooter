
#include "ShooterGame.h"
#include "SShooterStore.h"
#include "ShooterStyle.h"
#include "ShooterMenuWidgetStyle.h"
#include "SShooterMenuWidget.h"
#include "ShooterUIHelpers.h"
#include "SShooterStoreItem.h"
#include "ShooterGameViewportClient.h"
#include "ShooterGameInstance.h"
#include "SShooterConfirmationDialog.h"
#include "AccelByteOrderApi.h"
#include "AccelByteItemApi.h"
#include "AccelByteEntitlementApi.h"
#include "AccelByteError.h"
#include "Core/AccelByteRegistry.h"
#include "ShooterStoreStyle.h"
#include "ShooterInventoryWidgetStyle.h"
#include "SShooterCoinsWidget.h"
#include "SShooterPaymentDialog.h"
#include "Runtime/Networking/Public/Common/TcpListener.h"
#include "Kismet/KismetInternationalizationLibrary.h"
#include "ShooterGameConfig.h"
#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/MinimalWindowsApi.h"
#endif
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "Sockets.h"

#define USING_EXTERNAL_BROWSER 0

using namespace AccelByte::Api;

SShooterStore::SShooterStore()
	: ConfirmationBackgroundBrush(FLinearColor(0, 0, 0, 0.8f))
	, TileWidth(388)
	, TileHeight(200)
	, TileColumn(1)
	, TileRow(4)
	, HorizontalPaddingRatio(0.21875f)
	, VerticalPaddingRatio(0)
	, MarginTop(175)
{
	FIPv4Endpoint EndPoint;
	FIPv4Endpoint::Parse(FString("127.0.0.1:7777"), EndPoint);
	
	PaymentListener = MakeShared<FTcpListener>(EndPoint);
	PaymentListener->Init();
	PaymentListener->OnConnectionAccepted().BindLambda([this](FSocket* Socket, const FIPv4Endpoint EndPoint) {
		FString ResponseBody = "Your payment has been completed. You can close this window and return back to the game.\r\n";
		FTCHARToUTF8 ResponseBodyUtf8(*ResponseBody);

		FString ResponseHeader = FString::Printf(
			TEXT(
				"HTTP/1.1 200 OK\r\n"
				"Connection: keep-alive\r\n"
				"Date: Tue, 12 Mar 2019 06:01:15 GMT\r\n"
				"Content-Type: text/html; charset=UTF-8\r\n"
				"Content-Length: %d\r\n"
				"\r\n"
			), 
			ResponseBodyUtf8.Length());

		FString Response = ResponseHeader.Append(ResponseBody);

		FTCHARToUTF8 ResponseUtf8(*Response);
		int32 SentBytes = 0;

		Socket->Send((const uint8_t*)ResponseUtf8.Get(), ResponseUtf8.Length(), SentBytes);
		Socket->Close();

#if PLATFORM_WINDOWS
		HWND WindowHandle = static_cast<HWND>(GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle());
		BringWindowToTop(WindowHandle);
		SetForegroundWindow(WindowHandle);
#endif
		return true;
	});	
}

void SShooterStore::Construct(const FArguments& InArgs)
{
	PlayerOwner = InArgs._PlayerOwner;
	OwnerWidget = InArgs._OwnerWidget;
	UOwnerWidget = InArgs._UOwnerWidget;//TODO remove this argument after Store migrated to UMG completely
	OnBuyItemFinished = InArgs._OnBuyItemFinished;
	CoinsWidget = InArgs._CoinsWidget;

	const FShooterStoreStyle* StoreStyle = &FShooterStyle::Get().GetWidgetStyle<FShooterStoreStyle>("DefaultShooterStoreStyle");
	const FShooterInventoryStyle* InventoryStyle = &FShooterStyle::Get().GetWidgetStyle<FShooterInventoryStyle>("DefaultShooterInventoryStyle");
	const FShooterMenuStyle* MenuStyle = &FShooterStyle::Get().GetWidgetStyle<FShooterMenuStyle>("DefaultShooterMenuStyle");

	ChildSlot
	.VAlign(VAlign_Top)
	.HAlign(HAlign_Right)
	.Padding(0, MarginTop, 0, 0)
	[
		SNew(SBox)
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		.WidthOverride(TAttribute<FOptionalSize>::Create([&]() -> FOptionalSize {
			FVector2D Result = FVector2D(1, 1);
			GEngine->GameViewport->GetViewportSize(Result);
			return FOptionalSize(Result.X * (1.0f - HorizontalPaddingRatio) + 32);
		}))
		.HeightOverride(this, &SShooterStore::GetTileViewHeight)
		.Padding(0)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.Padding(FMargin(16.0f))
				.AutoHeight()
				[
					SNew(SImage)
					.Image(&StoreStyle->HeaderVirtualCoins)
				]
				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				[
					SAssignNew(CashInventoryListWidget, STileView< TSharedPtr<FInventoryEntry> >)
					.ItemWidth(this, &SShooterStore::GetItemWidth)
					.ItemHeight(this, &SShooterStore::GetItemHeight)
					.ListItemsSource(&CashInventoryList)
					/*.ScrollbarVisibility(TAttribute<EVisibility>::Create([&]() -> EVisibility {
						return CashInventoryList.Num() > TileColumn * TileRow ? EVisibility::Visible : EVisibility::Collapsed;
					}))*/
					.ScrollbarVisibility(EVisibility::Visible)
					.ExternalScrollbar(CoinsScrollBar)
					.OnSelectionChanged(this, &SShooterStore::CashEntrySelectionChanged)
					.OnGenerateTile(this, &SShooterStore::OnGenerateCashWidgetForTileView)
					.OnMouseButtonClick(this, &SShooterStore::OnCashInventoryMouseClick)
					.SelectionMode(ESelectionMode::Single)
				]
			]
			+ SHorizontalBox::Slot()	//Scroll bar
			.AutoWidth()
			[
				SNew(SBox)
				.HAlign(HAlign_Right)
				.Padding(FMargin(0, 45.0f, 0, 0))
				[
					SAssignNew(CoinsScrollBar, SScrollBar)
					.IsEnabled(true)
					.Thickness(FVector2D(2.0f, 2.0f))
					.Orientation(EOrientation::Orient_Vertical)
					.Visibility(EVisibility::Visible)
					.Style(&InventoryStyle->ScrollBarStyle)
				]
			]
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.Padding(FMargin(16.0f))
				.AutoHeight()
				[
					SNew(SImage)
					.Image(&StoreStyle->HeaderItems)
				]
				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				[
					SAssignNew(InventoryListWidget, STileView< TSharedPtr<FInventoryEntry> >)
					.ItemWidth(this, &SShooterStore::GetItemWidth)
					.ItemHeight(this, &SShooterStore::GetItemHeight)
					.ListItemsSource(&InventoryList)
					/*.ScrollbarVisibility(TAttribute<EVisibility>::Create([&]() -> EVisibility {
						return InventoryList.Num() > TileColumn * TileRow ? EVisibility::Visible : EVisibility::Collapsed;
					}))*/
					.ScrollbarVisibility(EVisibility::Visible)
					.ExternalScrollbar(ItemsScrollBar)
					.OnSelectionChanged(this, &SShooterStore::EntrySelectionChanged)
					.OnGenerateTile(this, &SShooterStore::OnGenerateWidgetForTileView)
					.OnMouseButtonClick(this, &SShooterStore::OnInventoryMouseClick)
					.SelectionMode(ESelectionMode::Single)
				]
			]
			+ SHorizontalBox::Slot()	//Scroll bar
			.AutoWidth()
			[
				SNew(SBox)
				.HAlign(HAlign_Right)
				.Padding(FMargin(0, 45.0f, 0, 0))
				[
					SAssignNew(ItemsScrollBar, SScrollBar)
					.IsEnabled(true)
					.Thickness(FVector2D(2.0f, 2.0f))
					.Orientation(EOrientation::Orient_Vertical)
					.Visibility(EVisibility::Visible)
					.Style(&InventoryStyle->ScrollBarStyle)
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Right)
			.Padding(FMargin(0, 0, 0, 20))
			[
				SNew(SBox)
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Right)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SButton)
						.ButtonStyle(&MenuStyle->EscapeButton)
						.VAlign(VAlign_Bottom)
						.OnClicked(FOnClicked::CreateLambda([&]()
						{
							if (OwnerWidget.IsValid())
							{
								static_cast<SShooterMenuWidget*>(OwnerWidget.Get())->MenuGoBack();
							}
							else if (UOwnerWidget != nullptr) //TODO remove this implementation to open main menu
							{
								static_cast<UMainMenuUI*>(UOwnerWidget)->OpenMainMenu();
							}
							return FReply::Handled();
						}))
					]
					+ SHorizontalBox::Slot()
					.Padding(10, 0, 0, 0)
					.AutoWidth()
					[
						SNew(SImage)
						.Image(&MenuStyle->EscapeMainMenuInfo)
					]
				]
			]
		]
	];
	BuildInventoryItem();
}

FOptionalSize SShooterStore::GetTileViewWidth(const TArray<TSharedPtr<FInventoryEntry>>& List) const
{
	FVector2D Result = FVector2D(1, 1);
	GEngine->GameViewport->GetViewportSize(Result);
	return FOptionalSize(Result.X * (1.0f - HorizontalPaddingRatio) + (List.Num() > TileColumn * TileRow ? 16 : 0));
}

FOptionalSize SShooterStore::GetTileViewHeight() const
{
	FVector2D Result = FVector2D(1, 1);
	GEngine->GameViewport->GetViewportSize(Result);
	return FOptionalSize(Result.Y * (1.0f - VerticalPaddingRatio) - MarginTop);
}

float SShooterStore::GetItemWidth() const
{
	FVector2D Result = FVector2D(1, 1);
	GEngine->GameViewport->GetViewportSize(Result);
	return ((Result.X * (1.0f - HorizontalPaddingRatio))) / (TileColumn * 2);
}

float SShooterStore::GetItemHeight() const
{
	return 180;
}

void SShooterStore::BuildInventoryItem()
{
	UShooterGameInstance* const GI = Cast<UShooterGameInstance>(PlayerOwner->GetGameInstance());
	
#if PLATFORM_WINDOWS
	FString Locale = FWindowsPlatformMisc::GetDefaultLocale();
#elif PLATFORM_MAC
	FString Locale = FMacPlatformMisc::GetDefaultLocale();
#elif PLATFORM_LINUX
	FString Locale = FLinuxPlatformMisc::GetDefaultLocale();
#endif

	if (!bRequestInventoryList)
	{
		bRequestInventoryList = true;
		InventoryList.Empty();
		FAccelByteModelsItemCriteria Criteria;
		Criteria.ItemType = EAccelByteItemType::INGAMEITEM;
		Criteria.Region = Locale;
		Criteria.Language = GI->UserProfileInfo.Language;
		Criteria.CategoryPath = "/item";
		FRegistry::Item.GetItemsByCriteria(Criteria, 0, 20,
			AccelByte::THandler<FAccelByteModelsItemPagingSlicedResult>::CreateSP(this, &SShooterStore::OnGetItemsByCriteria),
			AccelByte::FErrorHandler::CreateSP(this, &SShooterStore::OnGetItemsByCriteriaError));
	}
	if (!bRequestCashInventoryList)
	{
		bRequestCashInventoryList = true;
		CashInventoryList.Empty();
		FAccelByteModelsItemCriteria Criteria;
		Criteria.ItemType = EAccelByteItemType::COINS;
		Criteria.Region = Locale;
		Criteria.Language = GI->UserProfileInfo.Language;
		Criteria.CategoryPath = "/coin";
		FRegistry::Item.GetItemsByCriteria(Criteria, 0, 20,
			AccelByte::THandler<FAccelByteModelsItemPagingSlicedResult>::CreateSP(this, &SShooterStore::OnGetCashItemsByCriteria),
			AccelByte::FErrorHandler::CreateSP(this, &SShooterStore::OnGetItemsByCriteriaError));
	}
}

TSharedRef<ITableRow> SShooterStore::OnGenerateWidgetForTileView(TSharedPtr<FInventoryEntry> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(SShooterStoreItem, OwnerTable, PlayerOwner, Item)
		.OnBuyItem(FOnBuyItem::CreateSP(this, &SShooterStore::ShowBuyConfirmationDialog));
}

TSharedRef<ITableRow> SShooterStore::OnGenerateCashWidgetForTileView(TSharedPtr<FInventoryEntry> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(SShooterStoreItem, OwnerTable, PlayerOwner, Item)
		.OnBuyItem(FOnBuyItem::CreateSP(this, &SShooterStore::ShowBuyConfirmationDialog));
}

void SShooterStore::EntrySelectionChanged(TSharedPtr<FInventoryEntry> InItem, ESelectInfo::Type SelectInfo)
{
	SelectedItem = InItem;
}

void SShooterStore::CashEntrySelectionChanged(TSharedPtr<FInventoryEntry> InItem, ESelectInfo::Type SelectInfo)
{
	CashSelectedItem = InItem;
}

void SShooterStore::OnInventoryMouseClick(TSharedPtr<FInventoryEntry> InItem)
{
	// Only able to buy when item already selected
	//if (SelectedItem == InItem && InItem->Purchasable)
	//{
	//	ShowBuyConfirmationDialog(InItem);
	//}
}

void SShooterStore::OnCashInventoryMouseClick(TSharedPtr<FInventoryEntry> InItem)
{
	// Only able to buy when item already selected
	//if (CashSelectedItem == InItem && InItem->Purchasable)
	//{
	//	ShowBuyConfirmationDialog(InItem);
	//}
}

void SShooterStore::ShowBuyConfirmationDialog(TSharedPtr<FInventoryEntry> InItem)
{
	SelectedItem = InItem;
	float FinalPrice = InItem->DiscountedPrice != 0 ? InItem->DiscountedPrice : InItem->Price * (1.f - InItem->DiscountPercentage);
	if (InItem->CurrencyType != EAccelByteItemCurrencyType::REAL && CoinsWidget.Pin()->Balance < FinalPrice)
	{
		TSharedPtr<SShooterConfirmationDialog> Dialog;
		SAssignNew(DialogWidget, SOverlay)
		+ SOverlay::Slot()
		[
			SNew(SImage)
			.Image(&ConfirmationBackgroundBrush)
		]
		+ SOverlay::Slot()
		[
			SAssignNew(Dialog, SShooterConfirmationDialog).PlayerOwner(PlayerOwner)
			.MessageText(FText::FromString(FString::Printf(TEXT("Insufficient coins!"))))
			.ConfirmText(FText::FromString("OK"))
			.OnConfirmClicked(FOnClicked::CreateSP(this, &SShooterStore::OnBuyCancel))
		];

		GEngine->GameViewport->AddViewportWidgetContent(DialogWidget.ToSharedRef());
		FSlateApplication::Get().SetKeyboardFocus(Dialog);
		return;
	}

	float Price = (InItem->CurrencyType == EAccelByteItemCurrencyType::REAL ? FinalPrice /100.00f : FinalPrice /1.f);
	FString PriceString = FString::SanitizeFloat(Price, InItem->CurrencyType == EAccelByteItemCurrencyType::REAL ? 2 : 0);

	TSharedPtr<SShooterConfirmationDialog> Dialog;

	SAssignNew(DialogWidget, SOverlay)
	+ SOverlay::Slot()
	[
		SNew(SImage)
		.Image(&ConfirmationBackgroundBrush)
	]
	+ SOverlay::Slot()
	[
		SAssignNew(Dialog, SShooterConfirmationDialog).PlayerOwner(PlayerOwner)
		.MessageText(FText::FromString(FString::Printf(TEXT("Buy %s \nusing %s %s?"), *InItem->Name, *PriceString, *InItem->CurrencyCode)))
		.ConfirmText(FText::FromString("Yes"))
		.CancelText(FText::FromString("No"))
		.OnConfirmClicked(FOnClicked::CreateSP(this, &SShooterStore::OnBuyConfirm))
		.OnCancelClicked(FOnClicked::CreateSP(this, &SShooterStore::OnBuyCancel))
	];

	GEngine->GameViewport->AddViewportWidgetContent(DialogWidget.ToSharedRef());
	FSlateApplication::Get().SetKeyboardFocus(Dialog);
}

void SShooterStore::CloseConfirmationDialog()
{
	if (DialogWidget.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(DialogWidget.ToSharedRef());
		DialogWidget.Reset();
	}
	FSlateApplication::Get().SetKeyboardFocus(SharedThis(this));
}

FReply SShooterStore::OnBuyConfirm()
{

#if PLATFORM_WINDOWS
	FString Locale = FWindowsPlatformMisc::GetDefaultLocale();
#elif PLATFORM_MAC
	FString Locale = FMacPlatformMisc::GetDefaultLocale();
#elif PLATFORM_LINUX
	FString Locale = FLinuxPlatformMisc::GetDefaultLocale();
#endif

	FJsonSerializableArray Split;
	FString Region;
	Locale.ParseIntoArray(Split, TEXT("-"), true);
	if (Split.Num() > 1)
	{
		Region = Split[1];
	}
	else
	{
		Region = Locale;
	}
	const FString Language = UKismetInternationalizationLibrary::GetCurrentLanguage();

	
	FAccelByteModelsOrderCreate OrderCreate;
	OrderCreate.ItemId = SelectedItem->ItemId;
	OrderCreate.CurrencyCode = SelectedItem->CurrencyCode;
	OrderCreate.Price = SelectedItem->Price;
	OrderCreate.DiscountedPrice = SelectedItem->DiscountedPrice;
	OrderCreate.Region = Region;
	OrderCreate.Language = Language;
	OrderCreate.Quantity = 1;
	OrderCreate.ReturnUrl = TEXT("http://127.0.0.1:7777/");

	CloseConfirmationDialog();
	ShowLoadingDialog();


	FRegistry::Order.CreateNewOrder(OrderCreate, AccelByte::THandler<FAccelByteModelsOrderInfo>::CreateLambda([&](const FAccelByteModelsOrderInfo& OrderInfo) {
		CloseLoadingDialog(); 
		if (!OrderInfo.PaymentStationUrl.IsEmpty())
		{
#if USING_EXTERNAL_BROWSER
			FPlatformProcess::LaunchURL(*OrderInfo.PaymentStationUrl, nullptr, nullptr);
			OnBackFromPaymentBrowser(OrderInfo.PaymentStationUrl);
#else // USING EMBEDDED BROWSER
			OnPaymentOrderCreated(OrderInfo.PaymentStationUrl);
#endif
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

void SShooterStore::OnPaymentOrderCreated(FString Url)
{
	TSharedPtr<SShooterPaymentDialog> Dialog;

	SAssignNew(MessageDialogWidget, SOverlay)
	+ SOverlay::Slot()
	[
		SNew(SImage)
		.Image(&ConfirmationBackgroundBrush)
	]
	+ SOverlay::Slot()
	[
		SAssignNew(Dialog, SShooterPaymentDialog)
		.PlayerOwner(PlayerOwner)
		.PaymentUrl(Url)
		.CallBackUrl("127.0.0.1")
		.OnCallbackUrlLoaded(FSimpleDelegate::CreateLambda([&]()
		{
			AsyncTask(ENamedThreads::GameThread, [&]() {
				OnClosePayment();
			});
		}))
		.OnCloseClicked(FOnClicked::CreateSP(this, &SShooterStore::OnClosePayment))
	];

	GEngine->GameViewport->AddViewportWidgetContent(MessageDialogWidget.ToSharedRef());
	FSlateApplication::Get().SetKeyboardFocus(Dialog);
}

FReply SShooterStore::OnClosePayment()
{
	GEngine->GameViewport->RemoveViewportWidgetContent(MessageDialogWidget.ToSharedRef());
	MessageDialogWidget.Reset();
	BuildInventoryItem();
	OnBuyItemFinished.ExecuteIfBound();
	FSlateApplication::Get().SetKeyboardFocus(SharedThis(this));
	return FReply::Handled();
}

FReply SShooterStore::OnBuyCancel()
{
	CloseConfirmationDialog();
	return FReply::Handled();
}

TSharedRef< FInventoryEntry > SShooterStore::CreateInventoryItem(const FAccelByteModelsItemInfo& ItemInfo)
{
	TSharedRef< FInventoryEntry > Inventory = MakeShareable(new FInventoryEntry());
	Inventory->ItemId = ItemInfo.ItemId;
	Inventory->Name = ItemInfo.Title;
	Inventory->Quantity = 0;
	for (auto& image : ItemInfo.Images)
	{
		if (image.As == ShooterGameConfig::Get().ItemImageSetAs_)
		{
			Inventory->ImageURL = image.ImageUrl;
			break;
		}
	}

	for (int j = 0; j < ItemInfo.RegionData.Num(); j++)
	{
		if (ItemInfo.RegionData[j].CurrencyType == EAccelByteItemCurrencyType::VIRTUAL || ItemInfo.RegionData[j].CurrencyType == EAccelByteItemCurrencyType::REAL)
		{
			Inventory->CurrencyCode = ItemInfo.RegionData[j].CurrencyCode;
			Inventory->Price = ItemInfo.RegionData[j].Price;
			Inventory->CurrencyType = ItemInfo.RegionData[j].CurrencyType;
			UE_LOG(LogTemp, Display, TEXT("Item title: %s"), *ItemInfo.Title);
			UE_LOG(LogTemp, Display, TEXT("Discount Purchase: %s, Discount Expire: %s"), *ItemInfo.RegionData[j].DiscountPurchaseAt.ToString(), *ItemInfo.RegionData[j].DiscountExpireAt.ToString());
			UE_LOG(LogTemp, Display, TEXT("Discount Percentage: %d, Discount Amount: %d"), ItemInfo.RegionData[j].DiscountPercentage, ItemInfo.RegionData[j].DiscountAmount);
			if ((ItemInfo.RegionData[j].DiscountPurchaseAt < FDateTime::Now() && ItemInfo.RegionData[j].DiscountExpireAt > FDateTime::Now())||
				(ItemInfo.RegionData[j].DiscountPurchaseAt == FDateTime::MinValue() && ItemInfo.RegionData[j].DiscountExpireAt == FDateTime::MinValue()))
			{
				Inventory->DiscountedPrice = ItemInfo.RegionData[j].DiscountedPrice;
				if (ItemInfo.RegionData[j].DiscountAmount == 0)
				{
					Inventory->DiscountPercentage = ItemInfo.RegionData[j].DiscountPercentage / 100.f;
				}
				else if (ItemInfo.RegionData[j].Price == 0)
				{
					Inventory->DiscountPercentage = 0;
				}
				else
				{
					Inventory->DiscountPercentage = ((ItemInfo.RegionData[j].Price - ItemInfo.RegionData[j].DiscountAmount)/ItemInfo.RegionData[j].Price) * 100.f;
				}
			}
			else
			{
				Inventory->DiscountedPrice = ItemInfo.RegionData[j].Price;
				Inventory->DiscountPercentage = 0;
			}
			UE_LOG(LogTemp, Display, TEXT("Discount Percentage: %f"), Inventory->DiscountPercentage);
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
	return Inventory;
}

void SShooterStore::OnGetItemsByCriteria(const FAccelByteModelsItemPagingSlicedResult& Result)
{
	for (int i = 0; i < Result.Data.Num(); i++)
	{
		TSharedRef< FInventoryEntry > Inventory = CreateInventoryItem(Result.Data[i]);
		InventoryList.Add(Inventory);
	}
	InventoryListWidget->RequestListRefresh();
	GetUserEntitlements();
	bRequestInventoryList = false;
}

void SShooterStore::OnGetCashItemsByCriteria(const FAccelByteModelsItemPagingSlicedResult& Result)
{
	for (int i = 0; i < Result.Data.Num(); i++)
	{
		TSharedRef< FInventoryEntry > Inventory = CreateInventoryItem(Result.Data[i]);
		CashInventoryList.Add(Inventory);
	}
	CashInventoryListWidget->RequestListRefresh();
	bRequestCashInventoryList = false;
}

void SShooterStore::OnGetItemsByCriteriaError(int32 Code, const FString& Message)
{
	bRequestInventoryList = false;
	UE_LOG(LogTemp, Display, TEXT("GetItem Error: code: %d, message: %s"), Code, *Message)
}

void SShooterStore::OnGetCashItemsByCriteriaError(int32 Code, const FString& Message)
{
	bRequestCashInventoryList = false;
	UE_LOG(LogTemp, Display, TEXT("GetCashItem Error: code: %d, message: %s"), Code, *Message)
}

void SShooterStore::GetUserEntitlements() 
{
	FRegistry::Entitlement.QueryUserEntitlements("", "", 0, 100, AccelByte::THandler<FAccelByteModelsEntitlementPagingSlicedResult>::CreateLambda([&](const FAccelByteModelsEntitlementPagingSlicedResult& Result)
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

void SShooterStore::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
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

void SShooterStore::ShowLoadingDialog()
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

void SShooterStore::CloseLoadingDialog()
{
	if (LoadingDialogWidget.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(LoadingDialogWidget.ToSharedRef());
		LoadingDialogWidget.Reset();
	}
}

void SShooterStore::ShowMessageDialog(FString Message)
{
	TSharedPtr<SShooterConfirmationDialog> Dialog;
	SAssignNew(MessageDialogWidget, SOverlay)
	+ SOverlay::Slot()
	[
		SNew(SImage)
		.Image(&ConfirmationBackgroundBrush)
	]
	+ SOverlay::Slot()
	[
		SAssignNew(Dialog, SShooterConfirmationDialog).PlayerOwner(PlayerOwner)
		.MessageText(FText::FromString(Message))
		.ConfirmText(FText::FromString("OK"))
		.OnConfirmClicked(FOnClicked::CreateLambda([&]() -> FReply {
			CloseMessageDialog();
			return FReply::Handled();
		}))
	];

	GEngine->GameViewport->AddViewportWidgetContent(MessageDialogWidget.ToSharedRef());
	FSlateApplication::Get().SetKeyboardFocus(Dialog);
}

void SShooterStore::CloseMessageDialog()
{
	if (MessageDialogWidget.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(MessageDialogWidget.ToSharedRef());
		MessageDialogWidget.Reset();
	}
}

void SShooterStore::OnBackFromPaymentBrowser(FString PaymentUrl)
{
	TSharedPtr<SShooterConfirmationDialog> Dialog;
	SAssignNew(MessageDialogWidget, SOverlay)
	+ SOverlay::Slot()
	[
		SNew(SImage)
		.Image(&ConfirmationBackgroundBrush)
	]
	+ SOverlay::Slot()
	[
		SAssignNew(Dialog, SShooterConfirmationDialog).PlayerOwner(PlayerOwner)
		.MessageText(FText::FromString("Complete Payment"))
		.ConfirmText(FText::FromString("OK"))
		.OnConfirmClicked(FOnClicked::CreateLambda([&]() -> FReply {
			CloseMessageDialog();
			BuildInventoryItem();
			OnBuyItemFinished.ExecuteIfBound();
			return FReply::Handled();
		}))
	];

	GEngine->GameViewport->AddViewportWidgetContent(MessageDialogWidget.ToSharedRef());
	FSlateApplication::Get().SetKeyboardFocus(Dialog);
}

void SShooterStore::OnFocusLost(const FFocusEvent& InFocusEvent)
{
	if (InFocusEvent.GetCause() != EFocusCause::SetDirectly)
	{
		FSlateApplication::Get().SetKeyboardFocus(SharedThis(this));
	}
}

FReply SShooterStore::OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent)
{
	return FReply::Handled().SetUserFocus(InventoryListWidget.ToSharedRef(), EFocusCause::SetDirectly);
}