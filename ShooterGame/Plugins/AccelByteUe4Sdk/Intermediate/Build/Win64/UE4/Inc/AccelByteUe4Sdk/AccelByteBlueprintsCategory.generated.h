// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FAccelByteModelsFullCategoryInfo;
#ifdef ACCELBYTEUE4SDK_AccelByteBlueprintsCategory_generated_h
#error "AccelByteBlueprintsCategory.generated.h already included, missing '#pragma once' in AccelByteBlueprintsCategory.h"
#endif
#define ACCELBYTEUE4SDK_AccelByteBlueprintsCategory_generated_h

#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_37_DELEGATE \
struct AccelByteBlueprintsCategory_eventGetDescendantCategoriesSuccess_Parms \
{ \
	TArray<FAccelByteModelsFullCategoryInfo> Result; \
}; \
static inline void FGetDescendantCategoriesSuccess_DelegateWrapper(const FScriptDelegate& GetDescendantCategoriesSuccess, TArray<FAccelByteModelsFullCategoryInfo> const& Result) \
{ \
	AccelByteBlueprintsCategory_eventGetDescendantCategoriesSuccess_Parms Parms; \
	Parms.Result=Result; \
	GetDescendantCategoriesSuccess.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_31_DELEGATE \
struct AccelByteBlueprintsCategory_eventGetChildCategoriesSuccess_Parms \
{ \
	TArray<FAccelByteModelsFullCategoryInfo> Result; \
}; \
static inline void FGetChildCategoriesSuccess_DelegateWrapper(const FScriptDelegate& GetChildCategoriesSuccess, TArray<FAccelByteModelsFullCategoryInfo> const& Result) \
{ \
	AccelByteBlueprintsCategory_eventGetChildCategoriesSuccess_Parms Parms; \
	Parms.Result=Result; \
	GetChildCategoriesSuccess.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_25_DELEGATE \
struct AccelByteBlueprintsCategory_eventGetCategorySuccess_Parms \
{ \
	FAccelByteModelsFullCategoryInfo Result; \
}; \
static inline void FGetCategorySuccess_DelegateWrapper(const FScriptDelegate& GetCategorySuccess, FAccelByteModelsFullCategoryInfo const& Result) \
{ \
	AccelByteBlueprintsCategory_eventGetCategorySuccess_Parms Parms; \
	Parms.Result=Result; \
	GetCategorySuccess.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_19_DELEGATE \
struct AccelByteBlueprintsCategory_eventGetRootCategoriesSuccess_Parms \
{ \
	TArray<FAccelByteModelsFullCategoryInfo> Result; \
}; \
static inline void FGetRootCategoriesSuccess_DelegateWrapper(const FScriptDelegate& GetRootCategoriesSuccess, TArray<FAccelByteModelsFullCategoryInfo> const& Result) \
{ \
	AccelByteBlueprintsCategory_eventGetRootCategoriesSuccess_Parms Parms; \
	Parms.Result=Result; \
	GetRootCategoriesSuccess.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_17_DELEGATE \
struct AccelByteBlueprintsCategory_eventBlueprintError_Parms \
{ \
	int32 ErrorCode; \
	FString ErrorMessage; \
}; \
static inline void FBlueprintError_DelegateWrapper(const FScriptDelegate& BlueprintError, int32 ErrorCode, const FString& ErrorMessage) \
{ \
	AccelByteBlueprintsCategory_eventBlueprintError_Parms Parms; \
	Parms.ErrorCode=ErrorCode; \
	Parms.ErrorMessage=ErrorMessage; \
	BlueprintError.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetDescendantCategoriesEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UStrProperty,Z_Param_CategoryPath); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsCategory::GetDescendantCategoriesEasy(Z_Param_Language,Z_Param_CategoryPath,FGetDescendantCategoriesSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetDescendantCategories) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UStrProperty,Z_Param_CategoryPath); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsCategory::GetDescendantCategories(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_Language,Z_Param_CategoryPath,FGetDescendantCategoriesSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetChildCategoriesEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UStrProperty,Z_Param_CategoryPath); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsCategory::GetChildCategoriesEasy(Z_Param_Language,Z_Param_CategoryPath,FGetChildCategoriesSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetChildCategories) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UStrProperty,Z_Param_CategoryPath); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsCategory::GetChildCategories(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_Language,Z_Param_CategoryPath,FGetChildCategoriesSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetCategoryEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ParentPath); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsCategory::GetCategoryEasy(Z_Param_ParentPath,Z_Param_Language,FGetCategorySuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetCategory) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ParentPath); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsCategory::GetCategory(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_ParentPath,Z_Param_Language,FGetCategorySuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetRootCategoriesEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsCategory::GetRootCategoriesEasy(Z_Param_Language,FGetRootCategoriesSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetRootCategories) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsCategory::GetRootCategories(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_Language,FGetRootCategoriesSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetDescendantCategoriesEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UStrProperty,Z_Param_CategoryPath); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsCategory::GetDescendantCategoriesEasy(Z_Param_Language,Z_Param_CategoryPath,FGetDescendantCategoriesSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetDescendantCategories) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UStrProperty,Z_Param_CategoryPath); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsCategory::GetDescendantCategories(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_Language,Z_Param_CategoryPath,FGetDescendantCategoriesSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetChildCategoriesEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UStrProperty,Z_Param_CategoryPath); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsCategory::GetChildCategoriesEasy(Z_Param_Language,Z_Param_CategoryPath,FGetChildCategoriesSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetChildCategories) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UStrProperty,Z_Param_CategoryPath); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsCategory::GetChildCategories(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_Language,Z_Param_CategoryPath,FGetChildCategoriesSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetCategoryEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ParentPath); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsCategory::GetCategoryEasy(Z_Param_ParentPath,Z_Param_Language,FGetCategorySuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetCategory) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ParentPath); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsCategory::GetCategory(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_ParentPath,Z_Param_Language,FGetCategorySuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetRootCategoriesEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsCategory::GetRootCategoriesEasy(Z_Param_Language,FGetRootCategoriesSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetRootCategories) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsCategory::GetRootCategories(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_Language,FGetRootCategoriesSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAccelByteBlueprintsCategory(); \
	friend struct Z_Construct_UClass_UAccelByteBlueprintsCategory_Statics; \
public: \
	DECLARE_CLASS(UAccelByteBlueprintsCategory, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AccelByteUe4Sdk"), NO_API) \
	DECLARE_SERIALIZER(UAccelByteBlueprintsCategory)


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_15_INCLASS \
private: \
	static void StaticRegisterNativesUAccelByteBlueprintsCategory(); \
	friend struct Z_Construct_UClass_UAccelByteBlueprintsCategory_Statics; \
public: \
	DECLARE_CLASS(UAccelByteBlueprintsCategory, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AccelByteUe4Sdk"), NO_API) \
	DECLARE_SERIALIZER(UAccelByteBlueprintsCategory)


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAccelByteBlueprintsCategory(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAccelByteBlueprintsCategory) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAccelByteBlueprintsCategory); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAccelByteBlueprintsCategory); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAccelByteBlueprintsCategory(UAccelByteBlueprintsCategory&&); \
	NO_API UAccelByteBlueprintsCategory(const UAccelByteBlueprintsCategory&); \
public:


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAccelByteBlueprintsCategory(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAccelByteBlueprintsCategory(UAccelByteBlueprintsCategory&&); \
	NO_API UAccelByteBlueprintsCategory(const UAccelByteBlueprintsCategory&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAccelByteBlueprintsCategory); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAccelByteBlueprintsCategory); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAccelByteBlueprintsCategory)


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_15_PRIVATE_PROPERTY_OFFSET
#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_12_PROLOG
#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_15_PRIVATE_PROPERTY_OFFSET \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_15_RPC_WRAPPERS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_15_INCLASS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_15_PRIVATE_PROPERTY_OFFSET \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_15_INCLASS_NO_PURE_DECLS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsCategory_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
