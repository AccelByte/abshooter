// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "ServerConfig.h"

#if UE_SERVER

#include "AccelByteOauth2Api.h"
#include "AccelByteOauth2Models.h"

//#define CLIENT_ID "<PUT_CLIENT_ID_HERE>"
//#define CLIENT_SECRET "<PUT_CLIENT_SECRET_HERE>"
#define MATCHMAKING_SERVER_URL "https://alpha.justice.accelbyte.net/matchmaking"

#ifndef CLIENT_ID
#error Server Client Id is undefined
#endif

#ifndef CLIENT_SECRET
#error Server Client Secret is undefined
#endif

using AccelByte::Api::Oauth2;

FServerConfig& FServerConfig::Get()
{
	static FServerConfig Instance;
	return Instance;
}

FServerConfig::FServerConfig()
	: ClientId{ CLIENT_ID }
	, ClientSecret{ CLIENT_SECRET }
	, MatchmakingServerUrl{ MATCHMAKING_SERVER_URL }
{
	Credentials.SetClientCredentials(ClientId, ClientSecret);
}

void FServerConfig::GetClientAccessToken(const FGetClientAccessTokenSuccess& OnSuccess, const AccelByte::FErrorHandler& OnError)
{
	if (TokenExpirationTime < FPlatformTime::Seconds())
	{
		Oauth2::GetAccessTokenWithClientCredentialsGrant(ClientId, ClientSecret, Oauth2::FGetAccessTokenWithClientCredentialsGrantSuccess::CreateLambda([&, OnSuccess](const FAccelByteModelsOauth2Token& Token) {
			TokenExpirationTime = FPlatformTime::Seconds() + (Token.Expires_in*FMath::FRandRange(0.7, 0.9));
			Credentials.SetClientToken(Token.Access_token, Token.Expires_in, Token.Namespace);
			OnSuccess.ExecuteIfBound(Credentials);
		}),
			AccelByte::FErrorHandler::CreateLambda([&](int32 ErrorCode, const FString& ErrorMessage)
		{
			OnError.ExecuteIfBound(ErrorCode, ErrorMessage);
		}));
	}
	else
	{
		OnSuccess.ExecuteIfBound(Credentials);
	}
	
}

#undef CLIENT_ID
#undef CLIENT_SECRET

#endif