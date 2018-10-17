// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AccelByteUe4Sdk/Public/Models/AccelByteModelsWallet.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAccelByteModelsWallet() {}
// Cross Module References
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo();
	UPackage* Z_Construct_UPackage__Script_AccelByteUe4Sdk();
// End Cross Module References
class UScriptStruct* FAccelByteModelsWalletInfo::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsWalletInfo"), sizeof(FAccelByteModelsWalletInfo), Get_Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsWalletInfo(FAccelByteModelsWalletInfo::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsWalletInfo"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsWalletInfo
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsWalletInfo()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsWalletInfo")),new UScriptStruct::TCppStructOps<FAccelByteModelsWalletInfo>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsWalletInfo;
	struct Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Status_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Status;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UpdatedAt_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_UpdatedAt;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CreatedAt_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_CreatedAt;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Balance_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Balance;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrencySymbol_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_CurrencySymbol;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrencyCode_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_CurrencyCode;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UserId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_UserId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Namespace_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Namespace;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Id_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Id;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsWallet.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsWalletInfo>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_Status_MetaData[] = {
		{ "Category", "AccelByte | Models | Wallet | WalletInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsWallet.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_Status = { UE4CodeGen_Private::EPropertyClass::Str, "Status", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsWalletInfo, Status), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_Status_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_Status_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_UpdatedAt_MetaData[] = {
		{ "Category", "AccelByte | Models | Wallet | WalletInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsWallet.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_UpdatedAt = { UE4CodeGen_Private::EPropertyClass::Str, "UpdatedAt", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsWalletInfo, UpdatedAt), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_UpdatedAt_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_UpdatedAt_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_CreatedAt_MetaData[] = {
		{ "Category", "AccelByte | Models | Wallet | WalletInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsWallet.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_CreatedAt = { UE4CodeGen_Private::EPropertyClass::Str, "CreatedAt", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsWalletInfo, CreatedAt), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_CreatedAt_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_CreatedAt_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_Balance_MetaData[] = {
		{ "Category", "AccelByte | Models | Wallet | WalletInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsWallet.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_Balance = { UE4CodeGen_Private::EPropertyClass::Int, "Balance", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsWalletInfo, Balance), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_Balance_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_Balance_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_CurrencySymbol_MetaData[] = {
		{ "Category", "AccelByte | Models | Wallet | WalletInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsWallet.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_CurrencySymbol = { UE4CodeGen_Private::EPropertyClass::Str, "CurrencySymbol", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsWalletInfo, CurrencySymbol), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_CurrencySymbol_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_CurrencySymbol_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_CurrencyCode_MetaData[] = {
		{ "Category", "AccelByte | Models | Wallet | WalletInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsWallet.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_CurrencyCode = { UE4CodeGen_Private::EPropertyClass::Str, "CurrencyCode", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsWalletInfo, CurrencyCode), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_CurrencyCode_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_CurrencyCode_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_UserId_MetaData[] = {
		{ "Category", "AccelByte | Models | Wallet | WalletInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsWallet.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_UserId = { UE4CodeGen_Private::EPropertyClass::Str, "UserId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsWalletInfo, UserId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_UserId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_UserId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_Namespace_MetaData[] = {
		{ "Category", "AccelByte | Models | Wallet | WalletInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsWallet.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_Namespace = { UE4CodeGen_Private::EPropertyClass::Str, "Namespace", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsWalletInfo, Namespace), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_Namespace_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_Namespace_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_Id_MetaData[] = {
		{ "Category", "AccelByte | Models | Wallet | WalletInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsWallet.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_Id = { UE4CodeGen_Private::EPropertyClass::Str, "Id", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsWalletInfo, Id), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_Id_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_Id_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_Status,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_UpdatedAt,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_CreatedAt,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_Balance,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_CurrencySymbol,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_CurrencyCode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_UserId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_Namespace,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::NewProp_Id,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsWalletInfo",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsWalletInfo),
		alignof(FAccelByteModelsWalletInfo),
		Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsWalletInfo"), sizeof(FAccelByteModelsWalletInfo), Get_Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsWalletInfo_CRC() { return 150703821U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
