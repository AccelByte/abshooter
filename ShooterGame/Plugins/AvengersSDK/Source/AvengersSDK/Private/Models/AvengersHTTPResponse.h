// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HAL/ThreadSafeCounter.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Core/AvengersTypes.h"

/**
* @brief Describe Avengers Http response.
*/
struct FAvengersHttpResponse
{
	FString RequestContentType; /**< Stores the type of payload of the response. */
	FString RequestContent; /**< Stores the payload of the response. */
	FHttpRequestPtr Request; /**< Stores the request as pointer. */
	FHttpResponsePtr Response; /**< Stores the response as pointer. */
	EAvengersResult Result; /**< Stores the EAvengersResult enum of the response. */
};
typedef TSharedPtr<FAvengersHttpResponse, ESPMode::ThreadSafe> FAvengersResponsePtr;
DECLARE_DELEGATE_OneParam(FAvengersResponseDelegate, const FAvengersResponsePtr &);
