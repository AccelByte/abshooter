// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AccelByteUe4Sdk/Public/Models/AccelByteModelsUserProfile.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAccelByteModelsUserProfile() {}
// Cross Module References
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest();
	UPackage* Z_Construct_UPackage__Script_AccelByteUe4Sdk();
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate();
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse();
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo();
// End Cross Module References
class UScriptStruct* FAccelByteModelsUserProfileRequest::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsUserProfileRequest"), sizeof(FAccelByteModelsUserProfileRequest), Get_Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsUserProfileRequest(FAccelByteModelsUserProfileRequest::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsUserProfileRequest"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsUserProfileRequest
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsUserProfileRequest()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsUserProfileRequest")),new UScriptStruct::TCppStructOps<FAccelByteModelsUserProfileRequest>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsUserProfileRequest;
	struct Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DateOfBirth_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_DateOfBirth;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Timezone_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Timezone;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Email_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Email;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AvatarLargeUrl_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AvatarLargeUrl;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AvatarUrl_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AvatarUrl;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AvatarSmallUrl_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AvatarSmallUrl;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Language_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Language;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Country_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Country;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LastName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_LastName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FirstName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FirstName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_DisplayName;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsUserProfileRequest>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_DateOfBirth_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileRequest" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_DateOfBirth = { UE4CodeGen_Private::EPropertyClass::Str, "DateOfBirth", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileRequest, DateOfBirth), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_DateOfBirth_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_DateOfBirth_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_Timezone_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileRequest" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_Timezone = { UE4CodeGen_Private::EPropertyClass::Str, "Timezone", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileRequest, Timezone), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_Timezone_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_Timezone_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_Email_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileRequest" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_Email = { UE4CodeGen_Private::EPropertyClass::Str, "Email", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileRequest, Email), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_Email_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_Email_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_AvatarLargeUrl_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileRequest" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_AvatarLargeUrl = { UE4CodeGen_Private::EPropertyClass::Str, "AvatarLargeUrl", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileRequest, AvatarLargeUrl), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_AvatarLargeUrl_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_AvatarLargeUrl_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_AvatarUrl_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileRequest" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_AvatarUrl = { UE4CodeGen_Private::EPropertyClass::Str, "AvatarUrl", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileRequest, AvatarUrl), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_AvatarUrl_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_AvatarUrl_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_AvatarSmallUrl_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileRequest" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_AvatarSmallUrl = { UE4CodeGen_Private::EPropertyClass::Str, "AvatarSmallUrl", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileRequest, AvatarSmallUrl), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_AvatarSmallUrl_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_AvatarSmallUrl_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_Language_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileRequest" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_Language = { UE4CodeGen_Private::EPropertyClass::Str, "Language", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileRequest, Language), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_Language_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_Language_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_Country_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileRequest" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_Country = { UE4CodeGen_Private::EPropertyClass::Str, "Country", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileRequest, Country), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_Country_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_Country_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_LastName_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileRequest" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_LastName = { UE4CodeGen_Private::EPropertyClass::Str, "LastName", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileRequest, LastName), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_LastName_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_LastName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_FirstName_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileRequest" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_FirstName = { UE4CodeGen_Private::EPropertyClass::Str, "FirstName", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileRequest, FirstName), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_FirstName_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_FirstName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_DisplayName_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileRequest" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_DisplayName = { UE4CodeGen_Private::EPropertyClass::Str, "DisplayName", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileRequest, DisplayName), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_DisplayName_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_DisplayName_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_DateOfBirth,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_Timezone,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_Email,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_AvatarLargeUrl,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_AvatarUrl,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_AvatarSmallUrl,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_Language,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_Country,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_LastName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_FirstName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::NewProp_DisplayName,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsUserProfileRequest",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsUserProfileRequest),
		alignof(FAccelByteModelsUserProfileRequest),
		Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsUserProfileRequest"), sizeof(FAccelByteModelsUserProfileRequest), Get_Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsUserProfileRequest_CRC() { return 219843873U; }
