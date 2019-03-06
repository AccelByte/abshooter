
#include "ShooterGame.h"
#include "SShooterInventory.h"
#include "ShooterStyle.h"
#include "SShooterMenuWidget.h"
#include "ShooterMenuWidgetStyle.h"
#include "ShooterUIHelpers.h"
#include "SShooterInventoryItem.h"
#include "ShooterGameViewportClient.h"
#include "ShooterGameInstance.h"
#include "SShooterConfirmationDialog.h"
#include "AccelByteOrderApi.h"
#include "AccelByteItemApi.h"
#include "AccelByteEntitlementApi.h"
#include "AccelByteError.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"
#include "ShooterInventoryWidgetStyle.h"

using namespace AccelByte::Api;

SShooterInventory::SShooterInventory()
	: ConfirmationBackgroundBrush(FLinearColor(0, 0, 0, 0.8f))
	, TileWidth(388)
	, TileHeight(200)
	, TileColumn(2)
	, TileRow(2)
	, TileItemWidthRatio(0.2213f)
	, TileItemHeightRatio(0.2546f)
	, PaddingTopRatio(0.1944f)
{
}

void SShooterInventory::Construct(const FArguments& InArgs)
{
	PlayerOwner = InArgs._PlayerOwner;
	OwnerWidget = InArgs._OwnerWidget;
	OnBuyItemFinished = InArgs._OnBuyItemFinished;

	const FShooterInventoryStyle* InventoryStyle = &FShooterStyle::Get().GetWidgetStyle<FShooterInventoryStyle>("DefaultShooterInventoryStyle");
	const FShooterMenuStyle* MenuStyle = &FShooterStyle::Get().GetWidgetStyle<FShooterMenuStyle>("DefaultShooterMenuStyle");

	ChildSlot
	.VAlign(VAlign_Fill)
	.HAlign(HAlign_Fill)
	[
		SNew(SOverlay)
#pragma region Background
		+ SOverlay::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SBox)
			.WidthOverride(TAttribute<FOptionalSize>::Create([&]() -> FOptionalSize
			{
				return FOptionalSize(GetScreenWidth());
			}))
			.HeightOverride(TAttribute<FOptionalSize>::Create([&]() -> FOptionalSize
			{
				return FOptionalSize(GetScreenHeight());
			}))
			[
				SNew(SBox)
			]
		]
#pragma endregion Background
#pragma region Content
		+ SOverlay::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Left)
		.Padding(TAttribute<FMargin>::Create([&]() -> FMargin
		{
			return FMargin(GetScreenWidth() * 0.11f, GetScreenHeight() * PaddingTopRatio, 0, 0);
		}))
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			[
				SNew(SBox)
				.VAlign(VAlign_Fill)
				.HAlign(HAlign_Fill)
				.Padding(0)
				.WidthOverride(TAttribute<FOptionalSize>::Create([&]() -> FOptionalSize 
				{
					return GetTileViewWidth(InventoryList);
				}))
				.HeightOverride(this, &SShooterInventory::GetTileViewHeight)
				[
					SAssignNew(InventoryListWidget, STileView< TSharedPtr<FInventoryEntry> >)
					.ItemWidth(this, &SShooterInventory::GetItemWidth)
					.ItemHeight(this, &SShooterInventory::GetItemHeight)
					.ListItemsSource(&InventoryList)
					.ExternalScrollbar(ItemsScrollBar)
					.OnSelectionChanged(this, &SShooterInventory::EntrySelectionChanged)
					.OnGenerateTile(this, &SShooterInventory::OnGenerateWidgetForTileView)
					.SelectionMode(ESelectionMode::Single)
				]
			]
			+ SHorizontalBox::Slot()	//Scroll bar
			.AutoWidth()
			[
				SNew(SBox)
				.HAlign(HAlign_Right)
				.Padding(FMargin(0, 0, 0, 0))
				[
					SAssignNew(ItemsScrollBar, SScrollBar)
					.IsEnabled(true)
					.Thickness(FVector2D(2.0f, 2.0f))
					.Orientation(EOrientation::Orient_Vertical)
					.Visibility(EVisibility::Visible)
					.Style(&InventoryStyle->ScrollBarStyle)
				]
			]
		]
