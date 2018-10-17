// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AccelByteCustomWebBrowserWidget/Public/AccelByteCustomWebBrowserWidget.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAccelByteCustomWebBrowserWidget_init() {}
	ACCELBYTECUSTOMWEBBROWSERWIDGET_API UFunction* Z_Construct_UDelegateFunction_UAccelByteCustomWebBrowserWidget_OnUrlChanged__DelegateSignature();
	ACCELBYTECUSTOMWEBBROWSERWIDGET_API UFunction* Z_Construct_UDelegateFunction_UAccelByteCustomWebBrowserWidget_OnRedirectSuccess__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_AccelByteCustomWebBrowserWidget()
	{
		static UPackage* ReturnPackage = nullptr;
		if (!ReturnPackage)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_UAccelByteCustomWebBrowserWidget_OnUrlChanged__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_UAccelByteCustomWebBrowserWidget_OnRedirectSuccess__DelegateSignature,
			};
			static const UE4CodeGen_Private::FPackageParams PackageParams = {
				"/Script/AccelByteCustomWebBrowserWidget",
				PKG_CompiledIn | 0x00000000,
				0xDBD6C434,
				0xBAC534EA,
				SingletonFuncArray, ARRAY_COUNT(SingletonFuncArray),
				METADATA_PARAMS(nullptr, 0)
			};
			UE4CodeGen_Private::ConstructUPackage(ReturnPackage, PackageParams);
		}
		return ReturnPackage;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
