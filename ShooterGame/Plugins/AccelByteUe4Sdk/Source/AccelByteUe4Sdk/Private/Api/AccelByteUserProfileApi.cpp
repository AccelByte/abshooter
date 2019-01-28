// Copyright (c) 2018 - 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "AccelByteUserProfileApi.h"
#include "AccelByteOauth2Api.h"
#include "JsonUtilities.h"
#include "AccelByteRegistry.h"

namespace AccelByte
{
namespace Api
{

void UserProfile::GetUserProfile(const FGetUserProfileSuccess& OnSuccess, const FErrorHandler& OnError)
{
	FString Authorization = FString::Printf(TEXT("Bearer %s"), *FRegistry::Credentials.GetUserAccessToken());
	FString Url = FString::Printf(TEXT("%s/public/namespaces/%s/users/me/profiles"), *FRegistry::Settings.BasicServerUrl, *FRegistry::Credentials.GetUserNamespace());
	FString Verb = TEXT("GET");
	FString ContentType = TEXT("application/json");
	FString Accept = TEXT("application/json");
	FString Content;

	FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(Url);
	Request->SetHeader(TEXT("Authorization"), Authorization);
	Request->SetVerb(Verb);
	Request->SetHeader(TEXT("Content-Type"), ContentType);
	Request->SetHeader(TEXT("Accept"), Accept);
	Request->SetContentAsString(Content);
	Request->OnProcessRequestComplete().BindStatic(GetUserProfileResponse, OnSuccess, OnError);
	Request->ProcessRequest();
}

void UserProfile::GetPublicUserProfileInfo(FString UserID, const FGetPublicUserProfileInfoSuccess& OnSuccess, const FErrorHandler& OnError)
{
    FString Authorization = FString::Printf(TEXT("Bearer %s"), *FRegistry::Credentials.GetUserAccessToken());
    FString Url = FString::Printf(TEXT("%s/public/namespaces/%s/users/%s/profiles/public"), *FRegistry::Settings.BasicServerUrl, *FRegistry::Credentials.GetUserNamespace(), *UserID);
    FString Verb = TEXT("GET");
    FString ContentType = TEXT("application/json");
    FString Accept = TEXT("application/json");
    FString Content;

    FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(Url);
    Request->SetHeader(TEXT("Authorization"), Authorization);
    Request->SetVerb(Verb);
    Request->SetHeader(TEXT("Content-Type"), ContentType);
    Request->SetHeader(TEXT("Accept"), Accept);
    //Request->SetContentAsString(Content);
    Request->OnProcessRequestComplete().BindStatic(GetPublicUserProfileInfoResponse, OnSuccess, OnError);
    Request->ProcessRequest();
}


void UserProfile::UpdateUserProfile(const FAccelByteModelsUserProfileUpdateRequest& ProfileUpdateRequest, const FUpdateUserProfileSuccess& OnSuccess, const FErrorHandler& OnError)
{
	FString Authorization = FString::Printf(TEXT("Bearer %s"), *FRegistry::Credentials.GetUserAccessToken());
	FString Url = FString::Printf(TEXT("%s/public/namespaces/%s/users/%s/profiles"), *FRegistry::Settings.BasicServerUrl, *FRegistry::Credentials.GetUserNamespace(), *FRegistry::Credentials.GetUserId());
	FString Verb = TEXT("PUT");
	FString ContentType = TEXT("application/json");
	FString Accept = TEXT("application/json");
	FString Content;
	FJsonObjectConverter::UStructToJsonObjectString(ProfileUpdateRequest, Content);

	FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(Url);
	Request->SetHeader(TEXT("Authorization"), Authorization);
	Request->SetVerb(Verb);
	Request->SetHeader(TEXT("Content-Type"), ContentType);
	Request->SetHeader(TEXT("Accept"), Accept);
	Request->SetContentAsString(Content);
	Request->OnProcessRequestComplete().BindStatic(UpdateUserProfileResponse, OnSuccess, OnError);
	Request->ProcessRequest();
}

void UserProfile::CreateUserProfile(const FAccelByteModelsUserProfileCreateRequest& ProfileCreateRequest, const FCreateUserProfileSuccess& OnSuccess, const FErrorHandler& OnError)
{
	FString Authorization = FString::Printf(TEXT("Bearer %s"), *FRegistry::Credentials.GetUserAccessToken());
	FString Url = FString::Printf(TEXT("%s/public/namespaces/%s/users/%s/profiles"), *FRegistry::Settings.BasicServerUrl, *FRegistry::Credentials.GetUserNamespace(), *FRegistry::Credentials.GetUserId());
	FString Verb = TEXT("POST");
	FString ContentType = TEXT("application/json");
	FString Accept = TEXT("application/json");
	FString Content;
	FJsonObjectConverter::UStructToJsonObjectString(ProfileCreateRequest, Content);

	FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(Url);
	Request->SetHeader(TEXT("Authorization"), Authorization);
	Request->SetVerb(Verb);
	Request->SetHeader(TEXT("Content-Type"), ContentType);
	Request->SetHeader(TEXT("Accept"), Accept);
	Request->SetContentAsString(Content);
	Request->OnProcessRequestComplete().BindStatic(CreateUserProfileResponse, OnSuccess, OnError);
	Request->ProcessRequest();
}

void UserProfile::CreateDefaultUserProfile(FString DisplayName, const FCreateUserProfileSuccess& OnSuccess, const FErrorHandler& OnError)
{
    FString Authorization = FString::Printf(TEXT("Bearer %s"), *FRegistry::Credentials.GetUserAccessToken());
    FString Url = FString::Printf(TEXT("%s/public/namespaces/%s/users/%s/profiles"), *FRegistry::Settings.BasicServerUrl, *FRegistry::Credentials.GetUserNamespace(), *FRegistry::Credentials.GetUserId());
    FString Verb = TEXT("POST");
    FString ContentType = TEXT("application/json");
    FString Accept = TEXT("application/json");
    FString Content = FString::Printf(TEXT("{\"firstName\":\"%s\",\"avatarSmallUrl\":\"https://s3-us-west-2.amazonaws.com/justice-platform-service/avatar.jpg\",\"avatarUrl\":\"https://s3-us-west-2.amazonaws.com/justice-platform-service/avatar.jpg\",\"avatarLargeUrl\":\"https://s3-us-west-2.amazonaws.com/justice-platform-service/avatar.jpg\"}"), *DisplayName);

    FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(Url);
    Request->SetHeader(TEXT("Authorization"), Authorization);
    Request->SetVerb(Verb);
    Request->SetHeader(TEXT("Content-Type"), ContentType);
    Request->SetHeader(TEXT("Accept"), Accept);
    Request->SetContentAsString(Content);
    Request->OnProcessRequestComplete().BindStatic(CreateUserProfileResponse, OnSuccess, OnError);
    Request->ProcessRequest();
}

void UserProfile::CreateEntitlementReceiver(FString UserID, FString ExternalUserID, FString Content, const FCreateEntitlementReceiverSuccess & OnSuccess, const FErrorHandler & OnError)
{
    FString Authorization = FString::Printf(TEXT("Bearer %s"), *FRegistry::Credentials.GetUserAccessToken());
    FString Url = FString::Printf(TEXT("%s/public/namespaces/%s/users/%s/entitlements/receivers/%s"), *FRegistry::Settings.PlatformServerUrl, *FRegistry::Settings.Namespace, *UserID, *ExternalUserID);
    FString Verb = TEXT("POST");
    FString ContentType = TEXT("application/json");
    FString Accept = TEXT("application/json");        

    FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(Url);
    Request->SetHeader(TEXT("Authorization"), Authorization);
    Request->SetVerb(Verb);
    Request->SetHeader(TEXT("Content-Type"), ContentType);
    Request->SetHeader(TEXT("Accept"), Accept);
    Request->SetContentAsString(Content);
    Request->OnProcessRequestComplete().BindStatic(CreateEntitlementReceiverResponse, OnSuccess, OnError);
    Request->ProcessRequest();
}

// =============================================================================================================================
// ========================================================= Responses =========================================================
// =============================================================================================================================

void UserProfile::GetUserProfileResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FGetUserProfileSuccess OnSuccess, FErrorHandler OnError)
{
	int32 Code;
	FString Message;
	if (EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		FAccelByteModelsUserProfileInfo Result;
		FJsonObjectConverter::JsonObjectStringToUStruct(Response->GetContentAsString(), &Result, 0, 0);
		OnSuccess.ExecuteIfBound(Result);
		return;
	}
	HandleHttpError(Request, Response, Code, Message);
	OnError.ExecuteIfBound(Code, Message);
}

void UserProfile::GetPublicUserProfileInfoResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FGetPublicUserProfileInfoSuccess OnSuccess, FErrorHandler OnError)
{
    int32 Code;
    FString Message;
    if (EHttpResponseCodes::IsOk(Response->GetResponseCode()))
    {
        FAccelByteModelsPublicUserProfileInfo Result;
        FJsonObjectConverter::JsonObjectStringToUStruct(Response->GetContentAsString(), &Result, 0, 0);
        OnSuccess.ExecuteIfBound(Result);
        return;
    }
    HandleHttpError(Request, Response, Code, Message);
    OnError.ExecuteIfBound(Code, Message);
}

