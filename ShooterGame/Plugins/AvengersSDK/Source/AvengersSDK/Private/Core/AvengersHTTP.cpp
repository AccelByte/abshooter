// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "AvengersHTTP.h"
#include "AvengersError.h"
#include "AvengersRegistry.h"
#include "AvengersSettings.h"

DEFINE_LOG_CATEGORY(LogAvengersHTTP);
namespace AccelByte
{
	void FAvengersHTTP::CreateRawRequest(const FString &URL, const FString &Verb, const FString &ContentType, const FString &Content, const AccelByte::THandler<FString>& OnSuccess, const AccelByte::FErrorHandler& OnError)
	{
		FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
		Request->SetURL(URL);
		Request->SetVerb(Verb);
		Request->SetHeader(TEXT("Content-Type"), ContentType);
		Request->SetHeader(TEXT("Accept"), APPLICATION_JSON);
		Request->SetContentAsString(Content);
		Request->OnProcessRequestComplete() = CreateHttpResultHandler(OnSuccess, OnError);
		Request->ProcessRequest();
	}

	void FAvengersHTTP::NewSession(FAvengersClientDesc Desc, const AccelByte::THandler<FAvengersMPConfigs>& OnSuccess, const AccelByte::FErrorHandler& OnError)
	{
		FString URL = FString::Printf(TEXT("%s/microprofile/sessions"), *AccelByte::FAvengersRegistry::Settings.BaseURL);
		FString Content = TEXT("");
		FJsonObjectConverter::UStructToJsonObjectString(Desc, Content, 0, 0, 0, nullptr, false);

		FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
		Request->SetURL(URL);
		Request->SetVerb(POST);
		Request->SetHeader(TEXT("Content-Type"), APPLICATION_JSON);
		Request->SetHeader(TEXT("Accept"), APPLICATION_JSON);
		Request->SetContentAsString(Content);
		Request->OnProcessRequestComplete() = CreateHttpResultHandler(OnSuccess, OnError);
		Request->ProcessRequest();
	}

	void FAvengersHTTP::RequestUploadDump(FAvengersDumpConfig Desc, const AccelByte::THandler<FAvengersDumpResponse>& OnSuccess, const AccelByte::FErrorHandler & OnError)
	{
		FString URL = FString::Printf(TEXT("%s/microprofile/dumps"), *AccelByte::FAvengersRegistry::Settings.BaseURL);
		FString Content = TEXT("");
		FJsonObjectConverter::UStructToJsonObjectString(Desc, Content, 0, 0, 0, nullptr, false);

		FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
		Request->SetURL(URL);
		Request->SetVerb(POST);
		Request->SetHeader(TEXT("Content-Type"), APPLICATION_JSON);
		Request->SetHeader(TEXT("Accept"), APPLICATION_JSON);
		Request->SetContentAsString(Content);
		Request->OnProcessRequestComplete() = CreateHttpResultHandler(OnSuccess, OnError);
		Request->ProcessRequest();
	}

	void FAvengersHTTP::SendFrametime(FAvengersFrametimeData Desc, const AccelByte::FVoidHandler & OnSuccess, const AccelByte::FErrorHandler & OnError)
	{
		FString URL = FString::Printf(TEXT("%s/data/public/namespaces/accelbyte/projectids/%s/fps/mockagentid"),
			*AccelByte::FAvengersRegistry::Settings.BaseURL,
			*AccelByte::FAvengersRegistry::Settings.ProjectID);
		FString Content = TEXT("");
		FJsonObjectConverter::UStructToJsonObjectString(Desc, Content, 0, 0, 0, nullptr, false);

		FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
		Request->SetURL(URL);
		Request->SetVerb(PUT);
		Request->SetHeader(TEXT("Content-Type"), APPLICATION_JSON);
		Request->SetContentAsString(Content);
		Request->OnProcessRequestComplete() = CreateHttpResultHandler(OnSuccess, OnError);
		Request->ProcessRequest();
	}

	void FAvengersHTTP::SendHtmlDump(FString URL, FString Content, const AccelByte::FVoidHandler& OnSuccess, const AccelByte::FErrorHandler& OnError)
	{
		FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
		Request->SetURL(URL);
		Request->SetVerb(PUT);
		Request->SetHeader(TEXT("Content-Type"), APPLICATION_OCTET);
		Request->SetContentAsString(Content);
		Request->OnProcessRequestComplete() = CreateHttpResultHandler(OnSuccess, OnError);
		Request->ProcessRequest();
	}
}