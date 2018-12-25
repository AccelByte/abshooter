// Copyright (c) 2018 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "AccelByteCloudStorage.h"
#include "AccelByteError.h"
#include "JsonUtilities.h"
#include "AccelByteSettings.h"
#include "AccelByteCredentials.h"

namespace AccelByte
{
namespace Api
{

void CloudStorage::IntializeSlots(const int32 SlotCount, const FCreateSlotsSuccess& OnSuccess, const FErrorHandler& OnError)
{
	FString Authorization = FString::Printf(TEXT("Bearer %s"), *Credentials::Get().GetUserAccessToken());
	FString Url				= FString::Printf(TEXT("%s/config/namespaces/%s/users/%s"), *Settings::CloudStorageServerUrl, *Credentials::Get().GetUserNamespace(), *Credentials::Get().GetUserId());
	FString Verb			= TEXT("POST");
	FString ContentType		= TEXT("application/json");
	FString Accept			= TEXT("application/json");
	FString Content			= TEXT("");

	FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(Url);
	Request->SetHeader(TEXT("Authorization"), Authorization);
	Request->SetVerb(Verb);
	Request->SetHeader(TEXT("Content-Type"), ContentType);
	Request->SetHeader(TEXT("Accept"), Accept);
	Request->SetContentAsString(Content);
	Request->OnProcessRequestComplete().BindStatic(OnIntializeSlotsResponse, OnSuccess, OnError);
	Request->ProcessRequest();
}


void CloudStorage::GetAllSlot(const FGetAllSlotsSuccess& OnSuccess, const FErrorHandler& OnError)
{
	FString Authorization = FString::Printf(TEXT("Bearer %s"), *Credentials::Get().GetUserAccessToken());
	FString Url				= FString::Printf(TEXT("%s/namespaces/%s/users/%s/slots"), *Settings::CloudStorageServerUrl, *Credentials::Get().GetUserNamespace(), *Credentials::Get().GetUserId());
	FString Verb			= TEXT("GET");
	FString ContentType		= TEXT("application/json");
	FString Accept			= TEXT("application/json");
	FString Content			= TEXT("");

	FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(Url);
	Request->SetHeader(TEXT("Authorization"), Authorization);
	Request->SetVerb(Verb);
	Request->SetHeader(TEXT("Content-Type"), ContentType);
	Request->SetHeader(TEXT("Accept"), Accept);
	Request->SetContentAsString(Content);
	Request->OnProcessRequestComplete().BindStatic(OnGetAllSlotResponse, OnSuccess, OnError);
	Request->ProcessRequest();
}

void CloudStorage::SaveSlot(const TArray<uint8> BinaryData, const FString & Tags, const FSaveSlotSuccess & OnSuccess, FHttpRequestProgressDelegate OnProgress, const FErrorHandler & OnError)
{
    FString Authorization = FString::Printf(TEXT("Bearer %s"), *Credentials::Get().GetUserAccessToken());
    FString Url = FString::Printf(TEXT("%s/namespaces/%s/users/%s/slots"), *Settings::CloudStorageServerUrl, *Credentials::Get().GetUserNamespace(), *Credentials::Get().GetUserId());
    FString Verb = TEXT("POST");
    FString ContentType = TEXT("application/octet-stream");
    FString Accept = TEXT("application/json");

    FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(Url);
    Request->SetHeader(TEXT("Authorization"), Authorization);
    Request->SetVerb(Verb);
    Request->SetHeader(TEXT("Content-Type"), ContentType);
    Request->SetHeader(TEXT("Accept"), Accept);
    Request->SetContent(BinaryData);
    Request->OnRequestProgress() = OnProgress;
    Request->OnProcessRequestComplete().BindStatic(OnSaveSlotResponse, OnSuccess, OnError);
    Request->ProcessRequest();
}

void CloudStorage::LoadSlot(FString SlotID, const FLoadSlotSuccess & OnSuccess, const FErrorHandler & OnError)
{
}

void CloudStorage::UpdateSlot(FString SlotID, const TArray<uint8> BinaryData, const FString & Tags, const FSaveSlotSuccess & OnSuccess, const FErrorHandler & OnError)
{
}



// Response

void CloudStorage::OnIntializeSlotsResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FCreateSlotsSuccess OnSuccess, FErrorHandler OnError)
{
}

void CloudStorage::OnGetAllSlotResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FGetAllSlotsSuccess OnSuccess, FErrorHandler OnError)
{
}

void CloudStorage::OnSaveSlotResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FSaveSlotSuccess OnSuccess, FErrorHandler OnError)
{
    UE_LOG(LogTemp, Log, TEXT("OnSaveSlot Respnse:%s"), *Response->GetContentAsString());
    OnSuccess.ExecuteIfBound("");
}

void CloudStorage::OnLoadSlotResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FLoadSlotSuccess OnSuccess, FErrorHandler OnError)
{
}

void CloudStorage::OnUpdateSlotResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FSaveSlotSuccess OnSuccess, FErrorHandler OnError)
{
}

}
}