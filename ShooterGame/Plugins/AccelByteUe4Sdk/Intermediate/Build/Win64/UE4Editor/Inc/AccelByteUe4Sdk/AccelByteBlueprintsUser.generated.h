// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FAccelByteModelsUserProfileInfo;
struct FAccelByteModelsUserCreateResponse;
struct FDateTime;
struct FAccelByteModelsUserProfileInfoUpdate;
enum class EAccelBytePlatformType : uint8;
#ifdef ACCELBYTEUE4SDK_AccelByteBlueprintsUser_generated_h
#error "AccelByteBlueprintsUser.generated.h already included, missing '#pragma once' in AccelByteBlueprintsUser.h"
#endif
#define ACCELBYTEUE4SDK_AccelByteBlueprintsUser_generated_h

#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_103_DELEGATE \
static inline void FUpdateProfileSuccess_DelegateWrapper(const FScriptDelegate& UpdateProfileSuccess) \
{ \
	UpdateProfileSuccess.ProcessDelegate<UObject>(NULL); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_97_DELEGATE \
struct AccelByteBlueprintsUser_eventGetProfileSuccess_Parms \
{ \
	FAccelByteModelsUserProfileInfo UserProfileInfo; \
}; \
static inline void FGetProfileSuccess_DelegateWrapper(const FScriptDelegate& GetProfileSuccess, FAccelByteModelsUserProfileInfo const& UserProfileInfo) \
{ \
	AccelByteBlueprintsUser_eventGetProfileSuccess_Parms Parms; \
	Parms.UserProfileInfo=UserProfileInfo; \
	GetProfileSuccess.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_91_DELEGATE \
static inline void FLoginFromLauncherSuccess_DelegateWrapper(const FScriptDelegate& LoginFromLauncherSuccess) \
{ \
	LoginFromLauncherSuccess.ProcessDelegate<UObject>(NULL); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_85_DELEGATE \
static inline void FVerifyPasswordResetSuccess_DelegateWrapper(const FScriptDelegate& VerifyPasswordResetSuccess) \
{ \
	VerifyPasswordResetSuccess.ProcessDelegate<UObject>(NULL); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_79_DELEGATE \
static inline void FRequestPasswordResetSuccess_DelegateWrapper(const FScriptDelegate& RequestPasswordResetSuccess) \
{ \
	RequestPasswordResetSuccess.ProcessDelegate<UObject>(NULL); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_73_DELEGATE \
static inline void FVerifyEmailAccountSuccess_DelegateWrapper(const FScriptDelegate& VerifyEmailAccountSuccess) \
{ \
	VerifyEmailAccountSuccess.ProcessDelegate<UObject>(NULL); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_67_DELEGATE \
struct AccelByteBlueprintsUser_eventCreateEmailAccountSuccess_Parms \
{ \
	FAccelByteModelsUserCreateResponse Result; \
}; \
static inline void FCreateEmailAccountSuccess_DelegateWrapper(const FScriptDelegate& CreateEmailAccountSuccess, FAccelByteModelsUserCreateResponse const& Result) \
{ \
	AccelByteBlueprintsUser_eventCreateEmailAccountSuccess_Parms Parms; \
	Parms.Result=Result; \
	CreateEmailAccountSuccess.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_61_DELEGATE \
static inline void FUpgradeHeadlessAccountSuccess_DelegateWrapper(const FScriptDelegate& UpgradeHeadlessAccountSuccess) \
{ \
	UpgradeHeadlessAccountSuccess.ProcessDelegate<UObject>(NULL); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_52_DELEGATE \
static inline void FLoginWithDeviceIdSuccess_DelegateWrapper(const FScriptDelegate& LoginWithDeviceIdSuccess) \
{ \
	LoginWithDeviceIdSuccess.ProcessDelegate<UObject>(NULL); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_46_DELEGATE \
static inline void FLoginWithEmailAccountSuccess_DelegateWrapper(const FScriptDelegate& LoginWithEmailAccountSuccess) \
{ \
	LoginWithEmailAccountSuccess.ProcessDelegate<UObject>(NULL); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_40_DELEGATE \
static inline void FLoginWithOtherPlatformAccountSuccess_DelegateWrapper(const FScriptDelegate& LoginWithOtherPlatformAccountSuccess) \
{ \
	LoginWithOtherPlatformAccountSuccess.ProcessDelegate<UObject>(NULL); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_34_DELEGATE \
static inline void FClientLoginSuccess_DelegateWrapper(const FScriptDelegate& ClientLoginSuccess) \
{ \
	ClientLoginSuccess.ProcessDelegate<UObject>(NULL); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_32_DELEGATE \
struct AccelByteBlueprintsUser_eventBlueprintError_Parms \
{ \
	int32 ErrorCode; \
	FString ErrorMessage; \
}; \
static inline void FBlueprintError_DelegateWrapper(const FScriptDelegate& BlueprintError, int32 ErrorCode, const FString& ErrorMessage) \
{ \
	AccelByteBlueprintsUser_eventBlueprintError_Parms Parms; \
	Parms.ErrorCode=ErrorCode; \
	Parms.ErrorMessage=ErrorMessage; \
	BlueprintError.ProcessDelegate<UObject>(&Parms); \
}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_30_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetSettingsNamespace) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAccelByteBlueprintsUser::GetSettingsNamespace(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetSettingsClientSecret) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAccelByteBlueprintsUser::GetSettingsClientSecret(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetSettingsClientId) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAccelByteBlueprintsUser::GetSettingsClientId(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetSettingsServerBaseUrl) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAccelByteBlueprintsUser::GetSettingsServerBaseUrl(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserNamespace) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAccelByteBlueprintsUser::GetUserNamespace(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserDisplayName) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAccelByteBlueprintsUser::GetUserDisplayName(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserId) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAccelByteBlueprintsUser::GetUserId(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserAccessTokenExpirationUtc) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FDateTime*)Z_Param__Result=UAccelByteBlueprintsUser::GetUserAccessTokenExpirationUtc(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserRefreshToken) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAccelByteBlueprintsUser::GetUserRefreshToken(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserAccessToken) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAccelByteBlueprintsUser::GetUserAccessToken(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUpdateProfileEasy) \
	{ \
		P_GET_STRUCT_REF(FAccelByteModelsUserProfileInfoUpdate,Z_Param_Out_UpdateProfile); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::UpdateProfileEasy(Z_Param_Out_UpdateProfile,FUpdateProfileSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUpdateProfile) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_STRUCT_REF(FAccelByteModelsUserProfileInfoUpdate,Z_Param_Out_UpdateProfile); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::UpdateProfile(Z_Param_ServerBaseUrl,Z_Param_Out_UpdateProfile,FUpdateProfileSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetProfileEasy) \
	{ \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::GetProfileEasy(FGetProfileSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetProfile) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::GetProfile(Z_Param_ServerBaseUrl,FGetProfileSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoginFromLauncherEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_RedirectUri); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::LoginFromLauncherEasy(Z_Param_RedirectUri,FLoginFromLauncherSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoginFromLauncher) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientSecret); \
		P_GET_PROPERTY(UStrProperty,Z_Param_RedirectUri); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::LoginFromLauncher(Z_Param_ServerBaseUrl,Z_Param_ClientId,Z_Param_ClientSecret,Z_Param_RedirectUri,FLoginFromLauncherSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execVerifyPasswordResetEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_VerificationCode); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Email); \
		P_GET_PROPERTY(UStrProperty,Z_Param_NewPassword); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::VerifyPasswordResetEasy(Z_Param_VerificationCode,Z_Param_Email,Z_Param_NewPassword,FVerifyPasswordResetSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execVerifyPasswordReset) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientSecret); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_VerificationCode); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Email); \
		P_GET_PROPERTY(UStrProperty,Z_Param_NewPassword); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::VerifyPasswordReset(Z_Param_ServerBaseUrl,Z_Param_ClientId,Z_Param_ClientSecret,Z_Param_Namespace,Z_Param_VerificationCode,Z_Param_Email,Z_Param_NewPassword,FVerifyPasswordResetSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRequestPasswordResetEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Email); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::RequestPasswordResetEasy(Z_Param_Email,FRequestPasswordResetSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRequestPasswordReset) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientSecret); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Email); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::RequestPasswordReset(Z_Param_ServerBaseUrl,Z_Param_ClientId,Z_Param_ClientSecret,Z_Param_Namespace,Z_Param_Email,FRequestPasswordResetSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execVerifyEmailAccountEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_VerificationCode); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::VerifyEmailAccountEasy(Z_Param_UserId,Z_Param_VerificationCode,FVerifyEmailAccountSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execVerifyEmailAccount) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_VerificationCode); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::VerifyEmailAccount(Z_Param_ServerBaseUrl,Z_Param_Namespace,Z_Param_UserId,Z_Param_VerificationCode,FVerifyEmailAccountSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCreateEmailAccountEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Email); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Password); \
		P_GET_PROPERTY(UStrProperty,Z_Param_DisplayName); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::CreateEmailAccountEasy(Z_Param_Email,Z_Param_Password,Z_Param_DisplayName,FCreateEmailAccountSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCreateEmailAccount) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Email); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Password); \
		P_GET_PROPERTY(UStrProperty,Z_Param_DisplayName); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::CreateEmailAccount(Z_Param_ServerBaseUrl,Z_Param_Namespace,Z_Param_Email,Z_Param_Password,Z_Param_DisplayName,FCreateEmailAccountSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUpgradeHeadlessAccounEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Email); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Password); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::UpgradeHeadlessAccounEasy(Z_Param_Email,Z_Param_Password,FUpgradeHeadlessAccountSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUpgradeHeadlessAccount) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Email); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Password); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::UpgradeHeadlessAccount(Z_Param_ServerBaseUrl,Z_Param_Email,Z_Param_Password,FUpgradeHeadlessAccountSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execResetCredentials) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::ResetCredentials(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoginWithDeviceIdEasy) \
	{ \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::LoginWithDeviceIdEasy(FLoginWithDeviceIdSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoginWithDeviceId) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientSecret); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::LoginWithDeviceId(Z_Param_ServerBaseUrl,Z_Param_ClientId,Z_Param_ClientSecret,Z_Param_Namespace,FLoginWithDeviceIdSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoginWithEmailAccountEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Email); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Password); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::LoginWithEmailAccountEasy(Z_Param_Email,Z_Param_Password,FLoginWithEmailAccountSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoginWithEmailAccount) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientSecret); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Email); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Password); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::LoginWithEmailAccount(Z_Param_ServerBaseUrl,Z_Param_ClientId,Z_Param_ClientSecret,Z_Param_Namespace,Z_Param_Email,Z_Param_Password,FLoginWithEmailAccountSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoginWithOtherPlatformAccountEasy) \
	{ \
		P_GET_ENUM(EAccelBytePlatformType,Z_Param_PlatformId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Token); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::LoginWithOtherPlatformAccountEasy(EAccelBytePlatformType(Z_Param_PlatformId),Z_Param_Token,FLoginWithOtherPlatformAccountSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoginWithOtherPlatformAccount) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientSecret); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_ENUM(EAccelBytePlatformType,Z_Param_PlatformId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Token); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::LoginWithOtherPlatformAccount(Z_Param_ServerBaseUrl,Z_Param_ClientId,Z_Param_ClientSecret,Z_Param_Namespace,EAccelBytePlatformType(Z_Param_PlatformId),Z_Param_Token,FLoginWithOtherPlatformAccountSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execClientLoginEasy) \
	{ \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::ClientLoginEasy(FClientLoginSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execClientLogin) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientSecret); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::ClientLogin(Z_Param_ServerBaseUrl,Z_Param_ClientId,Z_Param_ClientSecret,FClientLoginSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_30_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetSettingsNamespace) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAccelByteBlueprintsUser::GetSettingsNamespace(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetSettingsClientSecret) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAccelByteBlueprintsUser::GetSettingsClientSecret(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetSettingsClientId) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAccelByteBlueprintsUser::GetSettingsClientId(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetSettingsServerBaseUrl) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAccelByteBlueprintsUser::GetSettingsServerBaseUrl(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserNamespace) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAccelByteBlueprintsUser::GetUserNamespace(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserDisplayName) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAccelByteBlueprintsUser::GetUserDisplayName(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserId) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAccelByteBlueprintsUser::GetUserId(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserAccessTokenExpirationUtc) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FDateTime*)Z_Param__Result=UAccelByteBlueprintsUser::GetUserAccessTokenExpirationUtc(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserRefreshToken) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAccelByteBlueprintsUser::GetUserRefreshToken(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetUserAccessToken) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAccelByteBlueprintsUser::GetUserAccessToken(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUpdateProfileEasy) \
	{ \
		P_GET_STRUCT_REF(FAccelByteModelsUserProfileInfoUpdate,Z_Param_Out_UpdateProfile); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::UpdateProfileEasy(Z_Param_Out_UpdateProfile,FUpdateProfileSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUpdateProfile) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_STRUCT_REF(FAccelByteModelsUserProfileInfoUpdate,Z_Param_Out_UpdateProfile); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::UpdateProfile(Z_Param_ServerBaseUrl,Z_Param_Out_UpdateProfile,FUpdateProfileSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetProfileEasy) \
	{ \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::GetProfileEasy(FGetProfileSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetProfile) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::GetProfile(Z_Param_ServerBaseUrl,FGetProfileSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoginFromLauncherEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_RedirectUri); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::LoginFromLauncherEasy(Z_Param_RedirectUri,FLoginFromLauncherSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoginFromLauncher) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientSecret); \
		P_GET_PROPERTY(UStrProperty,Z_Param_RedirectUri); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::LoginFromLauncher(Z_Param_ServerBaseUrl,Z_Param_ClientId,Z_Param_ClientSecret,Z_Param_RedirectUri,FLoginFromLauncherSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execVerifyPasswordResetEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_VerificationCode); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Email); \
		P_GET_PROPERTY(UStrProperty,Z_Param_NewPassword); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::VerifyPasswordResetEasy(Z_Param_VerificationCode,Z_Param_Email,Z_Param_NewPassword,FVerifyPasswordResetSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execVerifyPasswordReset) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientSecret); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_VerificationCode); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Email); \
		P_GET_PROPERTY(UStrProperty,Z_Param_NewPassword); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::VerifyPasswordReset(Z_Param_ServerBaseUrl,Z_Param_ClientId,Z_Param_ClientSecret,Z_Param_Namespace,Z_Param_VerificationCode,Z_Param_Email,Z_Param_NewPassword,FVerifyPasswordResetSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRequestPasswordResetEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Email); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::RequestPasswordResetEasy(Z_Param_Email,FRequestPasswordResetSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRequestPasswordReset) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientSecret); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Email); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::RequestPasswordReset(Z_Param_ServerBaseUrl,Z_Param_ClientId,Z_Param_ClientSecret,Z_Param_Namespace,Z_Param_Email,FRequestPasswordResetSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execVerifyEmailAccountEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_VerificationCode); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::VerifyEmailAccountEasy(Z_Param_UserId,Z_Param_VerificationCode,FVerifyEmailAccountSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execVerifyEmailAccount) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_UserId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_VerificationCode); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::VerifyEmailAccount(Z_Param_ServerBaseUrl,Z_Param_Namespace,Z_Param_UserId,Z_Param_VerificationCode,FVerifyEmailAccountSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCreateEmailAccountEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Email); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Password); \
		P_GET_PROPERTY(UStrProperty,Z_Param_DisplayName); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::CreateEmailAccountEasy(Z_Param_Email,Z_Param_Password,Z_Param_DisplayName,FCreateEmailAccountSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCreateEmailAccount) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Email); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Password); \
		P_GET_PROPERTY(UStrProperty,Z_Param_DisplayName); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::CreateEmailAccount(Z_Param_ServerBaseUrl,Z_Param_Namespace,Z_Param_Email,Z_Param_Password,Z_Param_DisplayName,FCreateEmailAccountSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUpgradeHeadlessAccounEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Email); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Password); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::UpgradeHeadlessAccounEasy(Z_Param_Email,Z_Param_Password,FUpgradeHeadlessAccountSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUpgradeHeadlessAccount) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Email); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Password); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::UpgradeHeadlessAccount(Z_Param_ServerBaseUrl,Z_Param_Email,Z_Param_Password,FUpgradeHeadlessAccountSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execResetCredentials) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::ResetCredentials(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoginWithDeviceIdEasy) \
	{ \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::LoginWithDeviceIdEasy(FLoginWithDeviceIdSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoginWithDeviceId) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientSecret); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::LoginWithDeviceId(Z_Param_ServerBaseUrl,Z_Param_ClientId,Z_Param_ClientSecret,Z_Param_Namespace,FLoginWithDeviceIdSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoginWithEmailAccountEasy) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_Email); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Password); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::LoginWithEmailAccountEasy(Z_Param_Email,Z_Param_Password,FLoginWithEmailAccountSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoginWithEmailAccount) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientSecret); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Email); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Password); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::LoginWithEmailAccount(Z_Param_ServerBaseUrl,Z_Param_ClientId,Z_Param_ClientSecret,Z_Param_Namespace,Z_Param_Email,Z_Param_Password,FLoginWithEmailAccountSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoginWithOtherPlatformAccountEasy) \
	{ \
		P_GET_ENUM(EAccelBytePlatformType,Z_Param_PlatformId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Token); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::LoginWithOtherPlatformAccountEasy(EAccelBytePlatformType(Z_Param_PlatformId),Z_Param_Token,FLoginWithOtherPlatformAccountSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoginWithOtherPlatformAccount) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientSecret); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Namespace); \
		P_GET_ENUM(EAccelBytePlatformType,Z_Param_PlatformId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_Token); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::LoginWithOtherPlatformAccount(Z_Param_ServerBaseUrl,Z_Param_ClientId,Z_Param_ClientSecret,Z_Param_Namespace,EAccelBytePlatformType(Z_Param_PlatformId),Z_Param_Token,FLoginWithOtherPlatformAccountSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execClientLoginEasy) \
	{ \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::ClientLoginEasy(FClientLoginSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execClientLogin) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerBaseUrl); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientId); \
		P_GET_PROPERTY(UStrProperty,Z_Param_ClientSecret); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnSuccess); \
		P_GET_PROPERTY(UDelegateProperty,Z_Param_OnError); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAccelByteBlueprintsUser::ClientLogin(Z_Param_ServerBaseUrl,Z_Param_ClientId,Z_Param_ClientSecret,FClientLoginSuccess(Z_Param_OnSuccess),FBlueprintError(Z_Param_OnError)); \
		P_NATIVE_END; \
	}


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_30_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAccelByteBlueprintsUser(); \
	friend struct Z_Construct_UClass_UAccelByteBlueprintsUser_Statics; \
