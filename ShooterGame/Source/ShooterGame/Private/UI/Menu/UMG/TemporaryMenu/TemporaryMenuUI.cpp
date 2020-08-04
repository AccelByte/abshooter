// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "TemporaryMenuUI.h"
#include "Serialization/JsonSerializerMacros.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Base64.h"
#include "ShooterGameConfig.h"
//AccelByte
#include "Core/AccelByteRegistry.h"
#include "AccelByteWalletApi.h"
#include "AccelByteQos.h"

#pragma region UInventoryMenuUI

UInventoryMenuUI::UInventoryMenuUI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsVariable = true;
}

void UInventoryMenuUI::RefreshInventory()
{
	InventorySlateUI->BuildInventoryItem();
}

void UInventoryMenuUI::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	InventorySlateUI.Reset();
}

TSharedRef<SWidget> UInventoryMenuUI::RebuildWidget()
{
	if (!IsDesignTime())
	{
		InventorySlateUI = SNew(SShooterInventory)
			.UOwnerWidget(this->Parent)
			.PlayerOwner(this->PlayerOwner);

		InventorySlateUI->BuildInventoryItem();
		return InventorySlateUI.ToSharedRef();
	}
	else
	{
		return SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString("DUMMY INVENTORY"))
			];
	}
}

void UInventoryMenuUI::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UInventoryMenuUI::NativeConstruct()
{
	Super::NativeConstruct();
}

#pragma endregion UInventoryMenuUI

#pragma region UCoinWidgetMenuUI

UCoinWidgetMenuUI::UCoinWidgetMenuUI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsVariable = true;
}

void UCoinWidgetMenuUI::RefreshWallet()
{
	FRegistry::Wallet.GetWalletInfoByCurrencyCode(
		"SGC",
		AccelByte::THandler<FAccelByteModelsWalletInfo>::CreateLambda([&](const FAccelByteModelsWalletInfo& Response){
			this->CoinsWidgetSlateUI->Balance = Response.Balance;
		}),
		FErrorHandler::CreateLambda([&](int32 Code, const FString& Message){
			this->CoinsWidgetSlateUI->Balance = -1;
		})
		);
}

void UCoinWidgetMenuUI::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	CoinsWidgetSlateUI.Reset();
}

TSharedRef<SWidget> UCoinWidgetMenuUI::RebuildWidget()
{
	if (!IsDesignTime())
	{
		CoinsWidgetSlateUI = SNew(SShooterCoinsWidget);
		return CoinsWidgetSlateUI.ToSharedRef();
	}
	else
	{
		return SNew(SBox)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Top)
			[
				SNew(STextBlock)
				.Text(FText::FromString("DUMMY WALLET"))
			];
	}
}

void UCoinWidgetMenuUI::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UCoinWidgetMenuUI::NativeConstruct()
{
	Super::NativeConstruct();
}

#pragma endregion UCoinWidgetMenuUI

#pragma region UStoreMenuUI

UStoreMenuUI::UStoreMenuUI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsVariable = true;
}

void UStoreMenuUI::BuildInventoryItem()
{
	StoreSlateUI->BuildInventoryItem();
}

void UStoreMenuUI::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	StoreSlateUI.Reset();
}

TSharedRef<SWidget> UStoreMenuUI::RebuildWidget()
{
	if (!IsDesignTime())
	{
		StoreSlateUI = SNew(SShooterStore)
			.UOwnerWidget(this->MainMenu)
			.PlayerOwner(this->PlayerOwner)
			.OnBuyItemFinished(FSimpleDelegate::CreateLambda([&]()
				{
					CoinsWidget->RefreshWallet();
				}))
			.CoinsWidget(CoinsWidget->CoinsWidgetSlateUI);
		return StoreSlateUI.ToSharedRef();
	}
	else
	{
		return SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString("DUMMY STORE"))
			];
	}
}

void UStoreMenuUI::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UStoreMenuUI::NativeConstruct()
{
	Super::NativeConstruct();
}

#pragma endregion UStoreMenuUI

#pragma region UTemporaryHelper
void UTemporaryHelper::GetServerLatencies(const FGetServerLatenciesSuccess& OnSuccess, const FBlueprintErrorHandler& OnError)
{
	FRegistry::Qos.GetServerLatencies(THandler<TArray<TPair<FString, float>>>::CreateLambda([=](TArray<TPair<FString, float>> Result) {
		ShooterGameConfig::Get().SetServerLatencies(Result);

		TArray<FPairLatencyAndRegion> Out;
		for (auto i = 0; i < Result.Num(); i++)
		{
			FPairLatencyAndRegion tmp;
			tmp.Latency = Result[i].Value;
			tmp.Region = Result[i].Key;
			Out.Add(tmp);
		}
		OnSuccess.ExecuteIfBound(Out);
		}),
		AccelByte::FErrorHandler::CreateLambda([=](int32 ErrorCode, FString ErrorString) {
			UE_LOG(LogTemp, Log, TEXT("Could not obtain server latencies from QoS endpoint. ErrorCode: %d\nMessage:%s"), ErrorCode, *ErrorString);
			OnError.ExecuteIfBound(ErrorCode, ErrorString);
		}));
};

void UTemporaryHelper::SelectedServerLatencies(const FPairLatencyAndRegion& Server)
{
	ShooterGameConfig::Get().SelectRegion(TPair<FString, float>(Server.Region, Server.Latency));
}
#pragma endregion UTemporaryHelper
