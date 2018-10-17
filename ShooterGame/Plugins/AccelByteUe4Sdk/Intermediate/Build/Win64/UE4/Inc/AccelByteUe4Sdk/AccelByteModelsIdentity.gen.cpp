// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AccelByteUe4Sdk/Public/Models/AccelByteModelsIdentity.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAccelByteModelsIdentity() {}
// Cross Module References
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform();
	UPackage* Z_Construct_UPackage__Script_AccelByteUe4Sdk();
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest();
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest();
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken();
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan();
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FDateTime();
// End Cross Module References
class UScriptStruct* FAccelByteModelsLinkedPlatform::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsLinkedPlatform"), sizeof(FAccelByteModelsLinkedPlatform), Get_Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsLinkedPlatform(FAccelByteModelsLinkedPlatform::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsLinkedPlatform"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsLinkedPlatform
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsLinkedPlatform()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsLinkedPlatform")),new UScriptStruct::TCppStructOps<FAccelByteModelsLinkedPlatform>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsLinkedPlatform;
	struct Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UserId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_UserId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Namespace_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Namespace;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PlatformUserId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_PlatformUserId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PlatformId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_PlatformId;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsLinkedPlatform>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::NewProp_UserId_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | LinkedPlatform" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::NewProp_UserId = { UE4CodeGen_Private::EPropertyClass::Str, "UserId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsLinkedPlatform, UserId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::NewProp_UserId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::NewProp_UserId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::NewProp_Namespace_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | LinkedPlatform" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::NewProp_Namespace = { UE4CodeGen_Private::EPropertyClass::Str, "Namespace", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsLinkedPlatform, Namespace), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::NewProp_Namespace_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::NewProp_Namespace_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::NewProp_PlatformUserId_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | LinkedPlatform" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::NewProp_PlatformUserId = { UE4CodeGen_Private::EPropertyClass::Str, "PlatformUserId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsLinkedPlatform, PlatformUserId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::NewProp_PlatformUserId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::NewProp_PlatformUserId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::NewProp_PlatformId_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | LinkedPlatform" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::NewProp_PlatformId = { UE4CodeGen_Private::EPropertyClass::Str, "PlatformId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsLinkedPlatform, PlatformId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::NewProp_PlatformId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::NewProp_PlatformId_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::NewProp_UserId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::NewProp_Namespace,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::NewProp_PlatformUserId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::NewProp_PlatformId,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsLinkedPlatform",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsLinkedPlatform),
		alignof(FAccelByteModelsLinkedPlatform),
		Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsLinkedPlatform"), sizeof(FAccelByteModelsLinkedPlatform), Get_Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsLinkedPlatform_CRC() { return 2546501237U; }
class UScriptStruct* FAccelByteModelsResetPasswordRequest::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsResetPasswordRequest"), sizeof(FAccelByteModelsResetPasswordRequest), Get_Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsResetPasswordRequest(FAccelByteModelsResetPasswordRequest::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsResetPasswordRequest"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsResetPasswordRequest
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsResetPasswordRequest()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsResetPasswordRequest")),new UScriptStruct::TCppStructOps<FAccelByteModelsResetPasswordRequest>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsResetPasswordRequest;
	struct Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NewPassword_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_NewPassword;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LoginId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_LoginId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Code_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Code;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsResetPasswordRequest>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::NewProp_NewPassword_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | ResetPasswordRequest" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::NewProp_NewPassword = { UE4CodeGen_Private::EPropertyClass::Str, "NewPassword", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsResetPasswordRequest, NewPassword), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::NewProp_NewPassword_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::NewProp_NewPassword_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::NewProp_LoginId_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | ResetPasswordRequest" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::NewProp_LoginId = { UE4CodeGen_Private::EPropertyClass::Str, "LoginId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsResetPasswordRequest, LoginId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::NewProp_LoginId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::NewProp_LoginId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::NewProp_Code_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | ResetPasswordRequest" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::NewProp_Code = { UE4CodeGen_Private::EPropertyClass::Str, "Code", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsResetPasswordRequest, Code), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::NewProp_Code_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::NewProp_Code_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::NewProp_NewPassword,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::NewProp_LoginId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::NewProp_Code,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsResetPasswordRequest",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsResetPasswordRequest),
		alignof(FAccelByteModelsResetPasswordRequest),
		Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsResetPasswordRequest"), sizeof(FAccelByteModelsResetPasswordRequest), Get_Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsResetPasswordRequest_CRC() { return 1835052927U; }
class UScriptStruct* FAccelByteModelsUserCreateRequest::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsUserCreateRequest"), sizeof(FAccelByteModelsUserCreateRequest), Get_Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsUserCreateRequest(FAccelByteModelsUserCreateRequest::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsUserCreateRequest"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsUserCreateRequest
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsUserCreateRequest()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsUserCreateRequest")),new UScriptStruct::TCppStructOps<FAccelByteModelsUserCreateRequest>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsUserCreateRequest;
	struct Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Password_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Password;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LoginId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_LoginId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_DisplayName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AuthType_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AuthType;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsUserCreateRequest>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::NewProp_Password_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | UserCreateRequest" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::NewProp_Password = { UE4CodeGen_Private::EPropertyClass::Str, "Password", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserCreateRequest, Password), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::NewProp_Password_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::NewProp_Password_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::NewProp_LoginId_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | UserCreateRequest" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::NewProp_LoginId = { UE4CodeGen_Private::EPropertyClass::Str, "LoginId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserCreateRequest, LoginId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::NewProp_LoginId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::NewProp_LoginId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::NewProp_DisplayName_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | UserCreateRequest" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::NewProp_DisplayName = { UE4CodeGen_Private::EPropertyClass::Str, "DisplayName", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserCreateRequest, DisplayName), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::NewProp_DisplayName_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::NewProp_DisplayName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::NewProp_AuthType_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | UserCreateRequest" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::NewProp_AuthType = { UE4CodeGen_Private::EPropertyClass::Str, "AuthType", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserCreateRequest, AuthType), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::NewProp_AuthType_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::NewProp_AuthType_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::NewProp_Password,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::NewProp_LoginId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::NewProp_DisplayName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::NewProp_AuthType,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsUserCreateRequest",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsUserCreateRequest),
		alignof(FAccelByteModelsUserCreateRequest),
		Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsUserCreateRequest"), sizeof(FAccelByteModelsUserCreateRequest), Get_Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsUserCreateRequest_CRC() { return 2387539381U; }
class UScriptStruct* FAccelByteModelsOAuthToken::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsOAuthToken"), sizeof(FAccelByteModelsOAuthToken), Get_Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsOAuthToken(FAccelByteModelsOAuthToken::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsOAuthToken"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOAuthToken
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOAuthToken()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsOAuthToken")),new UScriptStruct::TCppStructOps<FAccelByteModelsOAuthToken>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOAuthToken;
	struct Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Namespace_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Namespace;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Display_name_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Display_name;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_User_id_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_User_id;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Bans_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Bans;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Bans_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Roles_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Roles;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Roles_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Permissions_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Permissions;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Permissions_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Expires_in_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Expires_in;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Token_type_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Token_type;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Refresh_token_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Refresh_token;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Access_token_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Access_token;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsOAuthToken>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Namespace_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | OAuthToken" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Namespace = { UE4CodeGen_Private::EPropertyClass::Str, "Namespace", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOAuthToken, Namespace), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Namespace_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Namespace_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Display_name_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | OAuthToken" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Display_name = { UE4CodeGen_Private::EPropertyClass::Str, "Display_name", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOAuthToken, Display_name), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Display_name_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Display_name_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_User_id_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | OAuthToken" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_User_id = { UE4CodeGen_Private::EPropertyClass::Str, "User_id", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOAuthToken, User_id), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_User_id_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_User_id_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Bans_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | OAuthToken" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Bans = { UE4CodeGen_Private::EPropertyClass::Array, "Bans", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOAuthToken, Bans), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Bans_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Bans_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Bans_Inner = { UE4CodeGen_Private::EPropertyClass::Struct, "Bans", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0000000000000000, 1, nullptr, 0, Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Roles_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | OAuthToken" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Roles = { UE4CodeGen_Private::EPropertyClass::Array, "Roles", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOAuthToken, Roles), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Roles_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Roles_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Roles_Inner = { UE4CodeGen_Private::EPropertyClass::Str, "Roles", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0000000000000000, 1, nullptr, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Permissions_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | OAuthToken" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Permissions = { UE4CodeGen_Private::EPropertyClass::Array, "Permissions", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOAuthToken, Permissions), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Permissions_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Permissions_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Permissions_Inner = { UE4CodeGen_Private::EPropertyClass::Struct, "Permissions", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0000000000000000, 1, nullptr, 0, Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Expires_in_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | OAuthToken" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Expires_in = { UE4CodeGen_Private::EPropertyClass::Float, "Expires_in", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOAuthToken, Expires_in), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Expires_in_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Expires_in_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Token_type_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | OAuthToken" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Token_type = { UE4CodeGen_Private::EPropertyClass::Str, "Token_type", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOAuthToken, Token_type), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Token_type_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Token_type_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Refresh_token_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | OAuthToken" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Refresh_token = { UE4CodeGen_Private::EPropertyClass::Str, "Refresh_token", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOAuthToken, Refresh_token), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Refresh_token_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Refresh_token_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Access_token_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | OAuthToken" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Access_token = { UE4CodeGen_Private::EPropertyClass::Str, "Access_token", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOAuthToken, Access_token), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Access_token_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Access_token_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Namespace,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Display_name,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_User_id,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Bans,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Bans_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Roles,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Roles_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Permissions,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Permissions_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Expires_in,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Token_type,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Refresh_token,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::NewProp_Access_token,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsOAuthToken",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsOAuthToken),
		alignof(FAccelByteModelsOAuthToken),
		Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsOAuthToken"), sizeof(FAccelByteModelsOAuthToken), Get_Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken_CRC() { return 4147031491U; }
class UScriptStruct* FAccelByteModelsOAuthTokenBan::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsOAuthTokenBan"), sizeof(FAccelByteModelsOAuthTokenBan), Get_Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsOAuthTokenBan(FAccelByteModelsOAuthTokenBan::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsOAuthTokenBan"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOAuthTokenBan
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOAuthTokenBan()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsOAuthTokenBan")),new UScriptStruct::TCppStructOps<FAccelByteModelsOAuthTokenBan>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOAuthTokenBan;
	struct Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EndDate_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_EndDate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Ban_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Ban;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsOAuthTokenBan>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_Statics::NewProp_EndDate_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | OAuthToken | Ban" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_Statics::NewProp_EndDate = { UE4CodeGen_Private::EPropertyClass::Struct, "EndDate", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOAuthTokenBan, EndDate), Z_Construct_UScriptStruct_FDateTime, METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_Statics::NewProp_EndDate_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_Statics::NewProp_EndDate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_Statics::NewProp_Ban_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | OAuthToken | Ban" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_Statics::NewProp_Ban = { UE4CodeGen_Private::EPropertyClass::Str, "Ban", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOAuthTokenBan, Ban), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_Statics::NewProp_Ban_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_Statics::NewProp_Ban_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_Statics::NewProp_EndDate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_Statics::NewProp_Ban,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsOAuthTokenBan",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsOAuthTokenBan),
		alignof(FAccelByteModelsOAuthTokenBan),
		Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsOAuthTokenBan"), sizeof(FAccelByteModelsOAuthTokenBan), Get_Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenBan_CRC() { return 3352505460U; }
class UScriptStruct* FAccelByteModelsOAuthTokenPermission::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsOAuthTokenPermission"), sizeof(FAccelByteModelsOAuthTokenPermission), Get_Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsOAuthTokenPermission(FAccelByteModelsOAuthTokenPermission::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsOAuthTokenPermission"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOAuthTokenPermission
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOAuthTokenPermission()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsOAuthTokenPermission")),new UScriptStruct::TCppStructOps<FAccelByteModelsOAuthTokenPermission>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsOAuthTokenPermission;
	struct Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Action_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Action;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Resource_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Resource;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsOAuthTokenPermission>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_Statics::NewProp_Action_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | OAuthToken | Permission" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_Statics::NewProp_Action = { UE4CodeGen_Private::EPropertyClass::Int, "Action", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOAuthTokenPermission, Action), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_Statics::NewProp_Action_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_Statics::NewProp_Action_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_Statics::NewProp_Resource_MetaData[] = {
		{ "Category", "AccelByte | Models | Identity | OAuthToken | Permission" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_Statics::NewProp_Resource = { UE4CodeGen_Private::EPropertyClass::Str, "Resource", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsOAuthTokenPermission, Resource), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_Statics::NewProp_Resource_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_Statics::NewProp_Resource_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_Statics::NewProp_Action,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_Statics::NewProp_Resource,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsOAuthTokenPermission",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsOAuthTokenPermission),
		alignof(FAccelByteModelsOAuthTokenPermission),
		Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsOAuthTokenPermission"), sizeof(FAccelByteModelsOAuthTokenPermission), Get_Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsOAuthTokenPermission_CRC() { return 1969853397U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