void UserProfile::UpdateUserProfileResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FUpdateUserProfileSuccess OnSuccess, FErrorHandler OnError)
{
	int32 Code;
	FString Message;
	if (EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		OnSuccess.ExecuteIfBound();
		return;
	}
	HandleHttpError(Request, Response, Code, Message);
	OnError.ExecuteIfBound(Code, Message);
}

void UserProfile::CreateUserProfileResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FCreateUserProfileSuccess OnSuccess, FErrorHandler OnError)
{
	int32 Code;
	FString Message;
	if (EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		FAccelByteModelsUserProfileInfo Result;
		FJsonObjectConverter::JsonObjectStringToUStruct(Response->GetContentAsString(), &Result, 0, 0);
		OnSuccess.ExecuteIfBound(Result);
		return;
	}
	HandleHttpError(Request, Response, Code, Message);
	OnError.ExecuteIfBound(Code, Message);
}

void UserProfile::CreateEntitlementReceiverResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FCreateEntitlementReceiverSuccess OnSuccess, FErrorHandler OnError)
{
    int32 Code;
    FString Message;
    if (EHttpResponseCodes::IsOk(Response->GetResponseCode()))
    {
        //FAccelByteModelsUserProfileInfo Result;
        //FJsonObjectConverter::JsonObjectStringToUStruct(Response->GetContentAsString(), &Result, 0, 0);
        OnSuccess.ExecuteIfBound(Response->GetContentAsString());
        return;
    }
    HandleHttpError(Request, Response, Code, Message);
    OnError.ExecuteIfBound(Code, Message);
}

} // Namespace Api
} // Namespace AccelByte
