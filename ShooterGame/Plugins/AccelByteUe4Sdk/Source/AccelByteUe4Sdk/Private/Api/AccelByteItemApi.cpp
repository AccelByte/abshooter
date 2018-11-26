// Copyright (c) 2018 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "AccelByteItemApi.h"
#include "AccelByteError.h"
#include "JsonUtilities.h"
#include "AccelByteCredentials.h"
#include "AccelByteSettings.h"
#include "EngineMinimal.h"

namespace AccelByte
{
namespace Api
{

FString EItemTypeToString(const EAccelByteItemType& EnumValue) {
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EAccelByteItemType"), true);
	if (!EnumPtr) return "Invalid";

	return EnumPtr->GetNameStringByValue((int64)EnumValue);
}

FString EItemStatusToString(const EAccelByteItemStatus& EnumValue) {
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EAccelByteItemStatus"), true);
	if (!EnumPtr) return "Invalid";

	return EnumPtr->GetNameStringByValue((int64)EnumValue);
}

void Item::GetItemById(const FString& AccessToken, const FString& Namespace, const FString& ItemId, const FString& Language, const FString& Region, const FGetItemByIdSuccess& OnSuccess, const FErrorHandler& OnError)
{
	FString Authorization = FString::Printf(TEXT("Bearer %s"), *AccessToken);
	FString Url = FString::Printf(TEXT("%s/public/namespaces/%s/items/%s/locale"), *Settings::PlatformServerUrl, *Namespace, *ItemId);
	if (!Region.IsEmpty() || !Language.IsEmpty())
	{
		Url.Append(FString::Printf(TEXT("?")));
		if (!Region.IsEmpty())
		{
			Url.Append(FString::Printf(TEXT("region=%s"), *Region));
			if (!Language.IsEmpty())
			{
				Url.Append(FString::Printf(TEXT("&language=%s"), *Language));
			}
		}
		else if (!Language.IsEmpty())
		{
			Url.Append(FString::Printf(TEXT("language=%s"), *Language));
		}
	}

	FString Verb = TEXT("GET");
	FString ContentType = TEXT("application/json");
	FString Accept = TEXT("application/json");
	FString Content = TEXT("");

	FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(Url);
	Request->SetHeader(TEXT("Authorization"), Authorization);
	Request->SetVerb(Verb);
	Request->SetHeader(TEXT("Content-Type"), ContentType);
	Request->SetHeader(TEXT("Accept"), Accept);
	Request->SetContentAsString(Content);
	Request->OnProcessRequestComplete().BindStatic(GetItemByIdResponse, OnSuccess, OnError);
	Request->ProcessRequest();
}

void Item::GetItemByIdEasy(const FString& ItemId, const FString& Language, const FString& Region, const FGetItemByIdSuccess& OnSuccess, const FErrorHandler& OnError)
{
	GetItemById(Credentials::Get().GetUserAccessToken(), Credentials::Get().GetUserNamespace(), ItemId, Language, Region, OnSuccess, OnError);
}

void Item::GetItemsByCriteria(const FString& AccessToken, const FString& Namespace, const FString& Language, const FString& Region, const FString& CategoryPath, const EAccelByteItemType& ItemType, const EAccelByteItemStatus& Status, int32 Page, int32 Size, const FGetItemsByCriteriaSuccess& OnSuccess, const FErrorHandler& OnError)
{
	FString Authorization = FString::Printf(TEXT("Bearer %s"), *AccessToken);
	FString Url = FString::Printf(TEXT("%s/public/namespaces/%s/items/byCriteria?categoryPath=%s&language=%s&region=%s"), *Settings::PlatformServerUrl, *Namespace, *FGenericPlatformHttp::UrlEncode(CategoryPath), *Language, *Region);
	if (ItemType != EAccelByteItemType::NONE)
	{
		Url.Append(FString::Printf(TEXT("&itemType=%s"), *EItemTypeToString(ItemType)));
	}
	if (Status != EAccelByteItemStatus::NONE)
	{
		Url.Append(FString::Printf(TEXT("&status=%"), *EItemStatusToString(Status)));
	}
	Url.Append(FString::Printf(TEXT("&status=%d"), Page));
	if (Size > 0)
	{
		Url.Append(FString::Printf(TEXT("&size=%d"), Size));
	}
	FString Verb		= TEXT("GET");
	FString ContentType = TEXT("application/json");
	FString Accept		= TEXT("application/json");
	FString Content		= TEXT("");

	FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(Url);
	Request->SetHeader(TEXT("Authorization"), Authorization);
	Request->SetVerb(Verb);
	Request->SetHeader(TEXT("Content-Type"), ContentType);
	Request->SetHeader(TEXT("Accept"), Accept);
	Request->SetContentAsString(Content);
	Request->OnProcessRequestComplete().BindStatic(GetItemsByCriteriaResponse, OnSuccess, OnError);
	Request->ProcessRequest();
}

void Item::GetItemsByCriteriaEasy(const FString& Language, const FString& Region, const FString& CategoryPath, const EAccelByteItemType& ItemType, const EAccelByteItemStatus& Status, int32 Page, int32 Size, const FGetItemsByCriteriaSuccess& OnSuccess, const FErrorHandler& OnError)
{
	GetItemsByCriteria(Credentials::Get().GetUserAccessToken(), Credentials::Get().GetUserNamespace(), Language, Region, CategoryPath, ItemType, Status, Page, Size, OnSuccess, OnError);
}

// =============================================================================================================================
// ========================================================= Responses =========================================================
// =============================================================================================================================

void Item::GetItemByIdResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FGetItemByIdSuccess OnSuccess, FErrorHandler OnError)
{
	int32 Code;
	FString Message;
	FAccelByteModelsItemInfo Output;
	if (EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		if (FJsonObjectConverter::JsonObjectStringToUStruct(Response->GetContentAsString(), &Output, 0, 0))
		{
			OnSuccess.ExecuteIfBound(Output);
			return;
		}
		Code = static_cast<int32>(ErrorCodes::JsonDeserializationFailed);
	}
	HandleHttpError(Request, Response, Code, Message);
	OnError.ExecuteIfBound(Code, Message);
}

void Item::GetItemsByCriteriaResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FGetItemsByCriteriaSuccess OnSuccess, FErrorHandler OnError)
{
	int32 Code;
	FString Message;
	FAccelByteModelsItemPagingSlicedResult Output;
	if (EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		if (FJsonObjectConverter::JsonObjectStringToUStruct(Response->GetContentAsString(), &Output, 0, 0))
		{
			OnSuccess.ExecuteIfBound(Output);
			return;
		}
		Code = static_cast<int32>(ErrorCodes::JsonDeserializationFailed);
	}
	HandleHttpError(Request, Response, Code, Message);
	OnError.ExecuteIfBound(Code, Message);
}

} // Namespace Api
} // GameId AccelByte