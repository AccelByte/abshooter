// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef ACCELBYTECUSTOMWEBBROWSERWIDGET_AccelByteCustomWebBrowserWidget_generated_h
#error "AccelByteCustomWebBrowserWidget.generated.h already included, missing '#pragma once' in AccelByteCustomWebBrowserWidget.h"
#endif
#define ACCELBYTECUSTOMWEBBROWSERWIDGET_AccelByteCustomWebBrowserWidget_generated_h

#define ShooterGame_Plugins_AccelByteCustomWebBrowserWidget_Source_AccelByteCustomWebBrowserWidget_Public_AccelByteCustomWebBrowserWidget_h_20_DELEGATE \
struct AccelByteCustomWebBrowserWidget_eventOnRedirectSuccess_Parms \
{ \
	FText NewUrl; \
	FText Token; \
}; \
static inline void FOnRedirectSuccess_DelegateWrapper(const FMulticastScriptDelegate& OnRedirectSuccess, FText const& NewUrl, FText const& Token) \
{ \
	AccelByteCustomWebBrowserWidget_eventOnRedirectSuccess_Parms Parms; \
	Parms.NewUrl=NewUrl; \
	Parms.Token=Token; \
	OnRedirectSuccess.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteCustomWebBrowserWidget_Source_AccelByteCustomWebBrowserWidget_Public_AccelByteCustomWebBrowserWidget_h_19_DELEGATE \
struct AccelByteCustomWebBrowserWidget_eventOnUrlChanged_Parms \
{ \
	FText Url; \
}; \
static inline void FOnUrlChanged_DelegateWrapper(const FMulticastScriptDelegate& OnUrlChanged, FText const& Url) \
{ \
	AccelByteCustomWebBrowserWidget_eventOnUrlChanged_Parms Parms; \
	Parms.Url=Url; \
	OnUrlChanged.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteCustomWebBrowserWidget_Source_AccelByteCustomWebBrowserWidget_Public_AccelByteCustomWebBrowserWidget_h_16_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetUrl) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=P_THIS->GetUrl(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCefQuery) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_value); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=P_THIS->CefQuery(Z_Param_value); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetTitleText) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FText*)Z_Param__Result=P_THIS->GetTitleText(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execExecuteJavascript) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ScriptText); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->ExecuteJavascript(Z_Param_ScriptText); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoadString) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Contents); \
		P_GET_PROPERTY(UStrProperty,Z_Param_DummyUrl); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->LoadString(Z_Param_Contents,Z_Param_DummyUrl); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetRedirectSuccessUrl) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_NewUrl); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetRedirectSuccessUrl(Z_Param_NewUrl); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoadUrl) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_NewUrl); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->LoadUrl(Z_Param_NewUrl); \
		P_NATIVE_END; \
	}


#define ShooterGame_Plugins_AccelByteCustomWebBrowserWidget_Source_AccelByteCustomWebBrowserWidget_Public_AccelByteCustomWebBrowserWidget_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetUrl) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=P_THIS->GetUrl(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCefQuery) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_value); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=P_THIS->CefQuery(Z_Param_value); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetTitleText) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FText*)Z_Param__Result=P_THIS->GetTitleText(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execExecuteJavascript) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ScriptText); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->ExecuteJavascript(Z_Param_ScriptText); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoadString) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Contents); \
		P_GET_PROPERTY(UStrProperty,Z_Param_DummyUrl); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->LoadString(Z_Param_Contents,Z_Param_DummyUrl); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetRedirectSuccessUrl) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_NewUrl); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetRedirectSuccessUrl(Z_Param_NewUrl); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoadUrl) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_NewUrl); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->LoadUrl(Z_Param_NewUrl); \
		P_NATIVE_END; \
	}


#define ShooterGame_Plugins_AccelByteCustomWebBrowserWidget_Source_AccelByteCustomWebBrowserWidget_Public_AccelByteCustomWebBrowserWidget_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAccelByteCustomWebBrowserWidget(); \
	friend struct Z_Construct_UClass_UAccelByteCustomWebBrowserWidget_Statics; \