class UScriptStruct* FAccelByteModelsUserProfileInfoUpdate::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsUserProfileInfoUpdate"), sizeof(FAccelByteModelsUserProfileInfoUpdate), Get_Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate(FAccelByteModelsUserProfileInfoUpdate::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsUserProfileInfoUpdate"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsUserProfileInfoUpdate
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsUserProfileInfoUpdate()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsUserProfileInfoUpdate")),new UScriptStruct::TCppStructOps<FAccelByteModelsUserProfileInfoUpdate>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsUserProfileInfoUpdate;
	struct Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DateOfBirth_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_DateOfBirth;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Timezone_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Timezone;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Country_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Country;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Language_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Language;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Email_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Email;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AvatarLargeUrl_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AvatarLargeUrl;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AvatarUrl_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AvatarUrl;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AvatarSmallUrl_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AvatarSmallUrl;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LastName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_LastName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FirstName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FirstName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_DisplayName;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsUserProfileInfoUpdate>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_DateOfBirth_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfoUpdate" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_DateOfBirth = { UE4CodeGen_Private::EPropertyClass::Str, "DateOfBirth", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfoUpdate, DateOfBirth), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_DateOfBirth_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_DateOfBirth_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_Timezone_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfoUpdate" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_Timezone = { UE4CodeGen_Private::EPropertyClass::Str, "Timezone", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfoUpdate, Timezone), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_Timezone_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_Timezone_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_Country_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfoUpdate" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_Country = { UE4CodeGen_Private::EPropertyClass::Str, "Country", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfoUpdate, Country), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_Country_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_Country_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_Language_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfoUpdate" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_Language = { UE4CodeGen_Private::EPropertyClass::Str, "Language", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfoUpdate, Language), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_Language_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_Language_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_Email_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfoUpdate" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_Email = { UE4CodeGen_Private::EPropertyClass::Str, "Email", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfoUpdate, Email), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_Email_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_Email_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_AvatarLargeUrl_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfoUpdate" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_AvatarLargeUrl = { UE4CodeGen_Private::EPropertyClass::Str, "AvatarLargeUrl", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfoUpdate, AvatarLargeUrl), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_AvatarLargeUrl_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_AvatarLargeUrl_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_AvatarUrl_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfoUpdate" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_AvatarUrl = { UE4CodeGen_Private::EPropertyClass::Str, "AvatarUrl", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfoUpdate, AvatarUrl), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_AvatarUrl_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_AvatarUrl_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_AvatarSmallUrl_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfoUpdate" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_AvatarSmallUrl = { UE4CodeGen_Private::EPropertyClass::Str, "AvatarSmallUrl", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfoUpdate, AvatarSmallUrl), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_AvatarSmallUrl_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_AvatarSmallUrl_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_LastName_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfoUpdate" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_LastName = { UE4CodeGen_Private::EPropertyClass::Str, "LastName", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfoUpdate, LastName), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_LastName_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_LastName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_FirstName_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfoUpdate" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_FirstName = { UE4CodeGen_Private::EPropertyClass::Str, "FirstName", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfoUpdate, FirstName), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_FirstName_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_FirstName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_DisplayName_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfoUpdate" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_DisplayName = { UE4CodeGen_Private::EPropertyClass::Str, "DisplayName", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfoUpdate, DisplayName), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_DisplayName_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_DisplayName_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_DateOfBirth,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_Timezone,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_Country,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_Language,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_Email,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_AvatarLargeUrl,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_AvatarUrl,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_AvatarSmallUrl,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_LastName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_FirstName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::NewProp_DisplayName,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsUserProfileInfoUpdate",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		sizeof(FAccelByteModelsUserProfileInfoUpdate),
		alignof(FAccelByteModelsUserProfileInfoUpdate),
		Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsUserProfileInfoUpdate"), sizeof(FAccelByteModelsUserProfileInfoUpdate), Get_Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfoUpdate_CRC() { return 1282236818U; }
