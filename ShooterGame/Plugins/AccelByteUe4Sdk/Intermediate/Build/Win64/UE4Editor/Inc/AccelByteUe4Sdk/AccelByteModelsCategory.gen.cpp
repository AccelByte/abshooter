// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AccelByteUe4Sdk/Public/Models/AccelByteModelsCategory.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAccelByteModelsCategory() {}
// Cross Module References
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo();
	UPackage* Z_Construct_UPackage__Script_AccelByteUe4Sdk();
// End Cross Module References
class UScriptStruct* FAccelByteModelsFullCategoryInfo::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsFullCategoryInfo"), sizeof(FAccelByteModelsFullCategoryInfo), Get_Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsFullCategoryInfo(FAccelByteModelsFullCategoryInfo::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsFullCategoryInfo"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsFullCategoryInfo
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsFullCategoryInfo()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsFullCategoryInfo")),new UScriptStruct::TCppStructOps<FAccelByteModelsFullCategoryInfo>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsFullCategoryInfo;
	struct Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Root_MetaData[];
#endif
		static void NewProp_Root_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_Root;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UpdatedAt_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_UpdatedAt;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CreatedAt_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_CreatedAt;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_DisplayName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CategoryPath_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_CategoryPath;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ParentCategoryPath_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ParentCategoryPath;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Namespace_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Namespace;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsCategory.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsFullCategoryInfo>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_Root_MetaData[] = {
		{ "Category", "AccelByte | Models | Category | FullCategoryInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsCategory.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_Root_SetBit(void* Obj)
	{
		((FAccelByteModelsFullCategoryInfo*)Obj)->Root = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_Root = { UE4CodeGen_Private::EPropertyClass::Bool, "Root", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(FAccelByteModelsFullCategoryInfo), &Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_Root_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_Root_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_Root_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_UpdatedAt_MetaData[] = {
		{ "Category", "AccelByte | Models | Category | FullCategoryInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsCategory.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_UpdatedAt = { UE4CodeGen_Private::EPropertyClass::Str, "UpdatedAt", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsFullCategoryInfo, UpdatedAt), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_UpdatedAt_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_UpdatedAt_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_CreatedAt_MetaData[] = {
		{ "Category", "AccelByte | Models | Category | FullCategoryInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsCategory.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_CreatedAt = { UE4CodeGen_Private::EPropertyClass::Str, "CreatedAt", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsFullCategoryInfo, CreatedAt), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_CreatedAt_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_CreatedAt_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_DisplayName_MetaData[] = {
		{ "Category", "AccelByte | Models | Category | FullCategoryInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsCategory.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_DisplayName = { UE4CodeGen_Private::EPropertyClass::Str, "DisplayName", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsFullCategoryInfo, DisplayName), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_DisplayName_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_DisplayName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_CategoryPath_MetaData[] = {
		{ "Category", "AccelByte | Models | Category | FullCategoryInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsCategory.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_CategoryPath = { UE4CodeGen_Private::EPropertyClass::Str, "CategoryPath", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsFullCategoryInfo, CategoryPath), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_CategoryPath_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_CategoryPath_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_ParentCategoryPath_MetaData[] = {
		{ "Category", "AccelByte | Models | Category | FullCategoryInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsCategory.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_ParentCategoryPath = { UE4CodeGen_Private::EPropertyClass::Str, "ParentCategoryPath", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsFullCategoryInfo, ParentCategoryPath), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_ParentCategoryPath_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_ParentCategoryPath_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_Namespace_MetaData[] = {
		{ "Category", "AccelByte | Models | Category | FullCategoryInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsCategory.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_Namespace = { UE4CodeGen_Private::EPropertyClass::Str, "Namespace", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsFullCategoryInfo, Namespace), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_Namespace_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_Namespace_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_Root,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_UpdatedAt,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_CreatedAt,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_DisplayName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_CategoryPath,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_ParentCategoryPath,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::NewProp_Namespace,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsFullCategoryInfo",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		sizeof(FAccelByteModelsFullCategoryInfo),
		alignof(FAccelByteModelsFullCategoryInfo),
		Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsFullCategoryInfo"), sizeof(FAccelByteModelsFullCategoryInfo), Get_Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsFullCategoryInfo_CRC() { return 2061534357U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