public: \
	DECLARE_CLASS(UAccelByteBlueprintsUser, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AccelByteUe4Sdk"), NO_API) \
	DECLARE_SERIALIZER(UAccelByteBlueprintsUser)


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_30_INCLASS \
private: \
	static void StaticRegisterNativesUAccelByteBlueprintsUser(); \
	friend struct Z_Construct_UClass_UAccelByteBlueprintsUser_Statics; \
public: \
	DECLARE_CLASS(UAccelByteBlueprintsUser, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AccelByteUe4Sdk"), NO_API) \
	DECLARE_SERIALIZER(UAccelByteBlueprintsUser)


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_30_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAccelByteBlueprintsUser(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAccelByteBlueprintsUser) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAccelByteBlueprintsUser); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAccelByteBlueprintsUser); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAccelByteBlueprintsUser(UAccelByteBlueprintsUser&&); \
	NO_API UAccelByteBlueprintsUser(const UAccelByteBlueprintsUser&); \
public:


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_30_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAccelByteBlueprintsUser(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAccelByteBlueprintsUser(UAccelByteBlueprintsUser&&); \
	NO_API UAccelByteBlueprintsUser(const UAccelByteBlueprintsUser&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAccelByteBlueprintsUser); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAccelByteBlueprintsUser); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAccelByteBlueprintsUser)


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_30_PRIVATE_PROPERTY_OFFSET
#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_27_PROLOG
#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_30_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_30_PRIVATE_PROPERTY_OFFSET \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_30_RPC_WRAPPERS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_30_INCLASS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_30_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_30_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_30_PRIVATE_PROPERTY_OFFSET \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_30_RPC_WRAPPERS_NO_PURE_DECLS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_30_INCLASS_NO_PURE_DECLS \
	ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h_30_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ShooterGame_Plugins_AccelByteUe4Sdk_Source_AccelByteUe4Sdk_Public_Blueprints_AccelByteBlueprintsUser_h


#define FOREACH_ENUM_EACCELBYTEPLATFORMTYPE(op) \
	op(EAccelBytePlatformType::Steam) \
	op(EAccelBytePlatformType::Google) \
	op(EAccelBytePlatformType::Facebook) \
	op(EAccelBytePlatformType::Android) \
	op(EAccelBytePlatformType::iOS) \
	op(EAccelBytePlatformType::Device) \
	op(EAccelBytePlatformType::Twitch) \
	op(EAccelBytePlatformType::Oculus) \
	op(EAccelBytePlatformType::Twitter) 
PRAGMA_ENABLE_DEPRECATION_WARNINGS
