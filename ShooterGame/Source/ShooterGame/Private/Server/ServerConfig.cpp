// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "ServerConfig.h"

#if UE_SERVER

#include "AccelByteOauth2Api.h"
#include "AccelByteOauth2Models.h"

//#define SERVER_CLIENT_ID "<PUT_SERVER_CLIENT_ID_HERE>"
//#define SERVER_CLIENT_SECRET "<PUT_SERVER_CLIENT_SECRET_HERE>"
#define MATCHMAKING_SERVER_URL "https://alpha.justice.accelbyte.net/matchmaking"

#ifndef SERVER_CLIENT_ID
#error Server Client Id is undefined
#endif

#ifndef SERVER_CLIENT_SECRET
#error Server Client Secret is undefined
#endif

using AccelByte::Api::Oauth2;

const FString& Coalesce(const FString& Value, const FString& DefaultValue)
{
	return Value.IsEmpty() ? DefaultValue : Value;
}

FServerConfig& FServerConfig::Get()
{
	static FServerConfig Instance;
	return Instance;
}

FServerConfig::FServerConfig()
	: ClientId{ Coalesce( FPlatformMisc::GetEnvironmentVariable(TEXT("SHOOTERGAME_SERVER_CLIENT_ID")), SERVER_CLIENT_ID) }
	, ClientSecret{ Coalesce( FPlatformMisc::GetEnvironmentVariable(TEXT("SHOOTERGAME_SERVER_CLIENT_SECRET")), SERVER_CLIENT_SECRET) }
	, MatchmakingServerUrl{ Coalesce( FPlatformMisc::GetEnvironmentVariable(TEXT("SHOOTERGAME_MATCHMAKING_SERVER_URL")), MATCHMAKING_SERVER_URL) }
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

#undef SERVER_CLIENT_ID
#undef SERVER_CLIENT_SECRET

#endif