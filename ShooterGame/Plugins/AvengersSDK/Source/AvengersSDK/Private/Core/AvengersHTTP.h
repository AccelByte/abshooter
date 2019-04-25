// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.

#pragma once

#include "Models/AvengersHTTPResponse.h"
#include "Models/AvengersClientDesc.h"
#include "Models/AvengersMPConfigs.h"
#include "Models/AvengersDumpConfig.h"
#include "Models/AvengersDumpResponse.h"
#include "Models/AvengersFrametimeData.h"

#include "Core/AvengersError.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAvengersHTTP, Log, All);

#define APPLICATION_JSON TEXT("application/json")
#define APPLICATION_OCTET TEXT("application/octet-stream")

#define POST TEXT("POST")
#define PUT TEXT("PUT")

namespace AccelByte
{
	/**
	* @brief Describe Avengers Http.
	*/
	class FAvengersHTTP
	{
	public:
		/** @brief Create a request.
		*
		* @param URL - URL used to send the request.
		* @param Verb - Method of the request.
		* @param ContentType - Type of the payload of the request.
		* @param Content - Payload of the request.
		* @param OnResponsePtr - Process the response.
		* @return EAvengersResult::OK if it is success or failure otherwise.
		*/
		static void CreateRawRequest(const FString &URL, const FString &Verb, const FString &ContentType, const FString &Content, const AccelByte::THandler<FString>& OnSuccess, const AccelByte::FErrorHandler& OnError);

		// new SDK

		static void NewSession(FAvengersClientDesc Desc, const AccelByte::THandler<FAvengersMPConfigs>& OnSuccess, const AccelByte::FErrorHandler& OnError);

		static void RequestUploadDump(FAvengersDumpConfig Desc, const AccelByte::THandler<FAvengersDumpResponse>& OnSuccess, const AccelByte::FErrorHandler& OnError);

		static void SendFrametime(FAvengersFrametimeData Desc, const AccelByte::FVoidHandler& OnSuccess, const AccelByte::FErrorHandler& OnError);

		static void SendHtmlDump(FString URL, FString Content, const AccelByte::FVoidHandler& OnSuccess, const AccelByte::FErrorHandler& OnError);

	};
}
