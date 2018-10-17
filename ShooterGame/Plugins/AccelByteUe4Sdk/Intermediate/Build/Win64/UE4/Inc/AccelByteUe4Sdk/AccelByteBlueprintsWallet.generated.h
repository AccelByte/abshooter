// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FAccelByteModelsWalletInfo;
#ifdef ACCELBYTEUE4SDK_AccelByteBlueprintsWallet_generated_h
#error "AccelByteBlueprintsWallet.generated.h already included, missing '#pragma once' in AccelByteBlueprintsWallet.h"
#endif
#define ACCELBYTEUE4SDK_AccelByteBlueprintsWallet_generated_h

#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsWallet_h_20_DELEGATE \
struct AccelByteBlueprintsWallet_eventGetWalletByCurrencyCodeSuccess_Parms \
{ \
	FAccelByteModelsWalletInfo Result; \
}; \
static inline void FGetWalletByCurrencyCodeSuccess_DelegateWrapper(const FScriptDelegate& GetWalletByCurrencyCodeSuccess, FAccelByteModelsWalletInfo const& Result) \
{ \
	AccelByteBlueprintsWallet_eventGetWalletByCurrencyCodeSuccess_Parms Parms; \
	Parms.Result=Result; \
	GetWalletByCurrencyCodeSuccess.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsWallet_h_18_DELEGATE \
struct AccelByteBlueprintsWallet_eventBlueprintError_Parms \
{ \
	int32 ErrorCode; \
	FString ErrorMessage; \
}; \
static inline void FBlueprintError_DelegateWrapper(const FScriptDelegate& BlueprintError, int32 ErrorCode, const FString& ErrorMessage) \
{ \
	AccelByteBlueprintsWallet_eventBlueprintError_Parms Parms; \
	Parms.ErrorCode=ErrorCode; \
	Parms.ErrorMessage=ErrorMessage; \
	BlueprintError.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsWallet_h_16_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetWalletInfoByCurrencyCodeEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_CurrencyCode); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsWallet::GetWalletInfoByCurrencyCodeEasy(Z_Param_CurrencyCode,FGetWalletByCurrencyCodeSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetWalletInfoByCurrencyCode) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_CurrencyCode); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsWallet::GetWalletInfoByCurrencyCode(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,Z_Param_CurrencyCode,FGetWalletByCurrencyCodeSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsWallet_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetWalletInfoByCurrencyCodeEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_CurrencyCode); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsWallet::GetWalletInfoByCurrencyCodeEasy(Z_Param_CurrencyCode,FGetWalletByCurrencyCodeSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetWalletInfoByCurrencyCode) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_CurrencyCode); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsWallet::GetWalletInfoByCurrencyCode(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,Z_Param_CurrencyCode,FGetWalletByCurrencyCodeSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsWallet_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAccelByteBlueprintsWallet(); \
	friend struct Z_Construct_UClass_UAccelByteBlueprintsWallet_Statics; \
public: \
	DECLARE_CLASS(UAccelByteBlueprintsWallet, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AccelByteUe4Sdk"), NO_API) \
	DECLARE_SERIALIZER(UAccelByteBlueprintsWallet)


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsWallet_h_16_INCLASS \
private: \
	static void StaticRegisterNativesUAccelByteBlueprintsWallet(); \
	friend struct Z_Construct_UClass_UAccelByteBlueprintsWallet_Statics; \
public: \
	DECLARE_CLASS(UAccelByteBlueprintsWallet, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AccelByteUe4Sdk"), NO_API) \
	DECLARE_SERIALIZER(UAccelByteBlueprintsWallet)


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsWallet_h_16_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAccelByteBlueprintsWallet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAccelByteBlueprintsWallet) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAccelByteBlueprintsWallet); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAccelByteBlueprintsWallet); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAccelByteBlueprintsWallet(UAccelByteBlueprintsWallet&&); \
	NO_API UAccelByteBlueprintsWallet(const UAccelByteBlueprintsWallet&); \
public:


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsWallet_h_16_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAccelByteBlueprintsWallet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAccelByteBlueprintsWallet(UAccelByteBlueprintsWallet&&); \
	NO_API UAccelByteBlueprintsWallet(const UAccelByteBlueprintsWallet&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAccelByteBlueprintsWallet); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAccelByteBlueprintsWallet); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAccelByteBlueprintsWallet)


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsWallet_h_16_PRIVATE_PROPERTY_OFFSET
#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsWallet_h_13_PROLOG
#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsWallet_h_16_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsWallet_h_16_PRIVATE_PROPERTY_OFFSET \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsWallet_h_16_RPC_WRAPPERS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsWallet_h_16_INCLASS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsWallet_h_16_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsWallet_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsWallet_h_16_PRIVATE_PROPERTY_OFFSET \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsWallet_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsWallet_h_16_INCLASS_NO_PURE_DECLS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsWallet_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsWallet_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
