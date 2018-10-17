// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FAccelByteModelsUserProfileInfo;
struct FAccelByteModelsUserProfileInfoUpdate;
#ifdef ACCELBYTEUE4SDK_AccelByteBlueprintsUserProfile_generated_h
#error "AccelByteBlueprintsUserProfile.generated.h already included, missing '#pragma once' in AccelByteBlueprintsUserProfile.h"
#endif
#define ACCELBYTEUE4SDK_AccelByteBlueprintsUserProfile_generated_h

#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_30_DELEGATE \
static inline void FUpdateUserProfileSuccess_DelegateWrapper(const FScriptDelegate& UpdateUserProfileSuccess) \
{ \
	UpdateUserProfileSuccess.ProcessDelegate<UObject>(NULL); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_26_DELEGATE \
struct AccelByteBlueprintsUserProfile_eventCreateDefaultUserProfileSuccess_Parms \
{ \
	FAccelByteModelsUserProfileInfo Result; \
}; \
static inline void FCreateDefaultUserProfileSuccess_DelegateWrapper(const FScriptDelegate& CreateDefaultUserProfileSuccess, FAccelByteModelsUserProfileInfo const& Result) \
{ \
	AccelByteBlueprintsUserProfile_eventCreateDefaultUserProfileSuccess_Parms Parms; \
	Parms.Result=Result; \
	CreateDefaultUserProfileSuccess.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_22_DELEGATE \
struct AccelByteBlueprintsUserProfile_eventGetUserProfileSuccess_Parms \
{ \
	FAccelByteModelsUserProfileInfo Result; \
}; \
static inline void FGetUserProfileSuccess_DelegateWrapper(const FScriptDelegate& GetUserProfileSuccess, FAccelByteModelsUserProfileInfo const& Result) \
{ \
	AccelByteBlueprintsUserProfile_eventGetUserProfileSuccess_Parms Parms; \
	Parms.Result=Result; \
	GetUserProfileSuccess.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_20_DELEGATE \
struct AccelByteBlueprintsUserProfile_eventBlueprintError_Parms \
{ \
	int32 ErrorCode; \
	FString ErrorMessage; \
}; \
static inline void FBlueprintError_DelegateWrapper(const FScriptDelegate& BlueprintError, int32 ErrorCode, const FString& ErrorMessage) \
{ \
	AccelByteBlueprintsUserProfile_eventBlueprintError_Parms Parms; \
	Parms.ErrorCode=ErrorCode; \
	Parms.ErrorMessage=ErrorMessage; \
	BlueprintError.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_18_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execUpdateUserProfile) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_STRUCT_REF(FAccelByteModelsUserProfileInfoUpdate,Z_Param_Out_NewUserProfile); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUserProfile::UpdateUserProfile(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,Z_Param_Out_NewUserProfile,FUpdateUserProfileSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCreateDefaultUserProfile) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_DisplayName); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUserProfile::CreateDefaultUserProfile(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,Z_Param_DisplayName,FCreateDefaultUserProfileSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserProfile) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUserProfile::GetUserProfile(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,FGetUserProfileSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execUpdateUserProfile) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_STRUCT_REF(FAccelByteModelsUserProfileInfoUpdate,Z_Param_Out_NewUserProfile); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUserProfile::UpdateUserProfile(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,Z_Param_Out_NewUserProfile,FUpdateUserProfileSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCreateDefaultUserProfile) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_DisplayName); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUserProfile::CreateDefaultUserProfile(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,Z_Param_DisplayName,FCreateDefaultUserProfileSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserProfile) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUserProfile::GetUserProfile(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,FGetUserProfileSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAccelByteBlueprintsUserProfile(); \
	friend struct Z_Construct_UClass_UAccelByteBlueprintsUserProfile_Statics; \
public: \
	DECLARE_CLASS(UAccelByteBlueprintsUserProfile, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AccelByteUe4Sdk"), NO_API) \
	DECLARE_SERIALIZER(UAccelByteBlueprintsUserProfile)


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_18_INCLASS \
private: \
	static void StaticRegisterNativesUAccelByteBlueprintsUserProfile(); \
	friend struct Z_Construct_UClass_UAccelByteBlueprintsUserProfile_Statics; \
public: \
	DECLARE_CLASS(UAccelByteBlueprintsUserProfile, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AccelByteUe4Sdk"), NO_API) \
	DECLARE_SERIALIZER(UAccelByteBlueprintsUserProfile)


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_18_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAccelByteBlueprintsUserProfile(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAccelByteBlueprintsUserProfile) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAccelByteBlueprintsUserProfile); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAccelByteBlueprintsUserProfile); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAccelByteBlueprintsUserProfile(UAccelByteBlueprintsUserProfile&&); \
	NO_API UAccelByteBlueprintsUserProfile(const UAccelByteBlueprintsUserProfile&); \
public:


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_18_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAccelByteBlueprintsUserProfile(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAccelByteBlueprintsUserProfile(UAccelByteBlueprintsUserProfile&&); \
	NO_API UAccelByteBlueprintsUserProfile(const UAccelByteBlueprintsUserProfile&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAccelByteBlueprintsUserProfile); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAccelByteBlueprintsUserProfile); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAccelByteBlueprintsUserProfile)


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_18_PRIVATE_PROPERTY_OFFSET
#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_15_PROLOG
#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_18_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_18_PRIVATE_PROPERTY_OFFSET \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_18_RPC_WRAPPERS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_18_INCLASS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_18_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_18_PRIVATE_PROPERTY_OFFSET \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_18_INCLASS_NO_PURE_DECLS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUserProfile_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
