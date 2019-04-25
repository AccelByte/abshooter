// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpResponse.h"
#include "AvengersTypes.generated.h"

/**
* @brief Describe action result.
*/
UENUM(BlueprintType)
enum class EAvengersResult : uint8
{
	OK UMETA(DisplayName = "Ok"),
	CREATED UMETA(DisplayName = "Created"),
	NO_CONTENT UMETA(DisplayName = "No Content"),

	ERROR_UNKNOWN UMETA(DisplayName = "Error: Unknown"),

	ERROR_JSON_DESERIALIZATION_FAILED UMETA(DisplayName = "Error: Json Deserialization Failed"),
	ERROR_JSON_SERIALIZATION_FAILED UMETA(DisplayName = "Error: Json Serialization Failed"),

	// HTTP
	ERROR_REQUEST_INVALID UMETA(DisplayName = "Error: Request Invalid"),
	ERROR_RESPONSE_INVALID UMETA(DisplayName = "Error: Response Invalid"), 
	
	// ERROR CODE
	ERROR_BAD_REQUEST UMETA(DisplayName = "Error: Bad Request"),
	ERROR_DENIED UMETA(DisplayName = "Error: Denied"),
	ERROR_GATEWAY_TIMEOUT UMETA(DisplayName = "Error: Gateway Timeout"),
	ERROR_NOTFOUND UMETA(DisplayName = "Error: Not Found"),
	ERROR_REQUEST_TIMEOUT UMETA(DisplayName = "Error: Request Timeout"),
	ERROR_SERVER_ERROR UMETA(DisplayName = "Error: Server Error"),
	ERROR_SERVICE_UNAVAILABLE UMETA(DisplayName = "Error: Service Unavailable"),
	ERROR_UNEXPECTED_SERVER_ERROR UMETA(DisplayName = "Error: Unexpected Server Error"),
	ERROR_NOTFOUND1 UMETA(DisplayName = "Error: Not Found"),
};

/**
* @brief Describe Avengers types function.
*/
class AVENGERSSDK_API FAvengersTypes
{
public:
	/** @brief Convert EAvengers enum to string.
	*
	* @param Result - The AvengersResult which be converted to string.
	* @return The converted of EAvengersResult enum.
	*/
	static FString AvengersResultToString(const EAvengersResult &Result)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EAvengersResult"), true);
		if (!EnumPtr) return FString("Invalid");
		return EnumPtr->GetNameByValue((int64)Result).ToString();
	}

	/** @brief Convert HttpResponseCode enum to EAvengersResult enum.
	*
	* @param  ResponseCode - The HttpResponseCode which be converted to EAvengersResult enum.
	* @return The converted of HttpResponseCode enum.
	*/
	static EAvengersResult HttpResponseCodeToResult(const int32 &ResponseCode)
	{
		switch (ResponseCode)
		{
		case EHttpResponseCodes::Ok:
		{
			return EAvengersResult::OK;
		}
		case EHttpResponseCodes::Created:
		{
			return EAvengersResult::CREATED;
		}
		case EHttpResponseCodes::NoContent:
		{
			return EAvengersResult::NO_CONTENT;
		}
		case EHttpResponseCodes::BadRequest:
		{
			return EAvengersResult::ERROR_BAD_REQUEST;
		}
		case EHttpResponseCodes::Denied:
		{
			return EAvengersResult::ERROR_DENIED;
		}
		case EHttpResponseCodes::GatewayTimeout:
		{
			return EAvengersResult::ERROR_GATEWAY_TIMEOUT;
		}
		case EHttpResponseCodes::NotFound:
		{
			return EAvengersResult::ERROR_NOTFOUND;
		}
		case EHttpResponseCodes::RequestTimeout:
		{
			return EAvengersResult::ERROR_REQUEST_TIMEOUT;
		}
		case EHttpResponseCodes::ServerError:
		{
			return EAvengersResult::ERROR_SERVER_ERROR;
		}
		case EHttpResponseCodes::ServiceUnavail:
		{
			return EAvengersResult::ERROR_SERVICE_UNAVAILABLE;
		}
		default:
			return EAvengersResult::ERROR_UNEXPECTED_SERVER_ERROR;
		}
	}

	/** @brief Convert HttpResponseCode enum to string
	*
	* @param  ResponseCode - The HttpResponseCode which be converted to string.
	* @return The converted of HttpResponseCode enum.
	*/
	static FString HttpResponseCodeToString(const int32 &ResponseCode)
	{
		switch (ResponseCode)
		{
		case EHttpResponseCodes::Ok:
		{
			return TEXT("OK");
		}
		case EHttpResponseCodes::Created:
		{
			return TEXT("Created");
		}
		case EHttpResponseCodes::NoContent:
		{
			return TEXT("No Content");
		}
		case EHttpResponseCodes::BadRequest:
		{
			return TEXT("Bad Request");
		}
		case EHttpResponseCodes::Denied:
		{
			return TEXT("Denied");
		}
		case EHttpResponseCodes::GatewayTimeout:
		{
			return TEXT("Gateway Timeout");
		}
		case EHttpResponseCodes::NotFound:
		{
			return TEXT("Not Found");
		}
		case EHttpResponseCodes::RequestTimeout:
		{
			return TEXT("Request Timeout");
		}
		case EHttpResponseCodes::ServerError:
		{
			return TEXT("Server Error");
		}
		case EHttpResponseCodes::ServiceUnavail:
		{
			return TEXT("Service Unvailable");
		}
		default:
			return TEXT("Unexpected Error");
		}
	}
};
