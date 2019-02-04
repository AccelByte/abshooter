// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

// compiled only for dedicated server
#if UE_SERVER

#include "AccelByteCredentials.h"
#include "AccelByteError.h"

class FServerConfig
{
public:
	DECLARE_DELEGATE_OneParam(FGetClientAccessTokenSuccess, const AccelByte::Credentials&);

	const FString ClientId;
	const FString ClientSecret;

	const FString MatchmakingServerUrl;

	AccelByte::Credentials Credentials;

	FServerConfig();

	void GetClientAccessToken(const FGetClientAccessTokenSuccess& OnSuccess, const AccelByte::FErrorHandler& OnError);

	static FServerConfig& Get();

private:
	double TokenExpirationTime{ 0 };
};
#endif