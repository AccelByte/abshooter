// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AccelByteUe4Sdk/Public/Models/AccelByteModelsItem.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAccelByteModelsItem() {}
// Cross Module References
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult();
	UPackage* Z_Construct_UPackage__Script_AccelByteUe4Sdk();
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging();
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsItemInfo();
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FDateTime();
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage();
// End Cross Module References
class UScriptStruct* FAccelByteModelsItemPagingSlicedResult::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsItemPagingSlicedResult"), sizeof(FAccelByteModelsItemPagingSlicedResult), Get_Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult(FAccelByteModelsItemPagingSlicedResult::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsItemPagingSlicedResult"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsItemPagingSlicedResult
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsItemPagingSlicedResult()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsItemPagingSlicedResult")),new UScriptStruct::TCppStructOps<FAccelByteModelsItemPagingSlicedResult>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsItemPagingSlicedResult;
	struct Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Paging_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Paging;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Data_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Data;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Data_Inner;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsItemPagingSlicedResult>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics::NewProp_Paging_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemPagingSlicedResult" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics::NewProp_Paging = { UE4CodeGen_Private::EPropertyClass::Struct, "Paging", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemPagingSlicedResult, Paging), Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging, METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics::NewProp_Paging_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics::NewProp_Paging_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics::NewProp_Data_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemPagingSlicedResult" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics::NewProp_Data = { UE4CodeGen_Private::EPropertyClass::Array, "Data", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemPagingSlicedResult, Data), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics::NewProp_Data_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics::NewProp_Data_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics::NewProp_Data_Inner = { UE4CodeGen_Private::EPropertyClass::Struct, "Data", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0000000000000000, 1, nullptr, 0, Z_Construct_UScriptStruct_FAccelByteModelsItemInfo, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics::NewProp_Paging,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics::NewProp_Data,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics::NewProp_Data_Inner,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsItemPagingSlicedResult",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsItemPagingSlicedResult),
		alignof(FAccelByteModelsItemPagingSlicedResult),
		Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsItemPagingSlicedResult"), sizeof(FAccelByteModelsItemPagingSlicedResult), Get_Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResult_CRC() { return 2790519409U; }
class UScriptStruct* FAccelByteModelsItemPagingSlicedResultPaging::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsItemPagingSlicedResultPaging"), sizeof(FAccelByteModelsItemPagingSlicedResultPaging), Get_Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging(FAccelByteModelsItemPagingSlicedResultPaging::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsItemPagingSlicedResultPaging"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsItemPagingSlicedResultPaging
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsItemPagingSlicedResultPaging()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsItemPagingSlicedResultPaging")),new UScriptStruct::TCppStructOps<FAccelByteModelsItemPagingSlicedResultPaging>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsItemPagingSlicedResultPaging;
	struct Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_Statics
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsItemPagingSlicedResultPaging>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_Statics::NewProp_Next_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemPagingSlicedResult | Paging" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_Statics::NewProp_Next = { UE4CodeGen_Private::EPropertyClass::Str, "Next", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemPagingSlicedResultPaging, Next), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_Statics::NewProp_Next_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_Statics::NewProp_Next_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_Statics::NewProp_Previous_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemPagingSlicedResult | Paging" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_Statics::NewProp_Previous = { UE4CodeGen_Private::EPropertyClass::Str, "Previous", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemPagingSlicedResultPaging, Previous), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_Statics::NewProp_Previous_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_Statics::NewProp_Previous_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_Statics::NewProp_Next,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_Statics::NewProp_Previous,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsItemPagingSlicedResultPaging",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsItemPagingSlicedResultPaging),
		alignof(FAccelByteModelsItemPagingSlicedResultPaging),
		Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsItemPagingSlicedResultPaging"), sizeof(FAccelByteModelsItemPagingSlicedResultPaging), Get_Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsItemPagingSlicedResultPaging_CRC() { return 1888919534U; }
class UScriptStruct* FAccelByteModelsItemInfo::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsItemInfo"), sizeof(FAccelByteModelsItemInfo), Get_Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsItemInfo(FAccelByteModelsItemInfo::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsItemInfo"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsItemInfo
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsItemInfo()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsItemInfo")),new UScriptStruct::TCppStructOps<FAccelByteModelsItemInfo>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsItemInfo;
	struct Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Tags_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Tags;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Tags_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ItemIds_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ItemIds;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ItemIds_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RegionData_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_RegionData;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_RegionData_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TargetNamespace_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_TargetNamespace;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TargetCurrencyCode_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_TargetCurrencyCode;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UpdatedAt_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_UpdatedAt;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CreatedAt_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_CreatedAt;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ItemType_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ItemType;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Status_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Status;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CategoryPath_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_CategoryPath;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UseCount_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_UseCount;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EntitlementType_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_EntitlementType;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EntitlementName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_EntitlementName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Namespace_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Namespace;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Sku_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Sku;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AppType_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AppType;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AppId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AppId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ItemId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ItemId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ThumbnailImage_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ThumbnailImage;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Images_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Images;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Images_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LongDescription_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_LongDescription;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Description_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Description;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Title_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Title;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsItemInfo>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Tags_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Tags = { UE4CodeGen_Private::EPropertyClass::Array, "Tags", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, Tags), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Tags_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Tags_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Tags_Inner = { UE4CodeGen_Private::EPropertyClass::Str, "Tags", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0000000000000000, 1, nullptr, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ItemIds_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ItemIds = { UE4CodeGen_Private::EPropertyClass::Array, "ItemIds", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, ItemIds), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ItemIds_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ItemIds_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ItemIds_Inner = { UE4CodeGen_Private::EPropertyClass::Str, "ItemIds", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0000000000000000, 1, nullptr, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_RegionData_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_RegionData = { UE4CodeGen_Private::EPropertyClass::Array, "RegionData", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, RegionData), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_RegionData_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_RegionData_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_RegionData_Inner = { UE4CodeGen_Private::EPropertyClass::Struct, "RegionData", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0000000000000000, 1, nullptr, 0, Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_TargetNamespace_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_TargetNamespace = { UE4CodeGen_Private::EPropertyClass::Str, "TargetNamespace", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, TargetNamespace), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_TargetNamespace_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_TargetNamespace_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_TargetCurrencyCode_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_TargetCurrencyCode = { UE4CodeGen_Private::EPropertyClass::Str, "TargetCurrencyCode", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, TargetCurrencyCode), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_TargetCurrencyCode_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_TargetCurrencyCode_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_UpdatedAt_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_UpdatedAt = { UE4CodeGen_Private::EPropertyClass::Struct, "UpdatedAt", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, UpdatedAt), Z_Construct_UScriptStruct_FDateTime, METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_UpdatedAt_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_UpdatedAt_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_CreatedAt_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_CreatedAt = { UE4CodeGen_Private::EPropertyClass::Struct, "CreatedAt", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, CreatedAt), Z_Construct_UScriptStruct_FDateTime, METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_CreatedAt_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_CreatedAt_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ItemType_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ItemType = { UE4CodeGen_Private::EPropertyClass::Str, "ItemType", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, ItemType), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ItemType_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ItemType_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Status_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Status = { UE4CodeGen_Private::EPropertyClass::Str, "Status", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, Status), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Status_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Status_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_CategoryPath_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_CategoryPath = { UE4CodeGen_Private::EPropertyClass::Str, "CategoryPath", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, CategoryPath), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_CategoryPath_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_CategoryPath_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_UseCount_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_UseCount = { UE4CodeGen_Private::EPropertyClass::Int, "UseCount", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, UseCount), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_UseCount_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_UseCount_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_EntitlementType_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_EntitlementType = { UE4CodeGen_Private::EPropertyClass::Str, "EntitlementType", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, EntitlementType), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_EntitlementType_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_EntitlementType_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_EntitlementName_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_EntitlementName = { UE4CodeGen_Private::EPropertyClass::Str, "EntitlementName", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, EntitlementName), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_EntitlementName_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_EntitlementName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Namespace_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Namespace = { UE4CodeGen_Private::EPropertyClass::Str, "Namespace", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, Namespace), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Namespace_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Namespace_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Sku_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Sku = { UE4CodeGen_Private::EPropertyClass::Str, "Sku", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, Sku), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Sku_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Sku_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_AppType_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_AppType = { UE4CodeGen_Private::EPropertyClass::Str, "AppType", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, AppType), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_AppType_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_AppType_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_AppId_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_AppId = { UE4CodeGen_Private::EPropertyClass::Str, "AppId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, AppId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_AppId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_AppId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ItemId_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ItemId = { UE4CodeGen_Private::EPropertyClass::Str, "ItemId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, ItemId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ItemId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ItemId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ThumbnailImage_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ThumbnailImage = { UE4CodeGen_Private::EPropertyClass::Struct, "ThumbnailImage", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, ThumbnailImage), Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage, METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ThumbnailImage_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ThumbnailImage_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Images_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Images = { UE4CodeGen_Private::EPropertyClass::Array, "Images", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, Images), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Images_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Images_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Images_Inner = { UE4CodeGen_Private::EPropertyClass::Struct, "Images", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0000000000000000, 1, nullptr, 0, Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_LongDescription_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_LongDescription = { UE4CodeGen_Private::EPropertyClass::Str, "LongDescription", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, LongDescription), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_LongDescription_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_LongDescription_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Description_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Description = { UE4CodeGen_Private::EPropertyClass::Str, "Description", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, Description), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Description_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Description_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Title_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Title = { UE4CodeGen_Private::EPropertyClass::Str, "Title", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfo, Title), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Title_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Title_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Tags,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Tags_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ItemIds,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ItemIds_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_RegionData,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_RegionData_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_TargetNamespace,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_TargetCurrencyCode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_UpdatedAt,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_CreatedAt,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ItemType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Status,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_CategoryPath,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_UseCount,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_EntitlementType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_EntitlementName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Namespace,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Sku,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_AppType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_AppId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ItemId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_ThumbnailImage,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Images,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Images_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_LongDescription,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Description,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::NewProp_Title,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsItemInfo",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsItemInfo),
		alignof(FAccelByteModelsItemInfo),
		Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsItemInfo()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsItemInfo"), sizeof(FAccelByteModelsItemInfo), Get_Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsItemInfo_CRC() { return 2752821320U; }
class UScriptStruct* FAccelByteModelsItemInfoImage::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsItemInfoImage"), sizeof(FAccelByteModelsItemInfoImage), Get_Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsItemInfoImage(FAccelByteModelsItemInfoImage::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsItemInfoImage"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsItemInfoImage
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsItemInfoImage()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsItemInfoImage")),new UScriptStruct::TCppStructOps<FAccelByteModelsItemInfoImage>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsItemInfoImage;
	struct Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SmallImageUrl_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_SmallImageUrl;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ImageUrl_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ImageUrl;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Width_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Width;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Height_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Height;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsItemInfoImage>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::NewProp_SmallImageUrl_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo | Image" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::NewProp_SmallImageUrl = { UE4CodeGen_Private::EPropertyClass::Str, "SmallImageUrl", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfoImage, SmallImageUrl), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::NewProp_SmallImageUrl_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::NewProp_SmallImageUrl_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::NewProp_ImageUrl_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo | Image" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::NewProp_ImageUrl = { UE4CodeGen_Private::EPropertyClass::Str, "ImageUrl", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfoImage, ImageUrl), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::NewProp_ImageUrl_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::NewProp_ImageUrl_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::NewProp_Width_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo | Image" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::NewProp_Width = { UE4CodeGen_Private::EPropertyClass::Int, "Width", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfoImage, Width), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::NewProp_Width_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::NewProp_Width_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::NewProp_Height_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo | Image" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::NewProp_Height = { UE4CodeGen_Private::EPropertyClass::Int, "Height", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfoImage, Height), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::NewProp_Height_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::NewProp_Height_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::NewProp_SmallImageUrl,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::NewProp_ImageUrl,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::NewProp_Width,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::NewProp_Height,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsItemInfoImage",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsItemInfoImage),
		alignof(FAccelByteModelsItemInfoImage),
		Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsItemInfoImage"), sizeof(FAccelByteModelsItemInfoImage), Get_Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsItemInfoImage_CRC() { return 2482256059U; }
class UScriptStruct* FAccelByteModelsItemInfoRegionData::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsItemInfoRegionData"), sizeof(FAccelByteModelsItemInfoRegionData), Get_Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsItemInfoRegionData(FAccelByteModelsItemInfoRegionData::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsItemInfoRegionData"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsItemInfoRegionData
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsItemInfoRegionData()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsItemInfoRegionData")),new UScriptStruct::TCppStructOps<FAccelByteModelsItemInfoRegionData>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsItemInfoRegionData;
	struct Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DiscountTotalNumPerAccount_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_DiscountTotalNumPerAccount;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DiscountTotalNum_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_DiscountTotalNum;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DiscountExpireAt_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_DiscountExpireAt;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DiscountPurchaseAt_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_DiscountPurchaseAt;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TotalNumPerAccount_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_TotalNumPerAccount;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TotalNum_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_TotalNum;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ExpireAt_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ExpireAt;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PurchaseAt_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_PurchaseAt;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrencyNamespace_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_CurrencyNamespace;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrencyType_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_CurrencyType;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrencyCode_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_CurrencyCode;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DiscountedPrice_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_DiscountedPrice;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DiscountAmount_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_DiscountAmount;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DiscountPercentage_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_DiscountPercentage;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Price_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Price;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsItemInfoRegionData>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountTotalNumPerAccount_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo | RegionData" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountTotalNumPerAccount = { UE4CodeGen_Private::EPropertyClass::Int, "DiscountTotalNumPerAccount", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfoRegionData, DiscountTotalNumPerAccount), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountTotalNumPerAccount_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountTotalNumPerAccount_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountTotalNum_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo | RegionData" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountTotalNum = { UE4CodeGen_Private::EPropertyClass::Int, "DiscountTotalNum", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfoRegionData, DiscountTotalNum), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountTotalNum_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountTotalNum_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountExpireAt_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo | RegionData" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountExpireAt = { UE4CodeGen_Private::EPropertyClass::Str, "DiscountExpireAt", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfoRegionData, DiscountExpireAt), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountExpireAt_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountExpireAt_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountPurchaseAt_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo | RegionData" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountPurchaseAt = { UE4CodeGen_Private::EPropertyClass::Str, "DiscountPurchaseAt", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfoRegionData, DiscountPurchaseAt), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountPurchaseAt_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountPurchaseAt_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_TotalNumPerAccount_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo | RegionData" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_TotalNumPerAccount = { UE4CodeGen_Private::EPropertyClass::Int, "TotalNumPerAccount", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfoRegionData, TotalNumPerAccount), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_TotalNumPerAccount_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_TotalNumPerAccount_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_TotalNum_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo | RegionData" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_TotalNum = { UE4CodeGen_Private::EPropertyClass::Int, "TotalNum", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfoRegionData, TotalNum), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_TotalNum_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_TotalNum_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_ExpireAt_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo | RegionData" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_ExpireAt = { UE4CodeGen_Private::EPropertyClass::Str, "ExpireAt", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfoRegionData, ExpireAt), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_ExpireAt_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_ExpireAt_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_PurchaseAt_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo | RegionData" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_PurchaseAt = { UE4CodeGen_Private::EPropertyClass::Str, "PurchaseAt", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfoRegionData, PurchaseAt), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_PurchaseAt_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_PurchaseAt_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_CurrencyNamespace_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo | RegionData" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_CurrencyNamespace = { UE4CodeGen_Private::EPropertyClass::Str, "CurrencyNamespace", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfoRegionData, CurrencyNamespace), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_CurrencyNamespace_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_CurrencyNamespace_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_CurrencyType_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo | RegionData" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_CurrencyType = { UE4CodeGen_Private::EPropertyClass::Str, "CurrencyType", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfoRegionData, CurrencyType), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_CurrencyType_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_CurrencyType_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_CurrencyCode_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo | RegionData" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_CurrencyCode = { UE4CodeGen_Private::EPropertyClass::Str, "CurrencyCode", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfoRegionData, CurrencyCode), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_CurrencyCode_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_CurrencyCode_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountedPrice_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo | RegionData" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountedPrice = { UE4CodeGen_Private::EPropertyClass::Int, "DiscountedPrice", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfoRegionData, DiscountedPrice), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountedPrice_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountedPrice_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountAmount_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo | RegionData" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountAmount = { UE4CodeGen_Private::EPropertyClass::Int, "DiscountAmount", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfoRegionData, DiscountAmount), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountAmount_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountAmount_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountPercentage_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo | RegionData" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountPercentage = { UE4CodeGen_Private::EPropertyClass::Int, "DiscountPercentage", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfoRegionData, DiscountPercentage), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountPercentage_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountPercentage_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_Price_MetaData[] = {
		{ "Category", "AccelByte | Models | Item | ItemInfo | RegionData" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsItem.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_Price = { UE4CodeGen_Private::EPropertyClass::Int, "Price", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsItemInfoRegionData, Price), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_Price_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_Price_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountTotalNumPerAccount,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountTotalNum,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountExpireAt,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountPurchaseAt,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_TotalNumPerAccount,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_TotalNum,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_ExpireAt,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_PurchaseAt,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_CurrencyNamespace,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_CurrencyType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_CurrencyCode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountedPrice,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountAmount,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_DiscountPercentage,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::NewProp_Price,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsItemInfoRegionData",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsItemInfoRegionData),
		alignof(FAccelByteModelsItemInfoRegionData),
		Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsItemInfoRegionData"), sizeof(FAccelByteModelsItemInfoRegionData), Get_Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsItemInfoRegionData_CRC() { return 980787151U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