public: \
	DECLARE_CLASS(UAccelByteCustomWebBrowserWidget, UWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AccelByteCustomWebBrowserWidget"), NO_API) \
	DECLARE_SERIALIZER(UAccelByteCustomWebBrowserWidget)


#define ShooterGame_Plugins_AccelByteCustomWebBrowserWidget_Source_AccelByteCustomWebBrowserWidget_Public_AccelByteCustomWebBrowserWidget_h_16_INCLASS \
private: \
	static void StaticRegisterNativesUAccelByteCustomWebBrowserWidget(); \
	friend struct Z_Construct_UClass_UAccelByteCustomWebBrowserWidget_Statics; \
public: \
	DECLARE_CLASS(UAccelByteCustomWebBrowserWidget, UWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AccelByteCustomWebBrowserWidget"), NO_API) \
	DECLARE_SERIALIZER(UAccelByteCustomWebBrowserWidget)


#define ShooterGame_Plugins_AccelByteCustomWebBrowserWidget_Source_AccelByteCustomWebBrowserWidget_Public_AccelByteCustomWebBrowserWidget_h_16_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAccelByteCustomWebBrowserWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAccelByteCustomWebBrowserWidget) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAccelByteCustomWebBrowserWidget); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAccelByteCustomWebBrowserWidget); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAccelByteCustomWebBrowserWidget(UAccelByteCustomWebBrowserWidget&&); \
	NO_API UAccelByteCustomWebBrowserWidget(const UAccelByteCustomWebBrowserWidget&); \
public:


#define ShooterGame_Plugins_AccelByteCustomWebBrowserWidget_Source_AccelByteCustomWebBrowserWidget_Public_AccelByteCustomWebBrowserWidget_h_16_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAccelByteCustomWebBrowserWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAccelByteCustomWebBrowserWidget(UAccelByteCustomWebBrowserWidget&&); \
	NO_API UAccelByteCustomWebBrowserWidget(const UAccelByteCustomWebBrowserWidget&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAccelByteCustomWebBrowserWidget); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAccelByteCustomWebBrowserWidget); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAccelByteCustomWebBrowserWidget)


#define ShooterGame_Plugins_AccelByteCustomWebBrowserWidget_Source_AccelByteCustomWebBrowserWidget_Public_AccelByteCustomWebBrowserWidget_h_16_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__InitialUrl() { return STRUCT_OFFSET(UAccelByteCustomWebBrowserWidget, InitialUrl); } \
	FORCEINLINE static uint32 __PPO__RedirectSuccessUrl() { return STRUCT_OFFSET(UAccelByteCustomWebBrowserWidget, RedirectSuccessUrl); } \
	FORCEINLINE static uint32 __PPO__bSupportsTransparency() { return STRUCT_OFFSET(UAccelByteCustomWebBrowserWidget, bSupportsTransparency); }


#define ShooterGame_Plugins_AccelByteCustomWebBrowserWidget_Source_AccelByteCustomWebBrowserWidget_Public_AccelByteCustomWebBrowserWidget_h_13_PROLOG
#define ShooterGame_Plugins_AccelByteCustomWebBrowserWidget_Source_AccelByteCustomWebBrowserWidget_Public_AccelByteCustomWebBrowserWidget_h_16_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShooterGame_Plugins_AccelByteCustomWebBrowserWidget_Source_AccelByteCustomWebBrowserWidget_Public_AccelByteCustomWebBrowserWidget_h_16_PRIVATE_PROPERTY_OFFSET \
	ShooterGame_Plugins_AccelByteCustomWebBrowserWidget_Source_AccelByteCustomWebBrowserWidget_Public_AccelByteCustomWebBrowserWidget_h_16_RPC_WRAPPERS \
	ShooterGame_Plugins_AccelByteCustomWebBrowserWidget_Source_AccelByteCustomWebBrowserWidget_Public_AccelByteCustomWebBrowserWidget_h_16_INCLASS \
	ShooterGame_Plugins_AccelByteCustomWebBrowserWidget_Source_AccelByteCustomWebBrowserWidget_Public_AccelByteCustomWebBrowserWidget_h_16_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ShooterGame_Plugins_AccelByteCustomWebBrowserWidget_Source_AccelByteCustomWebBrowserWidget_Public_AccelByteCustomWebBrowserWidget_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShooterGame_Plugins_AccelByteCustomWebBrowserWidget_Source_AccelByteCustomWebBrowserWidget_Public_AccelByteCustomWebBrowserWidget_h_16_PRIVATE_PROPERTY_OFFSET \
	ShooterGame_Plugins_AccelByteCustomWebBrowserWidget_Source_AccelByteCustomWebBrowserWidget_Public_AccelByteCustomWebBrowserWidget_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	ShooterGame_Plugins_AccelByteCustomWebBrowserWidget_Source_AccelByteCustomWebBrowserWidget_Public_AccelByteCustomWebBrowserWidget_h_16_INCLASS_NO_PURE_DECLS \
	ShooterGame_Plugins_AccelByteCustomWebBrowserWidget_Source_AccelByteCustomWebBrowserWidget_Public_AccelByteCustomWebBrowserWidget_h_16_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class AccelByteCustomWebBrowserWidget."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ShooterGame_Plugins_AccelByteCustomWebBrowserWidget_Source_AccelByteCustomWebBrowserWidget_Public_AccelByteCustomWebBrowserWidget_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
