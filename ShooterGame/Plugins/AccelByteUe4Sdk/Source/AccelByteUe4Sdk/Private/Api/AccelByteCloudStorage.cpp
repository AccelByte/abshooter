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

void CloudStorage::SaveSlot(TArray<uint8> BinaryData, const FString & Tags, const FSaveSlotSuccess & OnSuccess, FHttpRequestProgressDelegate OnProgress, const FErrorHandler & OnError)
{
    FString Authorization = FString::Printf(TEXT("%s"), *Credentials::Get().GetUserAccessToken());
    FString Url = FString::Printf(TEXT("%s/namespaces/%s/users/%s/slots"), *Settings::CloudStorageServerUrl, *Credentials::Get().GetUserNamespace(), *Credentials::Get().GetUserId());
    FString Verb = TEXT("POST");
    FString Accept = TEXT("*/*");

    FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(Url);
    Request->SetHeader(TEXT("Authorization"), Authorization);
    Request->SetVerb(Verb);
    Request->SetHeader(TEXT("Accept"), Accept);
    Request->SetHeader(TEXT("Content-Type"), TEXT("multipart/form-data; boundary=WebKitFormBoundarysf3IEFIC18s0WwoY"));


    FString a = "\r\n--WebKitFormBoundarysf3IEFIC18s0WwoY\r\n";
    FString b = "Content-Disposition: form-data; name=\"file\";  filename=\"screenshot.png\"\r\n";
    FString c = "Content-Type: image/png\r\n\r\n";
    //d = UpFileRawData
    FString e = "\r\n--WebKitFormBoundarysf3IEFIC18s0WwoY--\r\n";

    TArray<uint8> data;
    data.Append((uint8*)TCHAR_TO_UTF8(*a), a.Len());
    data.Append((uint8*)TCHAR_TO_UTF8(*b), b.Len());
    data.Append((uint8*)TCHAR_TO_UTF8(*c), c.Len());
    data.Append(BinaryData);
    data.Append((uint8*)TCHAR_TO_UTF8(*e), e.Len());

    Request->SetContent(data); //or data<uint8>
    Request->OnRequestProgress() = OnProgress;
    Request->OnProcessRequestComplete().BindStatic(OnSaveSlotResponse, OnSuccess, OnError);
    Request->ProcessRequest();
    UE_LOG(LogTemp, Log, TEXT("[AccelByte] Cloud Storage Start uploading..."));
}

void CloudStorage::LoadSlot(FString SlotID, const FLoadSlotSuccess & OnSuccess, const FErrorHandler & OnError)
{
    FString Authorization = FString::Printf(TEXT("Bearer %s"), *Credentials::Get().GetUserAccessToken());
    FString Url = FString::Printf(TEXT("%s/namespaces/%s/users/%s/slots/%s"), *Settings::CloudStorageServerUrl, *Credentials::Get().GetUserNamespace(), *Credentials::Get().GetUserId(), *SlotID);
    FString Verb = TEXT("GET");
    FString ContentType = TEXT("application/json");
    FString Accept = TEXT("*/*");
    FString Content = TEXT("");

    FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(Url);
    Request->SetHeader(TEXT("Authorization"), Authorization);
    Request->SetVerb(Verb);
    Request->SetHeader(TEXT("Content-Type"), ContentType);
    Request->SetHeader(TEXT("Accept"), Accept);
    Request->SetContentAsString(Content);
    Request->OnProcessRequestComplete().BindStatic(OnLoadSlotResponse, OnSuccess, OnError);
    Request->ProcessRequest();
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
    int32 Code;
    FString Message;
    TArray<FAccelByteModelsSlot> Result;
    if (EHttpResponseCodes::IsOk(Response->GetResponseCode()))
    {
        if (FJsonObjectConverter::JsonArrayStringToUStruct(Response->GetContentAsString(), &Result, 0, 0))
        {
            OnSuccess.ExecuteIfBound(Result);
            return;
        }
        Code = static_cast<int32>(ErrorCodes::JsonDeserializationFailed);
    }
    HandleHttpError(Request, Response, Code, Message);
    OnError.ExecuteIfBound(Code, Message);
}

void CloudStorage::OnSaveSlotResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FSaveSlotSuccess OnSuccess, FErrorHandler OnError)
{
    FString ResponseText = Response->GetContentAsString();
    OnSuccess.ExecuteIfBound(ResponseText);
}

void CloudStorage::OnLoadSlotResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FLoadSlotSuccess OnSuccess, FErrorHandler OnError)
{
    if (Successful)
    {
        OnSuccess.ExecuteIfBound(Response->GetContent());
        return;
    }
    int32 Code = Response->GetResponseCode();
    FString Message;
    HandleHttpError(Request, Response, Code, Message);
    OnError.ExecuteIfBound(Code, Message);
}

void CloudStorage::OnUpdateSlotResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FSaveSlotSuccess OnSuccess, FErrorHandler OnError)
{
}

}
}