class UScriptStruct* FAccelByteModelsUserCreateResponse::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsUserCreateResponse"), sizeof(FAccelByteModelsUserCreateResponse), Get_Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsUserCreateResponse(FAccelByteModelsUserCreateResponse::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsUserCreateResponse"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsUserCreateResponse
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsUserCreateResponse()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsUserCreateResponse")),new UScriptStruct::TCppStructOps<FAccelByteModelsUserCreateResponse>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsUserCreateResponse;
	struct Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
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
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UserId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_UserId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Namespace_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Namespace;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsUserCreateResponse>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_LoginId_MetaData[] = {
		{ "Category", "AccelByte | Models | UserCreateResponse" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_LoginId = { UE4CodeGen_Private::EPropertyClass::Str, "LoginId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserCreateResponse, LoginId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_LoginId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_LoginId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_DisplayName_MetaData[] = {
		{ "Category", "AccelByte | Models | UserCreateResponse" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_DisplayName = { UE4CodeGen_Private::EPropertyClass::Str, "DisplayName", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserCreateResponse, DisplayName), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_DisplayName_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_DisplayName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_AuthType_MetaData[] = {
		{ "Category", "AccelByte | Models | UserCreateResponse" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_AuthType = { UE4CodeGen_Private::EPropertyClass::Str, "AuthType", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserCreateResponse, AuthType), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_AuthType_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_AuthType_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_UserId_MetaData[] = {
		{ "Category", "AccelByte | Models | UserCreateResponse" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_UserId = { UE4CodeGen_Private::EPropertyClass::Str, "UserId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserCreateResponse, UserId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_UserId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_UserId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_Namespace_MetaData[] = {
		{ "Category", "AccelByte | Models | UserCreateResponse" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_Namespace = { UE4CodeGen_Private::EPropertyClass::Str, "Namespace", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserCreateResponse, Namespace), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_Namespace_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_Namespace_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_LoginId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_DisplayName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_AuthType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_UserId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::NewProp_Namespace,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsUserCreateResponse",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsUserCreateResponse),
		alignof(FAccelByteModelsUserCreateResponse),
		Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsUserCreateResponse"), sizeof(FAccelByteModelsUserCreateResponse), Get_Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsUserCreateResponse_CRC() { return 836041U; }
class UScriptStruct* FAccelByteModelsUserProfileInfo::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ACCELBYTEUE4SDK_API uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo, Z_Construct_UPackage__Script_AccelByteUe4Sdk(), TEXT("AccelByteModelsUserProfileInfo"), sizeof(FAccelByteModelsUserProfileInfo), Get_Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAccelByteModelsUserProfileInfo(FAccelByteModelsUserProfileInfo::StaticStruct, TEXT("/Script/AccelByteUe4Sdk"), TEXT("AccelByteModelsUserProfileInfo"), false, nullptr, nullptr);
static struct FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsUserProfileInfo
{
	FScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsUserProfileInfo()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AccelByteModelsUserProfileInfo")),new UScriptStruct::TCppStructOps<FAccelByteModelsUserProfileInfo>);
	}
} ScriptStruct_AccelByteUe4Sdk_StaticRegisterNativesFAccelByteModelsUserProfileInfo;
	struct Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DateOfBirth_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_DateOfBirth;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Timezone_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Timezone;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Language_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Language;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Status_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Status;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Email_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Email;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AvatarLargeUrl_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AvatarLargeUrl;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AvatarUrl_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AvatarUrl;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AvatarSmallUrl_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AvatarSmallUrl;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Country_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Country;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LastName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_LastName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FirstName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FirstName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_DisplayName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Namespace_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Namespace;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UserId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_UserId;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAccelByteModelsUserProfileInfo>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_DateOfBirth_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_DateOfBirth = { UE4CodeGen_Private::EPropertyClass::Str, "DateOfBirth", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfo, DateOfBirth), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_DateOfBirth_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_DateOfBirth_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Timezone_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Timezone = { UE4CodeGen_Private::EPropertyClass::Str, "Timezone", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfo, Timezone), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Timezone_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Timezone_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Language_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Language = { UE4CodeGen_Private::EPropertyClass::Str, "Language", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfo, Language), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Language_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Language_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Status_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Status = { UE4CodeGen_Private::EPropertyClass::Str, "Status", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfo, Status), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Status_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Status_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Email_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Email = { UE4CodeGen_Private::EPropertyClass::Str, "Email", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfo, Email), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Email_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Email_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_AvatarLargeUrl_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_AvatarLargeUrl = { UE4CodeGen_Private::EPropertyClass::Str, "AvatarLargeUrl", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfo, AvatarLargeUrl), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_AvatarLargeUrl_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_AvatarLargeUrl_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_AvatarUrl_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_AvatarUrl = { UE4CodeGen_Private::EPropertyClass::Str, "AvatarUrl", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfo, AvatarUrl), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_AvatarUrl_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_AvatarUrl_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_AvatarSmallUrl_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_AvatarSmallUrl = { UE4CodeGen_Private::EPropertyClass::Str, "AvatarSmallUrl", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfo, AvatarSmallUrl), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_AvatarSmallUrl_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_AvatarSmallUrl_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Country_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Country = { UE4CodeGen_Private::EPropertyClass::Str, "Country", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfo, Country), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Country_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Country_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_LastName_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_LastName = { UE4CodeGen_Private::EPropertyClass::Str, "LastName", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfo, LastName), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_LastName_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_LastName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_FirstName_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_FirstName = { UE4CodeGen_Private::EPropertyClass::Str, "FirstName", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfo, FirstName), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_FirstName_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_FirstName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_DisplayName_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_DisplayName = { UE4CodeGen_Private::EPropertyClass::Str, "DisplayName", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfo, DisplayName), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_DisplayName_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_DisplayName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Namespace_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Namespace = { UE4CodeGen_Private::EPropertyClass::Str, "Namespace", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfo, Namespace), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Namespace_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Namespace_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_UserId_MetaData[] = {
		{ "Category", "AccelByte | Models | UserProfile | UserProfileInfo" },
		{ "ModuleRelativePath", "Public/Models/AccelByteModelsUserProfile.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_UserId = { UE4CodeGen_Private::EPropertyClass::Str, "UserId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FAccelByteModelsUserProfileInfo, UserId), METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_UserId_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_UserId_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_DateOfBirth,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Timezone,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Language,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Status,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Email,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_AvatarLargeUrl,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_AvatarUrl,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_AvatarSmallUrl,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Country,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_LastName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_FirstName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_DisplayName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_Namespace,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::NewProp_UserId,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
		nullptr,
		&NewStructOps,
		"AccelByteModelsUserProfileInfo",
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		sizeof(FAccelByteModelsUserProfileInfo),
		alignof(FAccelByteModelsUserProfileInfo),
		Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::PropPointers),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_AccelByteUe4Sdk();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AccelByteModelsUserProfileInfo"), sizeof(FAccelByteModelsUserProfileInfo), Get_Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAccelByteModelsUserProfileInfo_CRC() { return 117148351U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
