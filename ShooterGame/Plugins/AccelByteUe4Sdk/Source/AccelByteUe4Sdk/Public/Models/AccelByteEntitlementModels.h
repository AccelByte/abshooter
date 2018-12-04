// Copyright (c) 2018 AccelByte Inc. All Rights Reserved.
// This is licensed software from Accelbyte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "AccelByteItemModels.h"
#include "AccelByteEntitlementModels.generated.h"

#pragma region EntitlementEnumField

UENUM(BlueprintType)
enum class EAccelByteEntitlementClass : uint8
{
	NONE = 0 ,
	APP,
	ENTITLEMENT,
	DISTRIBUTION
};

UENUM(BlueprintType)
enum class EAccelByteEntitlementType : uint8
{
	NONE = 0,
	DURABLE,
	CONSUMABLE
};

UENUM(BlueprintType)
enum class EAccelByteEntitlementStatus : uint8
{
	NONE = 0,
	ACTIVE,
	INACTIVE,
	DISTRIBUTED,
	REVOKED,
	DELETED
};

UENUM(BlueprintType)
enum class EAccelByteAppType : uint8
{
	NONE = 0,
	GAME,
	SOFTWARE,
	DLC,
	DEMO
};

#pragma endregion EntitlementEnumField

USTRUCT(BlueprintType)
struct ACCELBYTEUE4SDK_API FAccelByteModelsEntitlementItemSnapshot
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo | ItemSnapshot ")
		FString itemId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo | ItemSnapshot ")
		FString appId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo | ItemSnapshot ")
		EAccelByteAppType appType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo | ItemSnapshot ")
		FString Sku;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo | ItemSnapshot ")
		FString Namespace;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo | ItemSnapshot ")
		FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo | ItemSnapshot ")
		int32 useCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo | ItemSnapshot ")
		EAccelByteItemType itemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo | ItemSnapshot ")
		FString targetCurrencyCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo | ItemSnapshot ")
		FString targetNamespace;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo | ItemSnapshot ")
		FString title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo | ItemSnapshot ")
		FAccelByteModelsItemInfoImage thumbnailImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo | ItemSnapshot ")
		FAccelByteModelsItemInfoRegionData regionDataItem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo | ItemSnapshot ")
		TArray<FString> itemIds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo | ItemSnapshot ")
		int32 maxCountPerUser;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo | ItemSnapshot ")
		FString region;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo | ItemSnapshot ")
		FString language;
};

USTRUCT(BlueprintType)
struct ACCELBYTEUE4SDK_API FAccelByteModelsEntitlementInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		FString id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		FString Namespace;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		EAccelByteEntitlementClass clazz;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		EAccelByteEntitlementType type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		EAccelByteEntitlementStatus status;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		FString appId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		EAccelByteAppType appType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		FString sku;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		FString userId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		FString itemId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		FString bundleItemId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		FString itemNamespace;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		int32 useCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		int32 quantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		int32 distributedQuantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		FString targetNamespace;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		FAccelByteModelsEntitlementItemSnapshot itemSnapshot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		FString startDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		FString endDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		FString grantedAt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		FString createdAt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | EntitlementInfo ")
		FString updatedAt;
};

USTRUCT(BlueprintType)
struct ACCELBYTEUE4SDK_API FAccelByteModelsEntitlementPaging
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | Paging")
		FString previous;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult | Paging")
		FString next;
};

USTRUCT(BlueprintType)
struct ACCELBYTEUE4SDK_API FAccelByteModelsEntitlementPagingSlicedResult
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult ")
		TArray<FAccelByteModelsEntitlementInfo> data;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accelbyte | Entitlement | Models | EntitlementPagingSlicedResult ")
		FAccelByteModelsEntitlementPaging paging;
};
