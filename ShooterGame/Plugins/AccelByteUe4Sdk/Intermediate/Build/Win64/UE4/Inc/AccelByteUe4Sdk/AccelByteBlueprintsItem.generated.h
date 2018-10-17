// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FAccelByteModelsItemPagingSlicedResult;
struct FAccelByteModelsItemInfo;
#ifdef ACCELBYTEUE4SDK_AccelByteBlueprintsItem_generated_h
#error "AccelByteBlueprintsItem.generated.h already included, missing '#pragma once' in AccelByteBlueprintsItem.h"
#endif
#define ACCELBYTEUE4SDK_AccelByteBlueprintsItem_generated_h

#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h_25_DELEGATE \
struct AccelByteBlueprintsItem_eventGetItemsByCriteriaSuccess_Parms \
{ \
	FAccelByteModelsItemPagingSlicedResult Result; \
}; \
static inline void FGetItemsByCriteriaSuccess_DelegateWrapper(const FScriptDelegate& GetItemsByCriteriaSuccess, FAccelByteModelsItemPagingSlicedResult const& Result) \
{ \
	AccelByteBlueprintsItem_eventGetItemsByCriteriaSuccess_Parms Parms; \
	Parms.Result=Result; \
	GetItemsByCriteriaSuccess.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h_19_DELEGATE \
struct AccelByteBlueprintsItem_eventGetItemByIdSuccess_Parms \
{ \
	FAccelByteModelsItemInfo Result; \
}; \
static inline void FGetItemByIdSuccess_DelegateWrapper(const FScriptDelegate& GetItemByIdSuccess, FAccelByteModelsItemInfo const& Result) \
{ \
	AccelByteBlueprintsItem_eventGetItemByIdSuccess_Parms Parms; \
	Parms.Result=Result; \
	GetItemByIdSuccess.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h_17_DELEGATE \
struct AccelByteBlueprintsItem_eventBlueprintError_Parms \
{ \
	int32 ErrorCode; \
	FString ErrorMessage; \
}; \
static inline void FBlueprintError_DelegateWrapper(const FScriptDelegate& BlueprintError, int32 ErrorCode, const FString& ErrorMessage) \
{ \
	AccelByteBlueprintsItem_eventBlueprintError_Parms Parms; \
	Parms.ErrorCode=ErrorCode; \
	Parms.ErrorMessage=ErrorMessage; \
	BlueprintError.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetItemsByCriteriaEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Region); \
		P_GET_PROPERTY(UStrProperty,Z_Param_CategoryPath); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ItemType); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Status); \
		P_GET_PROPERTY(UIntProperty,Z_Param_Page); \
		P_GET_PROPERTY(UIntProperty,Z_Param_Size); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsItem::GetItemsByCriteriaEasy(Z_Param_Language,Z_Param_Region,Z_Param_CategoryPath,Z_Param_ItemType,Z_Param_Status,Z_Param_Page,Z_Param_Size,FGetItemsByCriteriaSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetItemsByCriteria) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Region); \
		P_GET_PROPERTY(UStrProperty,Z_Param_CategoryPath); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ItemType); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Status); \
		P_GET_PROPERTY(UIntProperty,Z_Param_Page); \
		P_GET_PROPERTY(UIntProperty,Z_Param_Size); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsItem::GetItemsByCriteria(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,Z_Param_Language,Z_Param_Region,Z_Param_CategoryPath,Z_Param_ItemType,Z_Param_Status,Z_Param_Page,Z_Param_Size,FGetItemsByCriteriaSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetItemByIdEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ItemId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Region); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsItem::GetItemByIdEasy(Z_Param_ItemId,Z_Param_Region,Z_Param_Language,FGetItemByIdSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetItemById) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ItemId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Region); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsItem::GetItemById(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,Z_Param_ItemId,Z_Param_Region,Z_Param_Language,FGetItemByIdSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetItemsByCriteriaEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Region); \
		P_GET_PROPERTY(UStrProperty,Z_Param_CategoryPath); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ItemType); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Status); \
		P_GET_PROPERTY(UIntProperty,Z_Param_Page); \
		P_GET_PROPERTY(UIntProperty,Z_Param_Size); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsItem::GetItemsByCriteriaEasy(Z_Param_Language,Z_Param_Region,Z_Param_CategoryPath,Z_Param_ItemType,Z_Param_Status,Z_Param_Page,Z_Param_Size,FGetItemsByCriteriaSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetItemsByCriteria) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Region); \
		P_GET_PROPERTY(UStrProperty,Z_Param_CategoryPath); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ItemType); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Status); \
		P_GET_PROPERTY(UIntProperty,Z_Param_Page); \
		P_GET_PROPERTY(UIntProperty,Z_Param_Size); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsItem::GetItemsByCriteria(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,Z_Param_Language,Z_Param_Region,Z_Param_CategoryPath,Z_Param_ItemType,Z_Param_Status,Z_Param_Page,Z_Param_Size,FGetItemsByCriteriaSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetItemByIdEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ItemId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Region); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsItem::GetItemByIdEasy(Z_Param_ItemId,Z_Param_Region,Z_Param_Language,FGetItemByIdSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetItemById) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ItemId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Region); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Language); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsItem::GetItemById(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,Z_Param_ItemId,Z_Param_Region,Z_Param_Language,FGetItemByIdSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAccelByteBlueprintsItem(); \
	friend struct Z_Construct_UClass_UAccelByteBlueprintsItem_Statics; \
public: \
	DECLARE_CLASS(UAccelByteBlueprintsItem, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AccelByteUe4Sdk"), NO_API) \
	DECLARE_SERIALIZER(UAccelByteBlueprintsItem)


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h_15_INCLASS \
private: \
	static void StaticRegisterNativesUAccelByteBlueprintsItem(); \
	friend struct Z_Construct_UClass_UAccelByteBlueprintsItem_Statics; \
public: \
	DECLARE_CLASS(UAccelByteBlueprintsItem, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AccelByteUe4Sdk"), NO_API) \
	DECLARE_SERIALIZER(UAccelByteBlueprintsItem)


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAccelByteBlueprintsItem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAccelByteBlueprintsItem) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAccelByteBlueprintsItem); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAccelByteBlueprintsItem); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAccelByteBlueprintsItem(UAccelByteBlueprintsItem&&); \
	NO_API UAccelByteBlueprintsItem(const UAccelByteBlueprintsItem&); \
public:


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAccelByteBlueprintsItem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAccelByteBlueprintsItem(UAccelByteBlueprintsItem&&); \
	NO_API UAccelByteBlueprintsItem(const UAccelByteBlueprintsItem&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAccelByteBlueprintsItem); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAccelByteBlueprintsItem); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAccelByteBlueprintsItem)


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h_15_PRIVATE_PROPERTY_OFFSET
#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h_12_PROLOG
#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h_15_PRIVATE_PROPERTY_OFFSET \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h_15_RPC_WRAPPERS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h_15_INCLASS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h_15_PRIVATE_PROPERTY_OFFSET \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h_15_INCLASS_NO_PURE_DECLS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsItem_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
