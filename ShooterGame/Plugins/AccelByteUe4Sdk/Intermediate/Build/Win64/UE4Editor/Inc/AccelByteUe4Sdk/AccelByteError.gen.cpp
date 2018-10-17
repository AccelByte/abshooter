// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AccelByteUe4Sdk/Public/Core/AccelByteError.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAccelByteError() {}
// Cross Module References
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity();
	UPackage* Z_Construct_UPackage__Script_AccelByteUe4Sdk();
// End Cross Module References
class UScriptStruct* FAccelByteModelsErrorEntity::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsErrorEntity"), sizeof(FAccelByteModelsErrorEntity), Get_Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsErrorEntity(FAccelByteModelsErrorEntity::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsErrorEntity"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsErrorEntity
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsErrorEntity()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsErrorEntity")),new UScriptStruct::TCppStructOps<FAccelByteModelsErrorEntity>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsErrorEntity;
	struct Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ErrorMessage_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ErrorMessage;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ErrorCode_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ErrorCode;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NumericErrorCode_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_NumericErrorCode;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Core/AccelByteError.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsErrorEntity>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::NewProp_ErrorMessage_MetaData[] = {
		{ "Category", "AccelByte | Models | Error" },
		{ "ModuleRelativePath", "Public/Core/AccelByteError.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::NewProp_ErrorMessage = { UE4CodeGen_Private::EPropertyClass::Str, "ErrorMessage", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsErrorEntity, ErrorMessage), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::NewProp_ErrorMessage_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::NewProp_ErrorMessage_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::NewProp_ErrorCode_MetaData[] = {
		{ "Category", "AccelByte | Models | Error" },
		{ "ModuleRelativePath", "Public/Core/AccelByteError.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::NewProp_ErrorCode = { UE4CodeGen_Private::EPropertyClass::Str, "ErrorCode", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsErrorEntity, ErrorCode), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::NewProp_ErrorCode_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::NewProp_ErrorCode_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::NewProp_NumericErrorCode_MetaData[] = {
		{ "Category", "AccelByte | Models | Error" },
		{ "ModuleRelativePath", "Public/Core/AccelByteError.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::NewProp_NumericErrorCode = { UE4CodeGen_Private::EPropertyClass::Int, "NumericErrorCode", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsErrorEntity, NumericErrorCode), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::NewProp_NumericErrorCode_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::NewProp_NumericErrorCode_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::NewProp_ErrorMessage,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::NewProp_ErrorCode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::NewProp_NumericErrorCode,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsErrorEntity",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		sizeof(FAccelByteModelsErrorEntity),
		alignof(FAccelByteModelsErrorEntity),
		Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsErrorEntity"), sizeof(FAccelByteModelsErrorEntity), Get_Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsErrorEntity_CRC() { return 2434185758U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
