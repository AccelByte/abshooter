// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Online/ShooterGame_FreeForAll.h"
#include "ShooterGame.h"
#include "Online/ShooterPlayerState.h"
#include "Bots/ShooterAIController.h"
#include "Core/AccelByteRegistry.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "ShooterGameConfig.h"
#include "Models/ShooterMatchInfoModels.h"

// AccelByte's
#include "Core/AccelByteRegistry.h"
#include "Core/AccelByteHttpRetryScheduler.h"
#include "GameServerApi/AccelByteServerDSMApi.h"
#include "GameServerApi/AccelByteServerStatisticApi.h"
#include "GameServerApi/AccelByteServerMatchmakingApi.h"
#include "Models/AccelByteMatchmakingModels.h"


AShooterGame_FreeForAll::AShooterGame_FreeForAll(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bDelayedStart = true;
}

void AShooterGame_FreeForAll::PreLogin(const FString & Options, const FString & Address, const FUniqueNetIdRepl & UniqueId, FString & ErrorMessage)
{
	UE_LOG(LogOnlineGame, Log, TEXT("AShooterGame_FreeForAll::PreLogin: %s"), *Options);

	FString PartyIdOpt = UGameplayStatics::ParseOption(Options, TEXT("PartyId"));
	FString MatchIdOpt = UGameplayStatics::ParseOption(Options, TEXT("MatchId"));
	FString UserIdOpt = UGameplayStatics::ParseOption(Options, TEXT("UserId"));

	if (FRegistry::ServerCredentials.GetMatchId().IsEmpty())
	{
		// get session Id
		FRegistry::ServerDSM.GetSessionId(THandler<FAccelByteModelsServerSessionResponse>::CreateLambda([&](FAccelByteModelsServerSessionResponse response)
		{
			FRegistry::ServerCredentials.SetMatchId(response.Session_id);
			UE_LOG(LogOnlineGame, Display, TEXT("Fetching Session Id got %s"), *FRegistry::ServerCredentials.GetMatchId());
			if (FRegistry::ServerCredentials.GetMatchId().IsEmpty())
			{
				ErrorMessage = TEXT("Session is not available yet");
				UE_LOG(LogOnlineGame, Display, TEXT("[ERROR] %s"), *ErrorMessage);
			}
		}), 
			FErrorHandler::CreateLambda([&](int32 errorCode, FString eMessage)
		{
			ErrorMessage = FString::Printf(TEXT("GetSessionId Error code %d message %s"), errorCode, *eMessage);
			UE_LOG(LogOnlineGame, Display, TEXT("[ERROR] %s"), *ErrorMessage);
		}
		));

		UE_LOG(LogOnlineGame, Display, TEXT("Fetching Session Id..."));
		double LastTime = FPlatformTime::Seconds();
		while (FRegistry::ServerCredentials.GetMatchId().IsEmpty() && ErrorMessage.IsEmpty())
		{
			const double AppTime = FPlatformTime::Seconds();
			FHttpModule::Get().GetHttpManager().Tick(AppTime - LastTime);
			FTicker::GetCoreTicker().Tick(AppTime - LastTime);
			FRegistry::HttpRetryScheduler.PollRetry(FPlatformTime::Seconds(), FRegistry::Credentials);
			LastTime = AppTime;
			FPlatformProcess::Sleep(0.5f);
		}
		UE_LOG(LogOnlineGame, Display, TEXT("Fetch session id complete"));
	}


	if(MatchmakingInfo.Match_id.IsEmpty() || !ErrorMessage.IsEmpty())
	{
		// get getMatchInfo
		FRegistry::ServerMatchmaking.QuerySessionStatus(FRegistry::ServerCredentials.GetMatchId(), THandler<FAccelByteModelsMatchmakingResult>::CreateLambda([&](FAccelByteModelsMatchmakingResult result)
		{
			MatchmakingInfo = result;
			SetupMatch(result);
		}), 
			FErrorHandler::CreateLambda([&](int32 errorCode, FString eMessage)
		{
			ErrorMessage = FString::Printf(TEXT("QuerySessionInfo Error code %d message %s"), errorCode, *eMessage);
			UE_LOG(LogOnlineGame, Display, TEXT("[ERROR] %s"), *ErrorMessage);
		}));

		UE_LOG(LogOnlineGame, Display, TEXT("Fetching Match Info..."));
		double LastTime = FPlatformTime::Seconds();
		while (MatchmakingInfo.Match_id.IsEmpty() && ErrorMessage.IsEmpty())
		{
			const double AppTime = FPlatformTime::Seconds();
			FHttpModule::Get().GetHttpManager().Tick(AppTime - LastTime);
			FTicker::GetCoreTicker().Tick(AppTime - LastTime);
			FRegistry::HttpRetryScheduler.PollRetry(FPlatformTime::Seconds(), FRegistry::Credentials);
			LastTime = AppTime;
			FPlatformProcess::Sleep(0.5f);
		}
		UE_LOG(LogOnlineGame, Display, TEXT("Fetching Match info complete"));
	}


	if (this->MatchmakingInfo.Match_id != MatchIdOpt)
	{
		AShooterGameState* const MyGameState = Cast<AShooterGameState>(GameState);
		if (MyGameState)
		{
			ErrorMessage = FString::Printf(TEXT("No dedicated server are available at a moment,\nplease try again in %d seconds"), MyGameState->RemainingTime);
		}
		else
		{
			ErrorMessage = TEXT("No dedicated server are available at a moment,\nplease try again later");
		}
		UE_LOG(LogOnlineGame, Display, TEXT("[ERROR] %s"), *ErrorMessage);
		return;
	};

	bool UserFound = false;
	for (const auto& Allies : MatchmakingInfo.Matching_allies)
	{
		for(const auto& Party : Allies.Matching_parties)
		if (Party.Party_id == PartyIdOpt)
		{
			for (const auto& Member : Party.Party_members)
			{
				if (Member.User_id == UserIdOpt)
				{
					UserFound = true;
					break;
				}
			}
			if (UserFound) break;
		}
		if (UserFound) break;
	}

	if (!UserFound)
	{
		ErrorMessage = TEXT("[ERROR] User not found in current match");
		UE_LOG(LogOnlineGame, Display, TEXT("%s"), *ErrorMessage);
		return;
	}

	// GameSession can be NULL if the match is over
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

void AShooterGame_FreeForAll::GetSessionData()
{
	FRegistry::ServerDSM.GetSessionId(THandler<FAccelByteModelsServerSessionResponse>::CreateLambda([this](const FAccelByteModelsServerSessionResponse& sessionResponse)
	{
		if(sessionResponse.Session_id.IsEmpty())
		{
			UE_LOG(LogOnlineGame, Display, TEXT("Session not claimed yet"));
			return;
		}

		FRegistry::ServerMatchmaking.QuerySessionStatus(sessionResponse.Session_id, THandler<FAccelByteModelsMatchmakingResult>::CreateLambda([this](const FAccelByteModelsMatchmakingResult& mmResult)
		{
			MatchmakingInfo = mmResult;
		}), 
			FErrorHandler::CreateLambda([](int32 errorCode, FString errorMsg)
		{
			UE_LOG(LogOnlineGame, Display, TEXT("Error Query Session Status, code %s msg %s"), errorCode, *errorMsg);
		}));
	}), FErrorHandler::CreateLambda([](int32 errorCode, FString errorMsg)
	{
		UE_LOG(LogOnlineGame, Display, TEXT("Error Fetching Session Id, code %s msg %s"), errorCode, *errorMsg);
	}));
}

void AShooterGame_FreeForAll::PostLogin(APlayerController* NewPlayer)
{
	// Place player on a team before Super (VoIP team based init, findplayerstart, etc)
	AShooterPlayerState* NewPlayerState = CastChecked<AShooterPlayerState>(NewPlayer->PlayerState);

	NewPlayerState->SetTeamNum(0);

	UE_LOG(LogTemp, Display, TEXT("[MATCH] PostLogin %s Team: %d"), *NewPlayerState->GetUserId(), NewPlayerState->GetTeamNum());
	Super::PostLogin(NewPlayer);
}

void AShooterGame_FreeForAll::InitGameState()
{
	Super::InitGameState();

	AShooterGameState* const MyGameState = Cast<AShooterGameState>(GameState);

	if (MyGameState)
	{
		MyGameState->NumTeams = 1;
	}
}

FString AShooterGame_FreeForAll::InitNewPlayer(APlayerController * NewPlayerController, const FUniqueNetIdRepl & UniqueId, const FString & Options, const FString & Portal)
{
	UE_LOG(LogTemp, Display, TEXT("InitNewPlayer to %s, options: %s, portal: %s"), *UniqueId.ToString(), *Options, *Portal);
	FString PartyIdOpt = UGameplayStatics::ParseOption(Options, TEXT("PartyId"));
	FString MatchIdOpt = UGameplayStatics::ParseOption(Options, TEXT("MatchId"));
	FString UserIdOpt = UGameplayStatics::ParseOption(Options, TEXT("UserId"));

	// Loop for set member joined, 
	// not sure if it's affected something so I'll comment it for now
	/*for (auto& Allies : MatchmakingInfo.Matching_allies)
	{
		for (auto& Party : Allies.Matching_parties)
		{
			if (Party.Party_id == PartyIdOpt)
			{
				for (auto& Member : Party.Party_members)
				{
					if (Member.User_id == UserIdOpt)
					{
						// set member isjoined
						FShooterMemberAttribute member = new FShooterMemberAttribute();
						member.user_id = Member.User_id;
						member.joined = true;
						auto sharedMember = MakeShared(member);
						Members->Add(member);
					}
				}
			}
		}
	}*/

	AShooterPlayerState* NewPlayerState = CastChecked<AShooterPlayerState>(NewPlayerController->PlayerState);
	NewPlayerState->SetPartyId(PartyIdOpt);
	NewPlayerState->SetUserId(UserIdOpt);

	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}

void AShooterGame_FreeForAll::RestartGame()
{
	UE_LOG(LogTemp, Display, TEXT("[MATCH] RestartGame"));
	Super::RestartGame();
	MatchmakingInfo.Match_id = "";
	MatchmakingInfo.Matching_allies.Empty();
}

void AShooterGame_FreeForAll::EndMatch()
{
#if UE_SERVER
	if (MatchmakingInfo.Matching_allies.Num() > 0)
	{
		// This is called on the Super after EndMatch in ShooterGameMode::FinishMatch(), should we move it there instead to prevent double calling, or remove the one at FinishMatch()
		DetermineMatchWinner();
		TArray<FAccelByteModelsBulkUserStatItemInc> matchResults_;
		AShooterPlayerState* MVP = nullptr;

		for (auto Allies : MatchmakingInfo.Matching_allies)
		{
			for (const auto& party : Allies.Matching_parties)
			{
				for (const auto& partyMember : party.Party_members)
				{
					int32 Rank = 0;
					int32 match = 0;
					int32 kill = 0;
					int32 death = 0;
					// Fill the data for Statistic Reporting
					// Find player
					for (int32 i = 0; i < GameState->PlayerArray.Num(); i++)
					{
						AShooterPlayerState* PlayerState = Cast<AShooterPlayerState>(GameState->PlayerArray[i]);
						if (PlayerState->GetUserId() == partyMember.User_id)
						{
							match = 1;
							kill = PlayerState->GetKills();
							death = PlayerState->GetDeaths();

							if (PlayerState->GetScore() > 0)
							{
								if (MVP == nullptr)
								{
									MVP = PlayerState;
								}
								else if (MVP->GetScore() < PlayerState->GetScore())
								{
									MVP = PlayerState;
								}
							}
						}
					}
					if (kill > 0) 
					{ 
						matchResults_.Add({ (float)kill, partyMember.User_id, ShooterGameConfig::Get().StatisticCodeKill_ });
					}
					if (match > 0) 
					{
						matchResults_.Add({ (float)match, partyMember.User_id, ShooterGameConfig::Get().StatisticCodeMatch_ });
					}
					if (death > 0) 
					{
						matchResults_.Add({ (float)death, partyMember.User_id, ShooterGameConfig::Get().StatisticCodeDeath_ });
					}
				}
			}
		}
		if (MVP != nullptr) 
		{
			matchResults_.Add({ 1.0f, MVP->GetUserId(), ShooterGameConfig::Get().StatisticCodeMVP_ }); 
		}

		//Submit statistic
		FRegistry::ServerStatistic.IncrementManyUsersStatItems(matchResults_,
			THandler<TArray<FAccelByteModelsBulkStatItemOperationResult>>::CreateLambda([](const TArray<FAccelByteModelsBulkStatItemOperationResult>& submittedResult) {}),
			AccelByte::FErrorHandler::CreateLambda([](int32 ErrorCode, const FString& ErrorMessage) { UE_LOG(LogTemp, Log, TEXT("Failed to submit player's match statistic result.")); }));
			
		//Shutdown The match once it's done, this means match is only valid for 1 session, if we need to add multiple match in session we need to disable this/restart match afterwards until it passed the intended match count.
		if (ShooterGameConfig::Get().IsLocalMode_)
		{
			// Temporary Solution to fix Server Exited right after Match Ended.
			FRegistry::ServerDSM.DeregisterLocalServerFromDSM(ShooterGameConfig::Get().LocalServerName_,
				FVoidHandler::CreateLambda([this]()
					{
						FTimerHandle EndMatchTimerHandle;
						GetWorldTimerManager().SetTimer(EndMatchTimerHandle, FTimerDelegate::CreateLambda([=]()
							{
								UE_LOG(LogTemp, Log, TEXT("Requesting Exit Game From timer, Deregister Success"));
								FGenericPlatformMisc::RequestExitWithStatus(false, 0);
							}), 10, false);
					}),
				AccelByte::FErrorHandler::CreateLambda([this](int32 ErrorCode, const FString& ErrorMessage)
					{
						FTimerHandle EndMatchTimerHandle;
						GetWorldTimerManager().SetTimer(EndMatchTimerHandle, FTimerDelegate::CreateLambda([=]()
							{
								UE_LOG(LogTemp, Log, TEXT("Requesting Exit Game From timer, Deregister Failed"));
								FGenericPlatformMisc::RequestExitWithStatus(false, ErrorCode);
							}), 10, false);
					}));
		}
		else
		{
			// Temporary Solution to fix Server Exited right after Match Ended.

			FRegistry::ServerDSM.SendShutdownToDSM(true, MatchmakingInfo.Match_id,
				FVoidHandler::CreateLambda([this]()
					{
						FTimerHandle EndMatchTimerHandle;
						GetWorldTimerManager().SetTimer(EndMatchTimerHandle, FTimerDelegate::CreateLambda([=]()
							{
								UE_LOG(LogTemp, Log, TEXT("Requesting Exit Game From timer, Deregister Success"));
								FGenericPlatformMisc::RequestExitWithStatus(false, 0);
							}), 10, false);
					}),
				AccelByte::FErrorHandler::CreateLambda([this](int32 ErrorCode, const FString& ErrorMessage)
					{
						FTimerHandle EndMatchTimerHandle;
						GetWorldTimerManager().SetTimer(EndMatchTimerHandle, FTimerDelegate::CreateLambda([=]()
							{
								UE_LOG(LogTemp, Log, TEXT("Requesting Exit Game From timer, Deregister Failed"));
								FGenericPlatformMisc::RequestExitWithStatus(false, ErrorCode);
							}), 10, false);
					}));
		}
	}
#endif

	UE_LOG(LogTemp, Display, TEXT("[MATCH] EndMatch"));
	Super::EndMatch();
	MatchmakingInfo.Match_id = "";
	MatchmakingInfo.Matching_allies.Empty();
}

void AShooterGame_FreeForAll::DetermineMatchWinner()
{
	AShooterGameState const* const MyGameState = CastChecked<AShooterGameState>(GameState);
	float BestScore = MIN_flt;
	int32 BestPlayer = -1;
	int32 NumBestPlayers = 0;

	for (int32 i = 0; i < MyGameState->PlayerArray.Num(); i++)
	{
		const float PlayerScore = MyGameState->PlayerArray[i]->GetScore();
		if (BestScore < PlayerScore)
		{
			BestScore = PlayerScore;
			BestPlayer = i;
			NumBestPlayers = 1;
		}
		else if (BestScore == PlayerScore)
		{
			NumBestPlayers++;
		}
	}

	WinnerPlayerState = (NumBestPlayers == 1) ? Cast<AShooterPlayerState>(MyGameState->PlayerArray[BestPlayer]) : NULL;
}

bool AShooterGame_FreeForAll::IsWinner(AShooterPlayerState* PlayerState) const
{
	return PlayerState && !PlayerState->IsQuitter() && PlayerState == WinnerPlayerState;
}

void AShooterGame_FreeForAll::SetupMatch(const FAccelByteModelsMatchmakingResult& Info)
{
	// clear previous match
	//RequestFinishAndExitToMainMenu();

	// set state to WaitingToStart
	AShooterGameState* const MyGameState = Cast<AShooterGameState>(GameState);
	MyGameState->RemainingTime = WarmupTime;
	SetMatchState(MatchState::WaitingToStart);
	MatchmakingInfo = Info;
}

bool AShooterGame_FreeForAll::IsMatchStarted()
{
	return !MatchmakingInfo.Match_id.IsEmpty();
}

FShooterMatchInfo AShooterGame_FreeForAll::GetMatchInfo()
{
	FShooterMatchInfo MatchInfo;
	MatchInfo.matchmaking_info = MatchmakingInfo;
	MatchInfo.remaining_time = -1;

	AShooterGameState* const MyGameState = Cast<AShooterGameState>(GameState);
	if (MyGameState)
	{
		MatchInfo.remaining_time = MyGameState->RemainingTime;
	}
	MatchInfo.match_state = GetMatchState();

	for (int32 i = 0; i < GameState->PlayerArray.Num(); i++)
	{
		const AShooterPlayerState* const PlayerState = Cast<AShooterPlayerState>(GameState->PlayerArray[i]);
		if (PlayerState)
		{
			FShooterMatchPlayer Player;
			Player.name = PlayerState->GetPlayerName();
			Player.user_id = PlayerState->GetUserId();
			MatchInfo.players.Add(Player);
		}
	}

	return MatchInfo;
}

bool AShooterGame_FreeForAll::ResetMatch(bool Force)
{
	AShooterGameState* const MyGameState = Cast<AShooterGameState>(GameState);
	if (MyGameState)
	{
		if (GameState->PlayerArray.Num() == 0)
		{
			if (IsMatchStarted())
			{
				// clear previous match
				RequestFinishAndExitToMainMenu();
				MatchmakingInfo.Match_id = "";
				MatchmakingInfo.Matching_allies.Empty();
			}
			return true;
		}
	}
	return false;
}
