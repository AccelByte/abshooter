// Copyright (c) 2018 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.
#pragma once

#include "AccelByteError.h"
#include "Models/AccelByteItemModels.h"
#include "Models/AccelByteEntitlementModels.h"

namespace AccelByte
{
namespace Api
{

//
//@brief Entitlement API for checking user's ownership. User can query a list of item that belongs to him/her.
//
class ACCELBYTEUE4SDK_API Entitlement
{
public:
	DECLARE_DELEGATE_OneParam(FQueryUserEntitlementSuccess, const FAccelByteModelsEntitlementPagingSlicedResult&);
	/**
	 */
	static void QueryUserEntitlement(const FString & EntitlementName, const FString & ItemId, int32 Page, int32 Size, const FQueryUserEntitlementSuccess & OnSuccess, const FErrorHandler & OnError, const EAccelByteEntitlementClass & EntitlementClass, const EAccelByteAppType & AppType);

private:
	Entitlement() = delete;
	Entitlement(Entitlement const&) = delete;
	Entitlement(Entitlement&&) = delete;

	static void QueryUserEntitlementResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful, FQueryUserEntitlementSuccess OnSuccess, FErrorHandler OnError);
};

} // Namespace Api
}
