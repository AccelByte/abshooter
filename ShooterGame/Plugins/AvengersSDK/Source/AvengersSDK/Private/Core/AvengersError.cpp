// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "AvengersError.h"

namespace AccelByte
{

const std::unordered_map<std::underlying_type<ErrorCodes>::type, FString> AvengersErrorMessages::Default
{
    // HTTP 1xx
    { static_cast<int32>(ErrorCodes::StatusContinue), TEXT("StatusContinue Reference: RFC 7231, Section 6.2.1") },
    { static_cast<int32>(ErrorCodes::StatusSwitchingProtocols), TEXT("StatusSwitchingProtocols Reference: RFC 7231, Section 6.2.2") },
    { static_cast<int32>(ErrorCodes::StatusProcessing), TEXT("StatusProcessing Reference: RFC 2518, Section 10.1") },
    
    // HTTP 2xx
    { static_cast<int32>(ErrorCodes::StatusOk), TEXT("StatusOk Reference: RFC 7231, Section 6.3.1") },
    { static_cast<int32>(ErrorCodes::StatusCreated), TEXT("StatusCreated Reference: RFC 7231, Section 6.3.2") },
    { static_cast<int32>(ErrorCodes::StatusAccepted), TEXT("StatusAccepted Reference: RFC 7231, Section 6.3.3") },
    { static_cast<int32>(ErrorCodes::StatusNonAuthoritativeInfo), TEXT("StatusNonAuthoritativeInfo Reference: RFC 7231, Section 6.3.4") },
    { static_cast<int32>(ErrorCodes::StatusNoContent), TEXT("StatusNoContent Reference: RFC 7231, Section 6.3.5") },
    { static_cast<int32>(ErrorCodes::StatusResetContent), TEXT("StatusResetContent Reference: RFC 7231, Section 6.3.6") },
    { static_cast<int32>(ErrorCodes::StatusPartialContent), TEXT("StatusPartialContent Reference: RFC 7233, Section 4.1") },
    { static_cast<int32>(ErrorCodes::StatusMultiStatus), TEXT("StatusMultiStatus Reference: RFC 4918, Section 11.1") },
    { static_cast<int32>(ErrorCodes::StatusAlreadyReported), TEXT("StatusAlreadyReported Reference: RFC 5842, Section 7.1") },
    { static_cast<int32>(ErrorCodes::StatusImUsed), TEXT("StatusImUsed Reference: RFC 3229, Section 10.4.1") },
    
    // HTTP 3xx
    { static_cast<int32>(ErrorCodes::StatusMultipleChoices), TEXT("StatusMultipleChoices Reference: RFC 7231, Section 6.4.1") },
    { static_cast<int32>(ErrorCodes::StatusMovedPermanently), TEXT("StatusMovedPermanently Reference: RFC 7231, Section 6.4.2") },
    { static_cast<int32>(ErrorCodes::StatusFound), TEXT("StatusFound Reference: RFC 7231, Section 6.4.3") },
    { static_cast<int32>(ErrorCodes::StatusSeeOther), TEXT("StatusSeeOther Reference: RFC 7231, Section 6.4.4") },
    { static_cast<int32>(ErrorCodes::StatusNotModified), TEXT("StatusNotModified Reference: RFC 7232, Section 4.1") },
    { static_cast<int32>(ErrorCodes::StatusUseProxy), TEXT("StatusUseProxy Reference: RFC 7231, Section 6.4.5") },

    { static_cast<int32>(ErrorCodes::StatusTemporaryRedirect), TEXT("StatusTemporaryRedirect Reference: RFC 7231, Section 6.4.7") },
    { static_cast<int32>(ErrorCodes::StatusPermanentRedirect), TEXT("StatusPermanentRedirect Reference: RFC 7538, Section 3") },
    
    // HTTP 4xx
    { static_cast<int32>(ErrorCodes::StatusBadRequest), TEXT("StatusBadRequest Reference: RFC 7231, Section 6.5.1") },
    { static_cast<int32>(ErrorCodes::StatusUnauthorized), TEXT("StatusUnauthorized Reference: RFC 7235, Section 3.1") },
    { static_cast<int32>(ErrorCodes::StatusPaymentRequired), TEXT("StatusPaymentRequired Reference: RFC 7231, Section 6.5.2") },
    { static_cast<int32>(ErrorCodes::StatusForbidden), TEXT("StatusForbidden Reference: RFC 7231, Section 6.5.3") },
    { static_cast<int32>(ErrorCodes::StatusNotFound), TEXT("StatusNotFound Reference: RFC 7231, Section 6.5.4") },
    { static_cast<int32>(ErrorCodes::StatusMethodNotAllowed), TEXT("StatusMethodNotAllowed Reference: RFC 7231, Section 6.5.5") },
    { static_cast<int32>(ErrorCodes::StatusNotAcceptable), TEXT("StatusNotAcceptable Reference: RFC 7231, Section 6.5.6") },
    { static_cast<int32>(ErrorCodes::StatusProxyAuthRequired), TEXT("StatusProxyAuthRequired Reference: RFC 7235, Section 3.2") },
    { static_cast<int32>(ErrorCodes::StatusRequestTimeout), TEXT("StatusRequestTimeout Reference: RFC 7231, Section 6.5.7") },
    { static_cast<int32>(ErrorCodes::StatusConflict), TEXT("StatusConflict Reference: RFC 7231, Section 6.5.8") },
    { static_cast<int32>(ErrorCodes::StatusGone), TEXT("StatusGone Reference: RFC 7231, Section 6.5.9") },
    { static_cast<int32>(ErrorCodes::StatusLengthRequired), TEXT("StatusLengthRequired Reference: RFC 7231, Section 6.5.10") },
    { static_cast<int32>(ErrorCodes::StatusPreconditionFailed), TEXT("StatusPreconditionFailed Reference: RFC 7232, Section 4.2") },
    { static_cast<int32>(ErrorCodes::StatusRequestEntityTooLarge), TEXT("StatusRequestEntityTooLarge Reference: RFC 7231, Section 6.5.11") },
    { static_cast<int32>(ErrorCodes::StatusRequestUriTooLong), TEXT("StatusRequestUriTooLong Reference: RFC 7231, Section 6.5.12") },
    { static_cast<int32>(ErrorCodes::StatusUnsupportedMediaType), TEXT("StatusUnsupportedMediaType Reference: RFC 7231, Section 6.5.13") },
    { static_cast<int32>(ErrorCodes::StatusRequestedRangeNotSatisfiable), TEXT("StatusRequestedRangeNotSatisfiable Reference: RFC 7233, Section 4.4") },
    { static_cast<int32>(ErrorCodes::StatusExpectationFailed), TEXT("StatusExpectationFailed Reference: RFC 7231, Section 6.5.14") },
    { static_cast<int32>(ErrorCodes::StatusTeapot), TEXT("StatusTeapot Reference: RFC 7168, Section 2.3.3") },
    { static_cast<int32>(ErrorCodes::StatusMisdirectedRequest), TEXT("StatusMisdirectedRequest Reference: RFC 7540, Section 9.1.2") },
    { static_cast<int32>(ErrorCodes::StatusUnprocessableEntity), TEXT("StatusUnprocessableEntity Reference: RFC 4918, Section 11.2") },
    { static_cast<int32>(ErrorCodes::StatusLocked), TEXT("StatusLocked Reference: RFC 4918, Section 11.3") },
    { static_cast<int32>(ErrorCodes::StatusFailedDependency), TEXT("StatusFailedDependency Reference: RFC 4918, Section 11.4") },
    { static_cast<int32>(ErrorCodes::StatusUpgradeRequired), TEXT("StatusUpgradeRequired Reference: RFC 7231, Section 6.5.15") },
    { static_cast<int32>(ErrorCodes::StatusPreconditionRequired), TEXT("StatusPreconditionRequired Reference: RFC 6585, Section 3") },
    { static_cast<int32>(ErrorCodes::StatusTooManyRequests), TEXT("StatusTooManyRequests Reference: RFC 6585, Section 4") },
    { static_cast<int32>(ErrorCodes::StatusRequestHeaderFieldsTooLarge), TEXT("StatusRequestHeaderFieldsTooLarge Reference: RFC 6585, Section 5") },
    { static_cast<int32>(ErrorCodes::StatusUnavailableForLegalReasons), TEXT("StatusUnavailableForLegalReasons Reference: RFC 7725, Section 3") },
    
    // HTTP 5xx
    { static_cast<int32>(ErrorCodes::StatusInternalServerError), TEXT("StatusInternalServerError Reference: RFC 7231, Section 6.6.1") },
    { static_cast<int32>(ErrorCodes::StatusNotImplemented), TEXT("StatusNotImplemented Reference: RFC 7231, Section 6.6.2") },
    { static_cast<int32>(ErrorCodes::StatusBadGateway), TEXT("StatusBadGateway Reference: RFC 7231, Section 6.6.3") },
    { static_cast<int32>(ErrorCodes::StatusServiceUnavailable), TEXT("StatusServiceUnavailable Reference: RFC 7231, Section 6.6.4") },
    { static_cast<int32>(ErrorCodes::StatusGatewayTimeout), TEXT("StatusGatewayTimeout Reference: RFC 7231, Section 6.6.5") },
    { static_cast<int32>(ErrorCodes::StatusHttpVersionNotSupported), TEXT("StatusHttpVersionNotSupported Reference: RFC 7231, Section 6.6.6") },
    { static_cast<int32>(ErrorCodes::StatusVariantAlsoNegotiates), TEXT("StatusVariantAlsoNegotiates Reference: RFC 2295, Section 8.1") },
    { static_cast<int32>(ErrorCodes::StatusInsufficientStorage), TEXT("StatusInsufficientStorage Reference: RFC 4918, Section 11.5") },
    { static_cast<int32>(ErrorCodes::StatusLoopDetected), TEXT("StatusLoopDetected Reference: RFC 5842, Section 7.2") },
    { static_cast<int32>(ErrorCodes::StatusNotExtended), TEXT("StatusNotExtended Reference: RFC 2774, Section 7") },
    { static_cast<int32>(ErrorCodes::StatusNetworkAuthenticationRequired), TEXT("StatusNetworkAuthenticationRequired Reference: RFC 6585, Section 6") },

};

void AvengersHandleHttpError(FHttpRequestPtr Request, FHttpResponsePtr Response, int& OutCode, FString& OutMessage)
{
    FAvengersErrorInfo Error;
    int32 Code = 0;
    OutMessage = "";
    if (Response.IsValid())
    {
        if (FJsonObjectConverter::JsonObjectStringToUStruct(Response->GetContentAsString(), &Error, 0, 0) && Error.NumericErrorCode != -1)
        {
            Code = Error.NumericErrorCode;
        }
        else
        {
            Code = Response->GetResponseCode();
        }
    }
    else
    {
        Code = (int32)ErrorCodes::NetworkError;
    }

    auto it = AvengersErrorMessages::Default.find(Code);
    if (it != AvengersErrorMessages::Default.cend())
    {
        OutMessage += AvengersErrorMessages::Default.at(Code);
    }

    if (!Error.ErrorMessage.IsEmpty())
    {
        OutMessage += " " + Error.ErrorMessage;
    }
    
    // Debug message. Delete this code section for production
#if 0
    OutMessage += "\n\nResponse";
    OutMessage += "\nCode: " + FString::FromInt(Response->GetResponseCode());
    OutMessage += "\nContent: \n" + Response->GetContentAsString();

    OutMessage += " \n\nRequest";
    OutMessage += "\nElapsed time (seconds): " + FString::SanitizeFloat(Request->GetElapsedTime());
    OutMessage += "\nVerb: " + Request->GetVerb();
    OutMessage += "\nURL: " + Request->GetURL();
    OutMessage += "\nHeaders: \n";
    for (auto a : Request->GetAllHeaders())
    {
        OutMessage += a + "\n";
    }
    OutMessage += "\nContent: \n";
    for (auto a : Request->GetContent())
    {
        OutMessage += static_cast<char>(a);
    }
    OutMessage += "\n";
#endif
    OutCode = Code;
}
} // Namespace AccelByte

