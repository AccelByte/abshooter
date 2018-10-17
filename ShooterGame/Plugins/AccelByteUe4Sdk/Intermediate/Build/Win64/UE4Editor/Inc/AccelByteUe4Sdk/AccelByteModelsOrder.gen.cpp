// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AccelByteUe4Sdk/Public/Models/AccelByteModelsOrder.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAccelByteModelsOrder() {}
// Cross Module References
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate();
	UPackage* Z_Construct_UPackage__Script_AccelByteUe4Sdk();
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo();
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging();
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo();
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction();
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl();
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary();
// End Cross Module References
class UScriptStruct* FAccelByteModelsOrderCreate::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsOrderCreate"), sizeof(FAccelByteModelsOrderCreate), Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsOrderCreate(FAccelByteModelsOrderCreate::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsOrderCreate"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOrderCreate
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOrderCreate()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsOrderCreate")),new UScriptStruct::TCppStructOps<FAccelByteModelsOrderCreate>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOrderCreate;
	struct Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ReturnUrl_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnUrl;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrencyCode_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_CurrencyCode;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DiscountedPrice_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_DiscountedPrice;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Price_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Price;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Quantity_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Quantity;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ItemId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ItemId;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsOrderCreate>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_ReturnUrl_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderCreate" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_ReturnUrl = { UE4CodeGen_Private::EPropertyClass::Str, "ReturnUrl", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderCreate, ReturnUrl), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_ReturnUrl_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_ReturnUrl_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_CurrencyCode_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderCreate" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_CurrencyCode = { UE4CodeGen_Private::EPropertyClass::Str, "CurrencyCode", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderCreate, CurrencyCode), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_CurrencyCode_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_CurrencyCode_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_DiscountedPrice_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderCreate" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_DiscountedPrice = { UE4CodeGen_Private::EPropertyClass::Int, "DiscountedPrice", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderCreate, DiscountedPrice), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_DiscountedPrice_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_DiscountedPrice_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_Price_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderCreate" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_Price = { UE4CodeGen_Private::EPropertyClass::Int, "Price", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderCreate, Price), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_Price_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_Price_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_Quantity_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderCreate" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_Quantity = { UE4CodeGen_Private::EPropertyClass::Int, "Quantity", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderCreate, Quantity), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_Quantity_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_Quantity_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_ItemId_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderCreate" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_ItemId = { UE4CodeGen_Private::EPropertyClass::Str, "ItemId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderCreate, ItemId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_ItemId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_ItemId_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_ReturnUrl,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_CurrencyCode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_DiscountedPrice,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_Price,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_Quantity,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::NewProp_ItemId,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsOrderCreate",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		sizeof(FAccelByteModelsOrderCreate),
		alignof(FAccelByteModelsOrderCreate),
		Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsOrderCreate"), sizeof(FAccelByteModelsOrderCreate), Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderCreate_CRC() { return 2230303798U; }
class UScriptStruct* FAccelByteModelsOrderHistoryInfo::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsOrderHistoryInfo"), sizeof(FAccelByteModelsOrderHistoryInfo), Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsOrderHistoryInfo(FAccelByteModelsOrderHistoryInfo::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsOrderHistoryInfo"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOrderHistoryInfo
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOrderHistoryInfo()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsOrderHistoryInfo")),new UScriptStruct::TCppStructOps<FAccelByteModelsOrderHistoryInfo>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOrderHistoryInfo;
	struct Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UpdatedAt_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_UpdatedAt;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CreatedAt_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_CreatedAt;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UserId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_UserId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Reason_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Reason;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Action_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Action;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Operator_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Operator;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OrderNo_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_OrderNo;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsOrderHistoryInfo>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_UpdatedAt_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderHistoryInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_UpdatedAt = { UE4CodeGen_Private::EPropertyClass::Str, "UpdatedAt", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderHistoryInfo, UpdatedAt), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_UpdatedAt_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_UpdatedAt_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_CreatedAt_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderHistoryInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_CreatedAt = { UE4CodeGen_Private::EPropertyClass::Str, "CreatedAt", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderHistoryInfo, CreatedAt), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_CreatedAt_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_CreatedAt_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_UserId_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderHistoryInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_UserId = { UE4CodeGen_Private::EPropertyClass::Str, "UserId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderHistoryInfo, UserId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_UserId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_UserId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_Reason_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderHistoryInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_Reason = { UE4CodeGen_Private::EPropertyClass::Str, "Reason", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderHistoryInfo, Reason), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_Reason_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_Reason_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_Action_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderHistoryInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_Action = { UE4CodeGen_Private::EPropertyClass::Str, "Action", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderHistoryInfo, Action), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_Action_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_Action_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_Operator_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderHistoryInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_Operator = { UE4CodeGen_Private::EPropertyClass::Str, "Operator", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderHistoryInfo, Operator), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_Operator_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_Operator_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_OrderNo_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderHistoryInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_OrderNo = { UE4CodeGen_Private::EPropertyClass::Str, "OrderNo", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderHistoryInfo, OrderNo), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_OrderNo_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_OrderNo_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_UpdatedAt,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_CreatedAt,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_UserId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_Reason,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_Action,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_Operator,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::NewProp_OrderNo,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsOrderHistoryInfo",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsOrderHistoryInfo),
		alignof(FAccelByteModelsOrderHistoryInfo),
		Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsOrderHistoryInfo"), sizeof(FAccelByteModelsOrderHistoryInfo), Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderHistoryInfo_CRC() { return 3404703375U; }
class UScriptStruct* FAccelByteModelsOrderInfoPaging::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsOrderInfoPaging"), sizeof(FAccelByteModelsOrderInfoPaging), Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsOrderInfoPaging(FAccelByteModelsOrderInfoPaging::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsOrderInfoPaging"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOrderInfoPaging
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOrderInfoPaging()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsOrderInfoPaging")),new UScriptStruct::TCppStructOps<FAccelByteModelsOrderInfoPaging>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOrderInfoPaging;
	struct Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Next_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Next;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Previous_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Previous;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsOrderInfoPaging>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_Statics::NewProp_Next_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_Statics::NewProp_Next = { UE4CodeGen_Private::EPropertyClass::Str, "Next", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoPaging, Next), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_Statics::NewProp_Next_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_Statics::NewProp_Next_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_Statics::NewProp_Previous_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_Statics::NewProp_Previous = { UE4CodeGen_Private::EPropertyClass::Str, "Previous", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoPaging, Previous), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_Statics::NewProp_Previous_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_Statics::NewProp_Previous_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_Statics::NewProp_Next,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_Statics::NewProp_Previous,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsOrderInfoPaging",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsOrderInfoPaging),
		alignof(FAccelByteModelsOrderInfoPaging),
		Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsOrderInfoPaging"), sizeof(FAccelByteModelsOrderInfoPaging), Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaging_CRC() { return 1155218636U; }
class UScriptStruct* FAccelByteModelsOrderInfo::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsOrderInfo"), sizeof(FAccelByteModelsOrderInfo), Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsOrderInfo(FAccelByteModelsOrderInfo::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsOrderInfo"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOrderInfo
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOrderInfo()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsOrderInfo")),new UScriptStruct::TCppStructOps<FAccelByteModelsOrderInfo>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOrderInfo;
	struct Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UpdatedAt_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_UpdatedAt;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CreatedAt_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_CreatedAt;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RefundedTime_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_RefundedTime;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FulfilledTime_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FulfilledTime;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ChargedTime_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ChargedTime;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CreatedTime_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_CreatedTime;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Namespace_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Namespace;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StatusReason_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_StatusReason;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Status_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Status;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EntitlementIds_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_EntitlementIds;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_EntitlementIds_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Transactions_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Transactions;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Transactions_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PaymentStationUrl_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_PaymentStationUrl;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PaymentUrl_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_PaymentUrl;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Currency_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Currency;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PaymentMethodFee_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_PaymentMethodFee;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PaymentProviderFee_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_PaymentProviderFee;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SalesTax_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_SalesTax;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Vat_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Vat;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DiscountedPrice_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_DiscountedPrice;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Price_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Price;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Quantity_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Quantity;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bSandbox_MetaData[];
#endif
		static void NewProp_bSandbox_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bSandbox;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ItemId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ItemId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UserId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_UserId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OrderNo_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_OrderNo;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsOrderInfo>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_UpdatedAt_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_UpdatedAt = { UE4CodeGen_Private::EPropertyClass::Str, "UpdatedAt", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, UpdatedAt), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_UpdatedAt_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_UpdatedAt_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_CreatedAt_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_CreatedAt = { UE4CodeGen_Private::EPropertyClass::Str, "CreatedAt", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, CreatedAt), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_CreatedAt_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_CreatedAt_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_RefundedTime_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_RefundedTime = { UE4CodeGen_Private::EPropertyClass::Str, "RefundedTime", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, RefundedTime), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_RefundedTime_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_RefundedTime_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_FulfilledTime_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_FulfilledTime = { UE4CodeGen_Private::EPropertyClass::Str, "FulfilledTime", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, FulfilledTime), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_FulfilledTime_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_FulfilledTime_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_ChargedTime_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_ChargedTime = { UE4CodeGen_Private::EPropertyClass::Str, "ChargedTime", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, ChargedTime), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_ChargedTime_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_ChargedTime_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_CreatedTime_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_CreatedTime = { UE4CodeGen_Private::EPropertyClass::Str, "CreatedTime", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, CreatedTime), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_CreatedTime_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_CreatedTime_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Namespace_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Namespace = { UE4CodeGen_Private::EPropertyClass::Str, "Namespace", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, Namespace), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Namespace_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Namespace_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_StatusReason_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
		{ "ToolTip", "['INIT', 'CHARGED', 'FINISHED', 'CHARGE_FAILED', 'ERROR', 'REFUNDED', 'DELETED']," },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_StatusReason = { UE4CodeGen_Private::EPropertyClass::Str, "StatusReason", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, StatusReason), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_StatusReason_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_StatusReason_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Status_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Status = { UE4CodeGen_Private::EPropertyClass::Str, "Status", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, Status), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Status_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Status_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_EntitlementIds_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_EntitlementIds = { UE4CodeGen_Private::EPropertyClass::Array, "EntitlementIds", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, EntitlementIds), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_EntitlementIds_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_EntitlementIds_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_EntitlementIds_Inner = { UE4CodeGen_Private::EPropertyClass::Str, "EntitlementIds", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0000000000000000, 1, nullptr, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Transactions_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Transactions = { UE4CodeGen_Private::EPropertyClass::Array, "Transactions", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, Transactions), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Transactions_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Transactions_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Transactions_Inner = { UE4CodeGen_Private::EPropertyClass::Struct, "Transactions", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0000000000000000, 1, nullptr, 0, Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_PaymentStationUrl_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_PaymentStationUrl = { UE4CodeGen_Private::EPropertyClass::Str, "PaymentStationUrl", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, PaymentStationUrl), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_PaymentStationUrl_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_PaymentStationUrl_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_PaymentUrl_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_PaymentUrl = { UE4CodeGen_Private::EPropertyClass::Struct, "PaymentUrl", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, PaymentUrl), Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl, METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_PaymentUrl_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_PaymentUrl_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Currency_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Currency = { UE4CodeGen_Private::EPropertyClass::Struct, "Currency", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, Currency), Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary, METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Currency_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Currency_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_PaymentMethodFee_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_PaymentMethodFee = { UE4CodeGen_Private::EPropertyClass::Int, "PaymentMethodFee", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, PaymentMethodFee), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_PaymentMethodFee_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_PaymentMethodFee_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_PaymentProviderFee_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_PaymentProviderFee = { UE4CodeGen_Private::EPropertyClass::Int, "PaymentProviderFee", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, PaymentProviderFee), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_PaymentProviderFee_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_PaymentProviderFee_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_SalesTax_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_SalesTax = { UE4CodeGen_Private::EPropertyClass::Int, "SalesTax", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, SalesTax), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_SalesTax_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_SalesTax_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Vat_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Vat = { UE4CodeGen_Private::EPropertyClass::Int, "Vat", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, Vat), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Vat_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Vat_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_DiscountedPrice_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_DiscountedPrice = { UE4CodeGen_Private::EPropertyClass::Int, "DiscountedPrice", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, DiscountedPrice), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_DiscountedPrice_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_DiscountedPrice_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Price_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Price = { UE4CodeGen_Private::EPropertyClass::Int, "Price", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, Price), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Price_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Price_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Quantity_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Quantity = { UE4CodeGen_Private::EPropertyClass::Int, "Quantity", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, Quantity), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Quantity_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Quantity_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_bSandbox_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_bSandbox_SetBit(void* Obj)
	{
		((FAccelByteModelsOrderInfo*)Obj)->bSandbox = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_bSandbox = { UE4CodeGen_Private::EPropertyClass::Bool, "bSandbox", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(FAccelByteModelsOrderInfo), &Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_bSandbox_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_bSandbox_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_bSandbox_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_ItemId_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_ItemId = { UE4CodeGen_Private::EPropertyClass::Str, "ItemId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, ItemId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_ItemId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_ItemId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_UserId_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_UserId = { UE4CodeGen_Private::EPropertyClass::Str, "UserId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, UserId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_UserId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_UserId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_OrderNo_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_OrderNo = { UE4CodeGen_Private::EPropertyClass::Str, "OrderNo", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfo, OrderNo), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_OrderNo_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_OrderNo_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_UpdatedAt,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_CreatedAt,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_RefundedTime,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_FulfilledTime,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_ChargedTime,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_CreatedTime,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Namespace,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_StatusReason,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Status,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_EntitlementIds,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_EntitlementIds_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Transactions,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Transactions_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_PaymentStationUrl,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_PaymentUrl,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Currency,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_PaymentMethodFee,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_PaymentProviderFee,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_SalesTax,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Vat,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_DiscountedPrice,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Price,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_Quantity,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_bSandbox,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_ItemId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_UserId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::NewProp_OrderNo,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsOrderInfo",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsOrderInfo),
		alignof(FAccelByteModelsOrderInfo),
		Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsOrderInfo"), sizeof(FAccelByteModelsOrderInfo), Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfo_CRC() { return 3386042033U; }
class UScriptStruct* FAccelByteModelsOrderInfoTransaction::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsOrderInfoTransaction"), sizeof(FAccelByteModelsOrderInfoTransaction), Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsOrderInfoTransaction(FAccelByteModelsOrderInfoTransaction::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsOrderInfoTransaction"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOrderInfoTransaction
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOrderInfoTransaction()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsOrderInfoTransaction")),new UScriptStruct::TCppStructOps<FAccelByteModelsOrderInfoTransaction>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOrderInfoTransaction;
	struct Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TransactionEndTime_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_TransactionEndTime;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TransactionStartTime_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_TransactionStartTime;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ExternalMessage_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ExternalMessage;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ExternalStatusCode_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ExternalStatusCode;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ExternalTransactionId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ExternalTransactionId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MerchantId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_MerchantId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PaymentMethodFee_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_PaymentMethodFee;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PaymentMethod_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_PaymentMethod;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PaymentProviderFee_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_PaymentProviderFee;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Provider_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Provider;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Status_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Status;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Type_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Type;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Currency_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Currency;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SalesTax_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_SalesTax;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Vat_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Vat;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Amount_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Amount;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TransactionId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_TransactionId;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsOrderInfoTransaction>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_TransactionEndTime_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | Transaction" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_TransactionEndTime = { UE4CodeGen_Private::EPropertyClass::Str, "TransactionEndTime", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoTransaction, TransactionEndTime), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_TransactionEndTime_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_TransactionEndTime_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_TransactionStartTime_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | Transaction" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_TransactionStartTime = { UE4CodeGen_Private::EPropertyClass::Str, "TransactionStartTime", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoTransaction, TransactionStartTime), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_TransactionStartTime_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_TransactionStartTime_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_ExternalMessage_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | Transaction" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_ExternalMessage = { UE4CodeGen_Private::EPropertyClass::Str, "ExternalMessage", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoTransaction, ExternalMessage), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_ExternalMessage_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_ExternalMessage_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_ExternalStatusCode_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | Transaction" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_ExternalStatusCode = { UE4CodeGen_Private::EPropertyClass::Str, "ExternalStatusCode", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoTransaction, ExternalStatusCode), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_ExternalStatusCode_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_ExternalStatusCode_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_ExternalTransactionId_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | Transaction" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_ExternalTransactionId = { UE4CodeGen_Private::EPropertyClass::Str, "ExternalTransactionId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoTransaction, ExternalTransactionId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_ExternalTransactionId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_ExternalTransactionId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_MerchantId_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | Transaction" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_MerchantId = { UE4CodeGen_Private::EPropertyClass::Str, "MerchantId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoTransaction, MerchantId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_MerchantId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_MerchantId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_PaymentMethodFee_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | Transaction" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_PaymentMethodFee = { UE4CodeGen_Private::EPropertyClass::Int, "PaymentMethodFee", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoTransaction, PaymentMethodFee), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_PaymentMethodFee_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_PaymentMethodFee_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_PaymentMethod_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | Transaction" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_PaymentMethod = { UE4CodeGen_Private::EPropertyClass::Str, "PaymentMethod", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoTransaction, PaymentMethod), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_PaymentMethod_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_PaymentMethod_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_PaymentProviderFee_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | Transaction" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
		{ "ToolTip", "['XSOLLA', 'WALLET']," },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_PaymentProviderFee = { UE4CodeGen_Private::EPropertyClass::Int, "PaymentProviderFee", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoTransaction, PaymentProviderFee), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_PaymentProviderFee_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_PaymentProviderFee_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Provider_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | Transaction" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
		{ "ToolTip", "['INIT', 'FINISHED', 'FAILED']," },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Provider = { UE4CodeGen_Private::EPropertyClass::Str, "Provider", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoTransaction, Provider), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Provider_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Provider_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Status_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | Transaction" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
		{ "ToolTip", "['CHARGE', 'REFUND']," },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Status = { UE4CodeGen_Private::EPropertyClass::Str, "Status", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoTransaction, Status), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Status_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Status_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Type_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | Transaction" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Type = { UE4CodeGen_Private::EPropertyClass::Str, "Type", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoTransaction, Type), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Type_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Type_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Currency_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | Transaction" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Currency = { UE4CodeGen_Private::EPropertyClass::Struct, "Currency", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoTransaction, Currency), Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary, METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Currency_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Currency_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_SalesTax_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | Transaction" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_SalesTax = { UE4CodeGen_Private::EPropertyClass::Int, "SalesTax", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoTransaction, SalesTax), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_SalesTax_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_SalesTax_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Vat_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | Transaction" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Vat = { UE4CodeGen_Private::EPropertyClass::Int, "Vat", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoTransaction, Vat), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Vat_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Vat_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Amount_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | Transaction" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Amount = { UE4CodeGen_Private::EPropertyClass::Int, "Amount", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoTransaction, Amount), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Amount_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Amount_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_TransactionId_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | Transaction" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_TransactionId = { UE4CodeGen_Private::EPropertyClass::Str, "TransactionId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoTransaction, TransactionId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_TransactionId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_TransactionId_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_TransactionEndTime,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_TransactionStartTime,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_ExternalMessage,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_ExternalStatusCode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_ExternalTransactionId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_MerchantId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_PaymentMethodFee,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_PaymentMethod,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_PaymentProviderFee,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Provider,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Status,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Type,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Currency,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_SalesTax,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Vat,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_Amount,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::NewProp_TransactionId,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsOrderInfoTransaction",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsOrderInfoTransaction),
		alignof(FAccelByteModelsOrderInfoTransaction),
		Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsOrderInfoTransaction"), sizeof(FAccelByteModelsOrderInfoTransaction), Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoTransaction_CRC() { return 3642527685U; }
class UScriptStruct* FAccelByteModelsOrderInfoCurrencySummary::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsOrderInfoCurrencySummary"), sizeof(FAccelByteModelsOrderInfoCurrencySummary), Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary(FAccelByteModelsOrderInfoCurrencySummary::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsOrderInfoCurrencySummary"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOrderInfoCurrencySummary
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOrderInfoCurrencySummary()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsOrderInfoCurrencySummary")),new UScriptStruct::TCppStructOps<FAccelByteModelsOrderInfoCurrencySummary>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOrderInfoCurrencySummary;
	struct Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Decimals_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Decimals;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Namespace_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Namespace;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrencySymbol_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_CurrencySymbol;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrencyType_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_CurrencyType;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrencyCode_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_CurrencyCode;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsOrderInfoCurrencySummary>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_Decimals_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | CurrencySummary" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_Decimals = { UE4CodeGen_Private::EPropertyClass::Int, "Decimals", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoCurrencySummary, Decimals), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_Decimals_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_Decimals_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_Namespace_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | CurrencySummary" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_Namespace = { UE4CodeGen_Private::EPropertyClass::Str, "Namespace", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoCurrencySummary, Namespace), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_Namespace_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_Namespace_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_CurrencySymbol_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | CurrencySummary" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_CurrencySymbol = { UE4CodeGen_Private::EPropertyClass::Str, "CurrencySymbol", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoCurrencySummary, CurrencySymbol), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_CurrencySymbol_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_CurrencySymbol_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_CurrencyType_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | CurrencySummary" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_CurrencyType = { UE4CodeGen_Private::EPropertyClass::Str, "CurrencyType", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoCurrencySummary, CurrencyType), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_CurrencyType_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_CurrencyType_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_CurrencyCode_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | CurrencySummary" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_CurrencyCode = { UE4CodeGen_Private::EPropertyClass::Str, "CurrencyCode", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoCurrencySummary, CurrencyCode), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_CurrencyCode_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_CurrencyCode_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_Decimals,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_Namespace,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_CurrencySymbol,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_CurrencyType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::NewProp_CurrencyCode,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsOrderInfoCurrencySummary",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsOrderInfoCurrencySummary),
		alignof(FAccelByteModelsOrderInfoCurrencySummary),
		Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsOrderInfoCurrencySummary"), sizeof(FAccelByteModelsOrderInfoCurrencySummary), Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoCurrencySummary_CRC() { return 1067897461U; }
class UScriptStruct* FAccelByteModelsOrderInfoPaymentUrl::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsOrderInfoPaymentUrl"), sizeof(FAccelByteModelsOrderInfoPaymentUrl), Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl(FAccelByteModelsOrderInfoPaymentUrl::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsOrderInfoPaymentUrl"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOrderInfoPaymentUrl
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOrderInfoPaymentUrl()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsOrderInfoPaymentUrl")),new UScriptStruct::TCppStructOps<FAccelByteModelsOrderInfoPaymentUrl>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOrderInfoPaymentUrl;
	struct Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PaymentType_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_PaymentType;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ReturnUrl_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnUrl;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PaymentToken_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_PaymentToken;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PaymentUrl_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_PaymentUrl;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PaymentProvider_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_PaymentProvider;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsOrderInfoPaymentUrl>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_PaymentType_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | PaymentUrl" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_PaymentType = { UE4CodeGen_Private::EPropertyClass::Str, "PaymentType", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoPaymentUrl, PaymentType), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_PaymentType_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_PaymentType_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_ReturnUrl_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | PaymentUrl" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_ReturnUrl = { UE4CodeGen_Private::EPropertyClass::Str, "ReturnUrl", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoPaymentUrl, ReturnUrl), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_ReturnUrl_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_ReturnUrl_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_PaymentToken_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | PaymentUrl" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_PaymentToken = { UE4CodeGen_Private::EPropertyClass::Str, "PaymentToken", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoPaymentUrl, PaymentToken), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_PaymentToken_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_PaymentToken_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_PaymentUrl_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | PaymentUrl" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_PaymentUrl = { UE4CodeGen_Private::EPropertyClass::Str, "PaymentUrl", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoPaymentUrl, PaymentUrl), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_PaymentUrl_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_PaymentUrl_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_PaymentProvider_MetaData[] = {
		{ "Category", "AccelByte | Models | Order | OrderInfo | PaymentUrl" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsOrder.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_PaymentProvider = { UE4CodeGen_Private::EPropertyClass::Str, "PaymentProvider", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOrderInfoPaymentUrl, PaymentProvider), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_PaymentProvider_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_PaymentProvider_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_PaymentType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_ReturnUrl,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_PaymentToken,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_PaymentUrl,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::NewProp_PaymentProvider,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsOrderInfoPaymentUrl",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsOrderInfoPaymentUrl),
		alignof(FAccelByteModelsOrderInfoPaymentUrl),
		Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsOrderInfoPaymentUrl"), sizeof(FAccelByteModelsOrderInfoPaymentUrl), Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOrderInfoPaymentUrl_CRC() { return 279511895U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