#pragma endregion Content
		+ SOverlay::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("Empty")))
			.Visibility(TAttribute<EVisibility>::Create([&]()
			{
				return InventoryList.Num() == 0 ? EVisibility::Visible : EVisibility::Collapsed;
			}))
		]
		
		+ SOverlay::Slot()
		.VAlign(VAlign_Bottom)
		.HAlign(HAlign_Right)
		.Padding(0, 0, 200, 17)
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
					static_cast<SShooterMenuWidget*>(OwnerWidget.Get())->MenuGoBack();
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
	];
	//BuildInventoryItem();
}

float SShooterInventory::GetScreenWidth() const
{
	FVector2D Result = FVector2D(1, 1);
	GEngine->GameViewport->GetViewportSize(Result);
	return Result.X;
}

float SShooterInventory::GetScreenHeight() const
{
	FVector2D Result = FVector2D(1, 1);
	GEngine->GameViewport->GetViewportSize(Result);
	return Result.Y;
}

FOptionalSize SShooterInventory::GetTileViewWidth(const TArray<TSharedPtr<FInventoryEntry>>& List) const
{
	return FOptionalSize(GetItemWidth() * TileColumn + (List.Num() > TileColumn * TileRow ? 16 : 0));
}

FOptionalSize SShooterInventory::GetTileViewHeight() const
{
	return FOptionalSize(FMath::Max(GetScreenHeight() * (1.0f - PaddingTopRatio), GetItemHeight() * TileRow) + 4);
}

float SShooterInventory::GetItemWidth() const
{
	return FMath::Max(GetScreenWidth() * TileItemWidthRatio, 426.0f);
}

float SShooterInventory::GetItemHeight() const
{
	return FMath::Max(GetScreenHeight() * TileItemHeightRatio, 240.0f);
}

void SShooterInventory::BuildInventoryItem()
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
		Item::GetItemsByCriteria(GI->UserProfileInfo.Language, Locale,
			"/item", EAccelByteItemType::INGAMEITEM, EAccelByteItemStatus::ACTIVE, 0, 20,
			AccelByte::THandler<FAccelByteModelsItemPagingSlicedResult>::CreateSP(this, &SShooterInventory::OnGetItemsByCriteria),
			AccelByte::FErrorHandler::CreateSP(this, &SShooterInventory::OnGetItemsByCriteriaError));
	}
}

TSharedRef<ITableRow> SShooterInventory::OnGenerateWidgetForTileView(TSharedPtr<FInventoryEntry> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(SShooterInventoryItem, OwnerTable, PlayerOwner, Item);
}

void SShooterInventory::EntrySelectionChanged(TSharedPtr<FInventoryEntry> InItem, ESelectInfo::Type SelectInfo)
{
	SelectedItem = InItem;
}

TSharedRef< FInventoryEntry > SShooterInventory::CreateInventoryItem(const FAccelByteModelsItemInfo& ItemInfo)
{
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
	return Inventory;
}

void SShooterInventory::OnGetItemsByCriteria(const FAccelByteModelsItemPagingSlicedResult& Result)
{
	ItemModelList = Result.Data;
	GetUserEntitlements();
	bRequestInventoryList = false;
}

void SShooterInventory::OnGetItemsByCriteriaError(int32 Code, const FString& Message)
{
	bRequestInventoryList = false;
	UE_LOG(LogTemp, Display, TEXT("GetItem Error: code: %d, message: %s"), Code, *Message)
}

void SShooterInventory::GetUserEntitlements() 
{
	Entitlement::QueryUserEntitlement("", "", 0, 100, AccelByte::THandler<FAccelByteModelsEntitlementPagingSlicedResult>::CreateLambda([&](const FAccelByteModelsEntitlementPagingSlicedResult& Result)
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

		for (const FAccelByteModelsItemInfo& Item : ItemModelList)
		{
			int* Quantity = Quantities.Find(Item.ItemId);
			int ItemQuantity = 0;
			if (Quantity != nullptr)
			{
				ItemQuantity = (*Quantity > 0) ? *Quantity : 1;
			}
			if (ItemQuantity > 0)
			{
				TSharedRef< FInventoryEntry > Entry = CreateInventoryItem(Item);
				Entry->Owned = true;
				Entry->Quantity = ItemQuantity;
				InventoryList.Add(Entry);
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