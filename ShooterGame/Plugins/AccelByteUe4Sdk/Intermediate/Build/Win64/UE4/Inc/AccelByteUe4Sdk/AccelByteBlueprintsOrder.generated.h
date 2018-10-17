// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FAccelByteModelsOrderHistoryInfo;
struct FAccelByteModelsOrderInfo;
struct FAccelByteModelsOrderInfoPaging;
struct FAccelByteModelsOrderCreate;
#ifdef ACCELBYTEUE4SDK_AccelByteBlueprintsOrder_generated_h
#error "AccelByteBlueprintsOrder.generated.h already included, missing '#pragma once' in AccelByteBlueprintsOrder.h"
#endif
#define ACCELBYTEUE4SDK_AccelByteBlueprintsOrder_generated_h

#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_43_DELEGATE \
struct AccelByteBlueprintsOrder_eventGetUserOrderHistorySuccess_Parms \
{ \
	TArray<FAccelByteModelsOrderHistoryInfo> Result; \
}; \
static inline void FGetUserOrderHistorySuccess_DelegateWrapper(const FScriptDelegate& GetUserOrderHistorySuccess, TArray<FAccelByteModelsOrderHistoryInfo> const& Result) \
{ \
	AccelByteBlueprintsOrder_eventGetUserOrderHistorySuccess_Parms Parms; \
	Parms.Result=Result; \
	GetUserOrderHistorySuccess.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_37_DELEGATE \
struct AccelByteBlueprintsOrder_eventFulfillOrderSuccess_Parms \
{ \
	FAccelByteModelsOrderInfo Result; \
}; \
static inline void FFulfillOrderSuccess_DelegateWrapper(const FScriptDelegate& FulfillOrderSuccess, FAccelByteModelsOrderInfo const& Result) \
{ \
	AccelByteBlueprintsOrder_eventFulfillOrderSuccess_Parms Parms; \
	Parms.Result=Result; \
	FulfillOrderSuccess.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_31_DELEGATE \
struct AccelByteBlueprintsOrder_eventGetUserOrdersSuccess_Parms \
{ \
	FAccelByteModelsOrderInfoPaging Result; \
}; \
static inline void FGetUserOrdersSuccess_DelegateWrapper(const FScriptDelegate& GetUserOrdersSuccess, FAccelByteModelsOrderInfoPaging const& Result) \
{ \
	AccelByteBlueprintsOrder_eventGetUserOrdersSuccess_Parms Parms; \
	Parms.Result=Result; \
	GetUserOrdersSuccess.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_25_DELEGATE \
struct AccelByteBlueprintsOrder_eventGetUserOrderSuccess_Parms \
{ \
	FAccelByteModelsOrderInfo Result; \
}; \
static inline void FGetUserOrderSuccess_DelegateWrapper(const FScriptDelegate& GetUserOrderSuccess, FAccelByteModelsOrderInfo const& Result) \
{ \
	AccelByteBlueprintsOrder_eventGetUserOrderSuccess_Parms Parms; \
	Parms.Result=Result; \
	GetUserOrderSuccess.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_19_DELEGATE \
struct AccelByteBlueprintsOrder_eventCreateNewOrderSuccess_Parms \
{ \
	FAccelByteModelsOrderInfo Result; \
}; \
static inline void FCreateNewOrderSuccess_DelegateWrapper(const FScriptDelegate& CreateNewOrderSuccess, FAccelByteModelsOrderInfo const& Result) \
{ \
	AccelByteBlueprintsOrder_eventCreateNewOrderSuccess_Parms Parms; \
	Parms.Result=Result; \
	CreateNewOrderSuccess.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_17_DELEGATE \
struct AccelByteBlueprintsOrder_eventBlueprintError_Parms \
{ \
	int32 ErrorCode; \
	FString ErrorMessage; \
}; \
static inline void FBlueprintError_DelegateWrapper(const FScriptDelegate& BlueprintError, int32 ErrorCode, const FString& ErrorMessage) \
{ \
	AccelByteBlueprintsOrder_eventBlueprintError_Parms Parms; \
	Parms.ErrorCode=ErrorCode; \
	Parms.ErrorMessage=ErrorMessage; \
	BlueprintError.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetUserOrderHistoryEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_OrderNo); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsOrder::GetUserOrderHistoryEasy(Z_Param_OrderNo,FGetUserOrderHistorySuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserOrderHistory) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_OrderNo); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsOrder::GetUserOrderHistory(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,Z_Param_OrderNo,FGetUserOrderHistorySuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execFulfillOrderEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_OrderNo); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsOrder::FulfillOrderEasy(Z_Param_OrderNo,FFulfillOrderSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execFulfillOrder) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_OrderNo); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsOrder::FulfillOrder(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,Z_Param_OrderNo,FFulfillOrderSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserOrdersEasy) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_Page); \
		P_GET_PROPERTY(UIntProperty,Z_Param_Size); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsOrder::GetUserOrdersEasy(Z_Param_Page,Z_Param_Size,FGetUserOrdersSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserOrders) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UIntProperty,Z_Param_Page); \
		P_GET_PROPERTY(UIntProperty,Z_Param_Size); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsOrder::GetUserOrders(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,Z_Param_Page,Z_Param_Size,FGetUserOrdersSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserOrderEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_OrderNo); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsOrder::GetUserOrderEasy(Z_Param_OrderNo,FGetUserOrderSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserOrder) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_OrderNo); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsOrder::GetUserOrder(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,Z_Param_OrderNo,FGetUserOrderSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCreateNewOrderEasy) \
	{ \
		P_GET_STRUCT_REF(FAccelByteModelsOrderCreate,Z_Param_Out_OrderCreate); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsOrder::CreateNewOrderEasy(Z_Param_Out_OrderCreate,FCreateNewOrderSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCreateNewOrder) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_STRUCT_REF(FAccelByteModelsOrderCreate,Z_Param_Out_OrderCreate); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsOrder::CreateNewOrder(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,Z_Param_Out_OrderCreate,FCreateNewOrderSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetUserOrderHistoryEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_OrderNo); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsOrder::GetUserOrderHistoryEasy(Z_Param_OrderNo,FGetUserOrderHistorySuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserOrderHistory) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_OrderNo); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsOrder::GetUserOrderHistory(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,Z_Param_OrderNo,FGetUserOrderHistorySuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execFulfillOrderEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_OrderNo); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsOrder::FulfillOrderEasy(Z_Param_OrderNo,FFulfillOrderSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execFulfillOrder) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_OrderNo); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsOrder::FulfillOrder(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,Z_Param_OrderNo,FFulfillOrderSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserOrdersEasy) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_Page); \
		P_GET_PROPERTY(UIntProperty,Z_Param_Size); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsOrder::GetUserOrdersEasy(Z_Param_Page,Z_Param_Size,FGetUserOrdersSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserOrders) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UIntProperty,Z_Param_Page); \
		P_GET_PROPERTY(UIntProperty,Z_Param_Size); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsOrder::GetUserOrders(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,Z_Param_Page,Z_Param_Size,FGetUserOrdersSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserOrderEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_OrderNo); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsOrder::GetUserOrderEasy(Z_Param_OrderNo,FGetUserOrderSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserOrder) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_OrderNo); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsOrder::GetUserOrder(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,Z_Param_OrderNo,FGetUserOrderSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCreateNewOrderEasy) \
	{ \
		P_GET_STRUCT_REF(FAccelByteModelsOrderCreate,Z_Param_Out_OrderCreate); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsOrder::CreateNewOrderEasy(Z_Param_Out_OrderCreate,FCreateNewOrderSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCreateNewOrder) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_AccessToken); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_STRUCT_REF(FAccelByteModelsOrderCreate,Z_Param_Out_OrderCreate); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsOrder::CreateNewOrder(Z_Param_ServerBaseUrl,Z_Param_AccessToken,Z_Param_Namespace,Z_Param_UserId,Z_Param_Out_OrderCreate,FCreateNewOrderSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAccelByteBlueprintsOrder(); \
	friend struct Z_Construct_UClass_UAccelByteBlueprintsOrder_Statics; \
public: \
	DECLARE_CLASS(UAccelByteBlueprintsOrder, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AccelByteUe4Sdk"), NO_API) \
	DECLARE_SERIALIZER(UAccelByteBlueprintsOrder)


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_15_INCLASS \
private: \
	static void StaticRegisterNativesUAccelByteBlueprintsOrder(); \
	friend struct Z_Construct_UClass_UAccelByteBlueprintsOrder_Statics; \
public: \
	DECLARE_CLASS(UAccelByteBlueprintsOrder, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AccelByteUe4Sdk"), NO_API) \
	DECLARE_SERIALIZER(UAccelByteBlueprintsOrder)


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAccelByteBlueprintsOrder(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAccelByteBlueprintsOrder) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAccelByteBlueprintsOrder); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAccelByteBlueprintsOrder); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAccelByteBlueprintsOrder(UAccelByteBlueprintsOrder&&); \
	NO_API UAccelByteBlueprintsOrder(const UAccelByteBlueprintsOrder&); \
public:


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAccelByteBlueprintsOrder(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAccelByteBlueprintsOrder(UAccelByteBlueprintsOrder&&); \
	NO_API UAccelByteBlueprintsOrder(const UAccelByteBlueprintsOrder&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAccelByteBlueprintsOrder); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAccelByteBlueprintsOrder); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAccelByteBlueprintsOrder)


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_15_PRIVATE_PROPERTY_OFFSET
#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_12_PROLOG
#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_15_PRIVATE_PROPERTY_OFFSET \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_15_RPC_WRAPPERS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_15_INCLASS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_15_PRIVATE_PROPERTY_OFFSET \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_15_INCLASS_NO_PURE_DECLS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsOrder_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
