// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AccelByteUe4Sdk/Public/Blueprints/AccelByteBlueprintsIdentity.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAccelByteBlueprintsIdentity() {}
// Cross Module References
	ACCELBYTEUE4SDK_API UFunction* Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess__DelegateSignature();
	ACCELBYTEUE4SDK_API UClass* Z_Construct_UClass_UAccelByteBlueprintsIdentity();
	ACCELBYTEUE4SDK_API UScriptStruct* Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken();
	ACCELBYTEUE4SDK_API UFunction* Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrantSuccess__DelegateSignature();
	ACCELBYTEUE4SDK_API UFunction* Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_BlueprintError__DelegateSignature();
	ACCELBYTEUE4SDK_API UClass* Z_Construct_UClass_UAccelByteBlueprintsIdentity_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_AccelByteUe4Sdk();
	ACCELBYTEUE4SDK_API UFunction* Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant();
	ACCELBYTEUE4SDK_API UFunction* Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess__DelegateSignature_Statics
	{
		struct AccelByteBlueprintsIdentity_eventLoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess_Parms
		{
			FAccelByteModelsOAuthToken Result;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Result_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Result;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess__DelegateSignature_Statics::NewProp_Result_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess__DelegateSignature_Statics::NewProp_Result = { UE4CodeGen_Private::EPropertyClass::Struct, "Result", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000008000182, 1, nullptr, STRUCT_OFFSET(AccelByteBlueprintsIdentity_eventLoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess_Parms, Result), Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken, METADATA_PARAMS(Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess__DelegateSignature_Statics::NewProp_Result_MetaData, ARRAY_COUNT(Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess__DelegateSignature_Statics::NewProp_Result_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess__DelegateSignature_Statics::NewProp_Result,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Blueprints/AccelByteBlueprintsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAccelByteBlueprintsIdentity, "LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess__DelegateSignature", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x00520000, sizeof(AccelByteBlueprintsIdentity_eventLoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess_Parms), Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess__DelegateSignature_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess__DelegateSignature_Statics::PropPointers), 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess__DelegateSignature_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrantSuccess__DelegateSignature_Statics
	{
		struct AccelByteBlueprintsIdentity_eventGetAccessTokenWithDeviceGrantSuccess_Parms
		{
			FAccelByteModelsOAuthToken Result;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Result_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Result;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrantSuccess__DelegateSignature_Statics::NewProp_Result_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrantSuccess__DelegateSignature_Statics::NewProp_Result = { UE4CodeGen_Private::EPropertyClass::Struct, "Result", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000008000182, 1, nullptr, STRUCT_OFFSET(AccelByteBlueprintsIdentity_eventGetAccessTokenWithDeviceGrantSuccess_Parms, Result), Z_Construct_UScriptStruct_FAccelByteModelsOAuthToken, METADATA_PARAMS(Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrantSuccess__DelegateSignature_Statics::NewProp_Result_MetaData, ARRAY_COUNT(Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrantSuccess__DelegateSignature_Statics::NewProp_Result_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrantSuccess__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrantSuccess__DelegateSignature_Statics::NewProp_Result,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrantSuccess__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Blueprints/AccelByteBlueprintsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrantSuccess__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAccelByteBlueprintsIdentity, "GetAccessTokenWithDeviceGrantSuccess__DelegateSignature", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x00520000, sizeof(AccelByteBlueprintsIdentity_eventGetAccessTokenWithDeviceGrantSuccess_Parms), Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrantSuccess__DelegateSignature_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrantSuccess__DelegateSignature_Statics::PropPointers), 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrantSuccess__DelegateSignature_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrantSuccess__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrantSuccess__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrantSuccess__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_BlueprintError__DelegateSignature_Statics
	{
		struct AccelByteBlueprintsIdentity_eventBlueprintError_Parms
		{
			int32 ErrorCode;
			FString ErrorMessage;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ErrorMessage;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ErrorCode;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_BlueprintError__DelegateSignature_Statics::NewProp_ErrorMessage = { UE4CodeGen_Private::EPropertyClass::Str, "ErrorMessage", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(AccelByteBlueprintsIdentity_eventBlueprintError_Parms, ErrorMessage), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_BlueprintError__DelegateSignature_Statics::NewProp_ErrorCode = { UE4CodeGen_Private::EPropertyClass::Int, "ErrorCode", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(AccelByteBlueprintsIdentity_eventBlueprintError_Parms, ErrorCode), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_BlueprintError__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_BlueprintError__DelegateSignature_Statics::NewProp_ErrorMessage,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_BlueprintError__DelegateSignature_Statics::NewProp_ErrorCode,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_BlueprintError__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Blueprints/AccelByteBlueprintsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_BlueprintError__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAccelByteBlueprintsIdentity, "BlueprintError__DelegateSignature", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x00120000, sizeof(AccelByteBlueprintsIdentity_eventBlueprintError_Parms), Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_BlueprintError__DelegateSignature_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_BlueprintError__DelegateSignature_Statics::PropPointers), 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_BlueprintError__DelegateSignature_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_BlueprintError__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_BlueprintError__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_BlueprintError__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	void UAccelByteBlueprintsIdentity::StaticRegisterNativesUAccelByteBlueprintsIdentity()
	{
		UClass* Class = UAccelByteBlueprintsIdentity::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetAccessTokenWithDeviceGrant", &UAccelByteBlueprintsIdentity::execGetAccessTokenWithDeviceGrant },
			{ "GetUserAccessTokenWithPasswordGrant", &UAccelByteBlueprintsIdentity::execGetUserAccessTokenWithPasswordGrant },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant_Statics
	{
		struct AccelByteBlueprintsIdentity_eventGetAccessTokenWithDeviceGrant_Parms
		{
			FString ServerBaseUrl;
			FString ClientId;
			FString ClientSecret;
			FString Namespace;
			FScriptDelegate OnSuccess;
			FScriptDelegate OnError;
		};
		static const UE4CodeGen_Private::FDelegatePropertyParams NewProp_OnError;
		static const UE4CodeGen_Private::FDelegatePropertyParams NewProp_OnSuccess;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Namespace;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ClientSecret;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ClientId;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ServerBaseUrl;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant_Statics::NewProp_OnError = { UE4CodeGen_Private::EPropertyClass::Delegate, "OnError", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(AccelByteBlueprintsIdentity_eventGetAccessTokenWithDeviceGrant_Parms, OnError), Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_BlueprintError__DelegateSignature, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant_Statics::NewProp_OnSuccess = { UE4CodeGen_Private::EPropertyClass::Delegate, "OnSuccess", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(AccelByteBlueprintsIdentity_eventGetAccessTokenWithDeviceGrant_Parms, OnSuccess), Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrantSuccess__DelegateSignature, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant_Statics::NewProp_Namespace = { UE4CodeGen_Private::EPropertyClass::Str, "Namespace", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(AccelByteBlueprintsIdentity_eventGetAccessTokenWithDeviceGrant_Parms, Namespace), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant_Statics::NewProp_ClientSecret = { UE4CodeGen_Private::EPropertyClass::Str, "ClientSecret", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(AccelByteBlueprintsIdentity_eventGetAccessTokenWithDeviceGrant_Parms, ClientSecret), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant_Statics::NewProp_ClientId = { UE4CodeGen_Private::EPropertyClass::Str, "ClientId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(AccelByteBlueprintsIdentity_eventGetAccessTokenWithDeviceGrant_Parms, ClientId), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant_Statics::NewProp_ServerBaseUrl = { UE4CodeGen_Private::EPropertyClass::Str, "ServerBaseUrl", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(AccelByteBlueprintsIdentity_eventGetAccessTokenWithDeviceGrant_Parms, ServerBaseUrl), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant_Statics::NewProp_OnError,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant_Statics::NewProp_OnSuccess,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant_Statics::NewProp_Namespace,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant_Statics::NewProp_ClientSecret,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant_Statics::NewProp_ClientId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant_Statics::NewProp_ServerBaseUrl,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant_Statics::Function_MetaDataParams[] = {
		{ "Category", "AccelByte | Services | Identity" },
		{ "ModuleRelativePath", "Public/Blueprints/AccelByteBlueprintsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAccelByteBlueprintsIdentity, "GetAccessTokenWithDeviceGrant", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04022401, sizeof(AccelByteBlueprintsIdentity_eventGetAccessTokenWithDeviceGrant_Parms), Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant_Statics::PropPointers), 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics
	{
		struct AccelByteBlueprintsIdentity_eventGetUserAccessTokenWithPasswordGrant_Parms
		{
			FString ServerBaseUrl;
			FString ClientId;
			FString ClientSecret;
			FString Namespace;
			FString LoginId;
			FString Password;
			FScriptDelegate OnSuccess;
			FScriptDelegate OnError;
		};
		static const UE4CodeGen_Private::FDelegatePropertyParams NewProp_OnError;
		static const UE4CodeGen_Private::FDelegatePropertyParams NewProp_OnSuccess;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Password;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_LoginId;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Namespace;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ClientSecret;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ClientId;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ServerBaseUrl;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::NewProp_OnError = { UE4CodeGen_Private::EPropertyClass::Delegate, "OnError", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(AccelByteBlueprintsIdentity_eventGetUserAccessTokenWithPasswordGrant_Parms, OnError), Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_BlueprintError__DelegateSignature, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::NewProp_OnSuccess = { UE4CodeGen_Private::EPropertyClass::Delegate, "OnSuccess", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(AccelByteBlueprintsIdentity_eventGetUserAccessTokenWithPasswordGrant_Parms, OnSuccess), Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess__DelegateSignature, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::NewProp_Password = { UE4CodeGen_Private::EPropertyClass::Str, "Password", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(AccelByteBlueprintsIdentity_eventGetUserAccessTokenWithPasswordGrant_Parms, Password), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::NewProp_LoginId = { UE4CodeGen_Private::EPropertyClass::Str, "LoginId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(AccelByteBlueprintsIdentity_eventGetUserAccessTokenWithPasswordGrant_Parms, LoginId), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::NewProp_Namespace = { UE4CodeGen_Private::EPropertyClass::Str, "Namespace", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(AccelByteBlueprintsIdentity_eventGetUserAccessTokenWithPasswordGrant_Parms, Namespace), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::NewProp_ClientSecret = { UE4CodeGen_Private::EPropertyClass::Str, "ClientSecret", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(AccelByteBlueprintsIdentity_eventGetUserAccessTokenWithPasswordGrant_Parms, ClientSecret), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::NewProp_ClientId = { UE4CodeGen_Private::EPropertyClass::Str, "ClientId", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(AccelByteBlueprintsIdentity_eventGetUserAccessTokenWithPasswordGrant_Parms, ClientId), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::NewProp_ServerBaseUrl = { UE4CodeGen_Private::EPropertyClass::Str, "ServerBaseUrl", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(AccelByteBlueprintsIdentity_eventGetUserAccessTokenWithPasswordGrant_Parms, ServerBaseUrl), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::NewProp_OnError,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::NewProp_OnSuccess,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::NewProp_Password,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::NewProp_LoginId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::NewProp_Namespace,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::NewProp_ClientSecret,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::NewProp_ClientId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::NewProp_ServerBaseUrl,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::Function_MetaDataParams[] = {
		{ "Category", "AccelByte | Services | Identity" },
		{ "ModuleRelativePath", "Public/Blueprints/AccelByteBlueprintsIdentity.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAccelByteBlueprintsIdentity, "GetUserAccessTokenWithPasswordGrant", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04022401, sizeof(AccelByteBlueprintsIdentity_eventGetUserAccessTokenWithPasswordGrant_Parms), Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::PropPointers), 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UAccelByteBlueprintsIdentity_NoRegister()
	{
		return UAccelByteBlueprintsIdentity::StaticClass();
	}
	struct Z_Construct_UClass_UAccelByteBlueprintsIdentity_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAccelByteBlueprintsIdentity_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_AccelByteUe4Sdk,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UAccelByteBlueprintsIdentity_Statics::FuncInfo[] = {
		{ &Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_BlueprintError__DelegateSignature, "BlueprintError__DelegateSignature" }, // 1878869390
		{ &Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrant, "GetAccessTokenWithDeviceGrant" }, // 1954874124
		{ &Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_GetAccessTokenWithDeviceGrantSuccess__DelegateSignature, "GetAccessTokenWithDeviceGrantSuccess__DelegateSignature" }, // 2582322477
		{ &Z_Construct_UFunction_UAccelByteBlueprintsIdentity_GetUserAccessTokenWithPasswordGrant, "GetUserAccessTokenWithPasswordGrant" }, // 3597750855
		{ &Z_Construct_UDelegateFunction_UAccelByteBlueprintsIdentity_LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess__DelegateSignature, "LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess__DelegateSignature" }, // 905526730
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAccelByteBlueprintsIdentity_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "Blueprints/AccelByteBlueprintsIdentity.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/Blueprints/AccelByteBlueprintsIdentity.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAccelByteBlueprintsIdentity_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAccelByteBlueprintsIdentity>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UAccelByteBlueprintsIdentity_Statics::ClassParams = {
		&UAccelByteBlueprintsIdentity::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x000000A0u,
		FuncInfo, ARRAY_COUNT(FuncInfo),
		nullptr, 0,
		nullptr,
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_UAccelByteBlueprintsIdentity_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UAccelByteBlueprintsIdentity_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAccelByteBlueprintsIdentity()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAccelByteBlueprintsIdentity_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAccelByteBlueprintsIdentity, 3632679765);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAccelByteBlueprintsIdentity(Z_Construct_UClass_UAccelByteBlueprintsIdentity, &UAccelByteBlueprintsIdentity::StaticClass, TEXT("/Script/AccelByteUe4Sdk"), TEXT("UAccelByteBlueprintsIdentity"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAccelByteBlueprintsIdentity);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
