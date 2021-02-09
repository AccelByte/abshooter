// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Menu/Widgets/SShooterInventory.h"
#include "UI/Menu/Widgets/SShooterCoinsWidget.h"
#include "UI/Menu/Widgets/SShooterStore.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TemporaryMenuUI.generated.h"

/**
 * TEMPORARY SOLUTION TO WRAP SLATE UI
 */

UCLASS()
class UInventoryMenuUI : public UUserWidget
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "UInventoryMenuUI")
	UMainMenuUI* Parent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "UInventoryMenuUI")
	ULocalPlayer* PlayerOwner;

public:
	UFUNCTION(BlueprintCallable, Category="UInventoryMenuUI")
	void RefreshInventory();

	//~ Begin UWidget interface
	virtual void SynchronizeProperties() override;
	// End UWidget interface

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
		
protected:
	TSharedPtr<class SShooterInventory> InventorySlateUI;

protected:
	// UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget interface

	virtual void NativeConstruct() override;
};

UCLASS()
class UCoinWidgetMenuUI : public UUserWidget
{
	GENERATED_UCLASS_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "UCoinWidgetMenuUI")
	void RefreshWallet();

	//~ Begin UWidget interface
	virtual void SynchronizeProperties() override;
	// End UWidget interface

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	TSharedPtr<class SShooterCoinsWidget> CoinsWidgetSlateUI;

protected:
	// UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget interface

	virtual void NativeConstruct() override;
};

UCLASS()
class UStoreMenuUI : public UUserWidget
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "UStoreMenuUI")
		UMainMenuUI* MainMenu;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "UStoreMenuUI")
		ULocalPlayer* PlayerOwner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "UStoreMenuUI")
		UCoinWidgetMenuUI* CoinsWidget;

public:
	UFUNCTION(BlueprintCallable, Category = "UStoreMenuUI")
	void BuildInventoryItem();

	//~ Begin UWidget interface
	virtual void SynchronizeProperties() override;
	// End UWidget interface

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

protected:
	TSharedPtr<class SShooterStore> StoreSlateUI;

protected:
	// UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget interface

	virtual void NativeConstruct() override;
};

USTRUCT(BlueprintType)
struct FPairLatencyAndRegion
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Latency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Region;
};

struct FPairLatencyAndRegion;

UCLASS(Blueprintable, BlueprintType)
class UTemporaryHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FBlueprintErrorHandler, int32, ErrorCode, const FString&, ErrorMessage);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FGetServerLatenciesSuccess, const TArray<FPairLatencyAndRegion>&, OnSuccess);
	
	UFUNCTION(BlueprintCallable)
	static void GetServerLatencies(const FGetServerLatenciesSuccess& OnSuccess, const FBlueprintErrorHandler& OnError);
	UFUNCTION(BlueprintCallable)
	static void SelectedServerLatencies(const FPairLatencyAndRegion& Server);
};