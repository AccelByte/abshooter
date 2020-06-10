// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#include "ShooterGameSteamUtility.h"

// Steam
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystemSteam.h"
/*
*    This is added so we can compile for Linux
*
*    Taken from: https://answers.unrealengine.com/questions/170549/engine-wont-compile-with-steamworks-132-latest.html
*/
#pragma push_macro("ARRAY_COUNT")
#undef ARRAY_COUNT
// Prevents deprecated messages for steam header
#pragma warning(push)
#pragma warning(disable : 4996)
#include <steam/steam_api.h>
// Bring deprecated warnings back
#pragma warning(pop)
#pragma pop_macro("ARRAY_COUNT")
/*
*    Above is added so we can compile for Linux
*/

// AccelByte
#include "AccelByteOauth2Api.h"
#include "Core/AccelByteRegistry.h"
#include "AccelByteUserApi.h"
#include "ShooterGameConfig.h"

void ExecuteErrorDelegate(const AccelByte::FErrorHandler& OnErrorExt, int Code, FString Reason)
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *Reason);
	OnErrorExt.ExecuteIfBound(Code, Reason);
}

void ShooterGameSteamUtility::SteamLogin(FVoidHandler OnSuccess, AccelByte::FErrorHandler OnError)
{
	auto OSS = static_cast<FOnlineSubsystemSteam*>(IOnlineSubsystem::Get(STEAM_SUBSYSTEM));
	if (OSS)
	{
		OSS->GetIdentityInterface()->AddOnLoginCompleteDelegate_Handle(
			0,
			FOnLoginCompleteDelegate::CreateStatic(&OnIdentityLoginComplete, OnSuccess, OnError));

		FOnlineAccountCredentials NewAccount;
		NewAccount.Id = ShooterGameConfig::Get().SteamAppID_;
		OSS->GetIdentityInterface()->Login(0, NewAccount);
	}
	else
	{
		ExecuteErrorDelegate(OnError, 400, "Failed to initialize Online Subsystem Steam");
	}
}

void ShooterGameSteamUtility::OnIdentityLoginComplete(int32 LocalUserNum, bool bSuccessful, const FUniqueNetId& UserId, const FString& ErrorStr, FVoidHandler OnSuccessExt, FErrorHandler OnErrorExt)
{
	if (bSuccessful)
	{
		auto OSS = static_cast<FOnlineSubsystemSteam*>(IOnlineSubsystem::Get(STEAM_SUBSYSTEM));
		if (OSS)
		{
			if (SteamAPI_Init())
			{
				FString SteamTicket = OSS->GetIdentityInterface()->GetAuthToken(0);
				FString SteamDislayName = OSS->GetIdentityInterface()->GetPlayerNickname(0);
				UE_LOG(LogTemp, Log, TEXT("SteamLogin prerequisites are complete. Leave the rest to AccelByte authentication."));
				FRegistry::User.LoginWithOtherPlatform(EAccelBytePlatformType::Steam, SteamTicket, OnSuccessExt, OnErrorExt);
			}
			else
			{
				ExecuteErrorDelegate(OnErrorExt, 400, "IdentityLogin complete, but SteamAPI_Init() is failed");
			}
		}
		else
		{
			ExecuteErrorDelegate(OnErrorExt, 400, "IdentityLogin complete, but failed to initialize Online Subsystem Steam");
		}
	}
	else
	{
		ExecuteErrorDelegate(OnErrorExt, 400, "IdentityLogin is not success. \nReason:" + ErrorStr);
	}
}
