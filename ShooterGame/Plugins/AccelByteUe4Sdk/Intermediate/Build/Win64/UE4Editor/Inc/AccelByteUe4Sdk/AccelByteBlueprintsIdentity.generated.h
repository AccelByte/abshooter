// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FAccelByteModelsOAuthToken;
#ifdef ACCELBYTEUE4SDK_AccelByteBlueprintsIdentity_generated_h
#error "AccelByteBlueprintsIdentity.generated.h already included, missing '#pragma once' in AccelByteBlueprintsIdentity.h"
#endif
#define ACCELBYTEUE4SDK_AccelByteBlueprintsIdentity_generated_h

#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h_23_DELEGATE \
struct AccelByteBlueprintsIdentity_eventLoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess_Parms \
{ \
	FAccelByteModelsOAuthToken Result; \
}; \
static inline void FLoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess_DelegateWrapper(const FScriptDelegate& LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess, FAccelByteModelsOAuthToken const& Result) \
{ \
	AccelByteBlueprintsIdentity_eventLoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess_Parms Parms; \
	Parms.Result=Result; \
	LoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h_19_DELEGATE \
struct AccelByteBlueprintsIdentity_eventGetAccessTokenWithDeviceGrantSuccess_Parms \
{ \
	FAccelByteModelsOAuthToken Result; \
}; \
static inline void FGetAccessTokenWithDeviceGrantSuccess_DelegateWrapper(const FScriptDelegate& GetAccessTokenWithDeviceGrantSuccess, FAccelByteModelsOAuthToken const& Result) \
{ \
	AccelByteBlueprintsIdentity_eventGetAccessTokenWithDeviceGrantSuccess_Parms Parms; \
	Parms.Result=Result; \
	GetAccessTokenWithDeviceGrantSuccess.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h_17_DELEGATE \
struct AccelByteBlueprintsIdentity_eventBlueprintError_Parms \
{ \
	int32 ErrorCode; \
	FString ErrorMessage; \
}; \
static inline void FBlueprintError_DelegateWrapper(const FScriptDelegate& BlueprintError, int32 ErrorCode, const FString& ErrorMessage) \
{ \
	AccelByteBlueprintsIdentity_eventBlueprintError_Parms Parms; \
	Parms.ErrorCode=ErrorCode; \
	Parms.ErrorMessage=ErrorMessage; \
	BlueprintError.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetUserAccessTokenWithPasswordGrant) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientSecret); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_LoginId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Password); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsIdentity::GetUserAccessTokenWithPasswordGrant(Z_Param_ServerBaseUrl,Z_Param_ClientId,Z_Param_ClientSecret,Z_Param_Namespace,Z_Param_LoginId,Z_Param_Password,FLoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetAccessTokenWithDeviceGrant) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientSecret); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsIdentity::GetAccessTokenWithDeviceGrant(Z_Param_ServerBaseUrl,Z_Param_ClientId,Z_Param_ClientSecret,Z_Param_Namespace,FGetAccessTokenWithDeviceGrantSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetUserAccessTokenWithPasswordGrant) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientSecret); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_LoginId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Password); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsIdentity::GetUserAccessTokenWithPasswordGrant(Z_Param_ServerBaseUrl,Z_Param_ClientId,Z_Param_ClientSecret,Z_Param_Namespace,Z_Param_LoginId,Z_Param_Password,FLoginWithDeviceIdGetUserAccessTokenWithPasswordGrantSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetAccessTokenWithDeviceGrant) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientSecret); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsIdentity::GetAccessTokenWithDeviceGrant(Z_Param_ServerBaseUrl,Z_Param_ClientId,Z_Param_ClientSecret,Z_Param_Namespace,FGetAccessTokenWithDeviceGrantSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAccelByteBlueprintsIdentity(); \
	friend struct Z_Construct_UClass_UAccelByteBlueprintsIdentity_Statics; \
public: \
	DECLARE_CLASS(UAccelByteBlueprintsIdentity, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AccelByteUe4Sdk"), NO_API) \
	DECLARE_SERIALIZER(UAccelByteBlueprintsIdentity)


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h_15_INCLASS \
private: \
	static void StaticRegisterNativesUAccelByteBlueprintsIdentity(); \
	friend struct Z_Construct_UClass_UAccelByteBlueprintsIdentity_Statics; \
public: \
	DECLARE_CLASS(UAccelByteBlueprintsIdentity, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AccelByteUe4Sdk"), NO_API) \
	DECLARE_SERIALIZER(UAccelByteBlueprintsIdentity)


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAccelByteBlueprintsIdentity(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAccelByteBlueprintsIdentity) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAccelByteBlueprintsIdentity); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAccelByteBlueprintsIdentity); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAccelByteBlueprintsIdentity(UAccelByteBlueprintsIdentity&&); \
	NO_API UAccelByteBlueprintsIdentity(const UAccelByteBlueprintsIdentity&); \
public:


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAccelByteBlueprintsIdentity(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAccelByteBlueprintsIdentity(UAccelByteBlueprintsIdentity&&); \
	NO_API UAccelByteBlueprintsIdentity(const UAccelByteBlueprintsIdentity&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAccelByteBlueprintsIdentity); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAccelByteBlueprintsIdentity); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAccelByteBlueprintsIdentity)


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h_15_PRIVATE_PROPERTY_OFFSET
#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h_12_PROLOG
#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h_15_PRIVATE_PROPERTY_OFFSET \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h_15_RPC_WRAPPERS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h_15_INCLASS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h_15_PRIVATE_PROPERTY_OFFSET \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h_15_INCLASS_NO_PURE_DECLS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsIdentity_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
