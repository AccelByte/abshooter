// Copyright (c) 2018 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AccelByteUserAuthenticationApi.h"
#include "AccelByteUserAuthenticationBlueprints.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UAccelByteBlueprintsUserAuthentication : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FBlueprintErrorHandler, int32, ErrorCode, FString, ErrorMessage);
	
	DECLARE_DYNAMIC_DELEGATE(FLoginWithClientCredentialsSuccess);
	UFUNCTION(BlueprintCallable, Category = "AccelByte | UserAuthentication | Api ")
    static void LoginWithClientCredentialsEasy(const FLoginWithClientCredentialsSuccess& OnSuccess, const FBlueprintErrorHandler& OnError);
	
	DECLARE_DYNAMIC_DELEGATE(FLoginWithUsernameAndPasswordSuccess);
	UFUNCTION(BlueprintCallable, Category = "AccelByte | UserAuthentication | Api ")
	static void LoginWithUsernameAndPasswordEasy(const FString& Username, const FString& Password, const FLoginWithUsernameAndPasswordSuccess& OnSuccess, const FBlueprintErrorHandler& OnError);

	DECLARE_DYNAMIC_DELEGATE(FLoginWithOtherPlatformAccountSuccess);
	UFUNCTION(BlueprintCallable, Category = "AccelByte | UserAuthentication | Api ")
    static void LoginWithOtherPlatformAccountEasy(EAccelBytePlatformType PlatformId, const FString& Token, const FLoginWithOtherPlatformAccountSuccess& OnSuccess, const FBlueprintErrorHandler& OnError);

	DECLARE_DYNAMIC_DELEGATE(FLoginWithDeviceIdSuccess);
	UFUNCTION(BlueprintCallable, Category = "AccelByte | UserAuthentication | Api ")
	static void LoginWithDeviceIdEasy(const FLoginWithDeviceIdSuccess& OnSuccess, const FBlueprintErrorHandler& OnError);
	
	UFUNCTION(BlueprintCallable, Category = "AccelByte | UserAuthentication | Api ")
	static void ForgetAllCredentials();
};