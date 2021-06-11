// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Online/ShooterGame_TeamDeathMatch.h"
#include "ShooterGame.h"
#include "ShooterTeamStart.h"
#include "Online/ShooterPlayerState.h"
#include "Bots/ShooterAIController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "Models/ShooterMatchInfoModels.h"
#include "ShooterGameConfig.h"

// Accelbyte's
#include "Core/AccelByteRegistry.h"
#include "Core/AccelByteHttpRetryScheduler.h"
#include "Models/AccelByteMatchmakingModels.h"
#include "GameServerApi/AccelByteServerDSMApi.h"
#include "GameServerApi/AccelByteServerMatchmakingApi.h"
#include "GameServerApi/AccelByteServerStatisticApi.h"


template<typename CharType = TCHAR, template<typename> class PrintPolicy = TPrettyJsonPrintPolicy, typename InStructType>
static bool TArrayUStructToJsonString(const TArray<InStructType>& InArray, FString& OutJsonString, int64 CheckFlags = 0, int64 SkipFlags = 0, int32 Indent = 0)
{
	const UStruct* StructDefinition = InStructType::StaticStruct();
	TArray< TSharedPtr<FJsonValue> > JsonArray;

	for (auto& Item : InArray)
	{
		const void* Struct = &Item;
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		if (FJsonObjectConverter::UStructToJsonObject(StructDefinition, Struct, JsonObject.ToSharedRef(), CheckFlags, SkipFlags, nullptr))
		{
			TSharedRef< FJsonValueObject > JsonValue = MakeShareable(new FJsonValueObject(JsonObject));
			JsonArray.Add(JsonValue);
		}
	}

	TSharedRef<TJsonWriter<CharType, PrintPolicy<CharType>>> JsonWriter = TJsonWriterFactory<CharType, PrintPolicy<CharType>>::Create(&OutJsonString, Indent);
	if (FJsonSerializer::Serialize(JsonArray, JsonWriter))
	{
		JsonWriter->Close();
		return true;
	}
	else
	{
		UE_LOG(LogJson, Warning, TEXT("UStructToFormattedObjectString - Unable to write out json"));
		JsonWriter->Close();
	}

	return false;
}

AShooterGame_TeamDeathMatch::AShooterGame_TeamDeathMatch(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NumTeams = 2;
	bDelayedStart = true;
}

FString AShooterGame_TeamDeathMatch::InitNewPlayer(APlayerController * NewPlayerController, const FUniqueNetIdRepl & UniqueId, const FString & Options, const FString & Portal)
{
	UE_LOG(LogTemp, Display, TEXT("InitNewPlayer to %s, options: %s, portal: %s"), *UniqueId.ToString(), *Options, *Portal);
	FString PartyIdOpt = UGameplayStatics::ParseOption(Options, TEXT("PartyId"));
	FString MatchIdOpt = UGameplayStatics::ParseOption(Options, TEXT("MatchId"));
	FString UserIdOpt = UGameplayStatics::ParseOption(Options, TEXT("UserId"));

	// Loop for set member joined, 
	// not sure if it's affected something so I'll comment it for now
	/*
	bool AllJoined = true;
	for (auto& Allies : MatchmakingInfo.Matching_allies)
	{
		for (auto& Party : Allies.Matching_parties)
		{
			if (Party.Party_id == PartyIdOpt)
			{
				for (auto& Member : Party.Party_members)
				{
					if (Member.User_id == UserIdOpt)
					{
						Member.joined = true;
					}
					else if (!Member.joined)
					{
						AllJoined = false;
					}
				}
			}
		}
	}
	*/

	AShooterPlayerState* NewPlayerState = CastChecked<AShooterPlayerState>(NewPlayerController->PlayerState);
	NewPlayerState->SetPartyId(PartyIdOpt);
	NewPlayerState->SetUserId(UserIdOpt);

	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}

void AShooterGame_TeamDeathMatch::PreLogin(const FString & Options, const FString & Address, const FUniqueNetIdRepl & UniqueId, FString & ErrorMessage)
{
	UE_LOG(LogOnlineGame, Log, TEXT("AShooterGame_TeamDeathMatch::PreLogin: %s"), *Options);
	
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
		UE_LOG(LogOnlineGame, Display, TEXT("Fetching session id complete"));
	}


	if (MatchmakingInfo.Match_id.IsEmpty() || !ErrorMessage.IsEmpty())
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
		while (MatchmakingInfo.Match_id.IsEmpty() && ErrorMessage.IsEmpty() )
		{
			const double AppTime = FPlatformTime::Seconds();
			FHttpModule::Get().GetHttpManager().Tick(AppTime - LastTime);
			FTicker::GetCoreTicker().Tick(AppTime - LastTime);
			LastTime = AppTime;
			FPlatformProcess::Sleep(0.5f);
		}
		UE_LOG(LogOnlineGame, Display, TEXT("Fetching Match info complete"));
	}


	if (this->MatchmakingInfo.Match_id.IsEmpty())
	{
		ErrorMessage = TEXT("[ERROR] Match is not initialized");
		UE_LOG(LogOnlineGame, Display, TEXT("%s"), *ErrorMessage);
		return;
	}

	if(this->MatchmakingInfo.Match_id != MatchIdOpt)
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
		for (const auto& Party : Allies.Matching_parties)
		{
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
			}
		}
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

void AShooterGame_TeamDeathMatch::PostLogin(APlayerController* NewPlayer)
{
	// Place player on a team before Super (VoIP team based init, findplayerstart, etc)
	AShooterPlayerState* NewPlayerState = CastChecked<AShooterPlayerState>(NewPlayer->PlayerState);

	int32 Index = -1;
	for (int32 i = 0; i < MatchmakingInfo.Matching_allies.Num(); i++)
	{
		if (MatchmakingInfo.Matching_allies[i].Matching_parties[0].Party_id == NewPlayerState->GetPartyId())
		{
			Index = i;
			break;
		}
	}
	NewPlayerState->SetTeamNum(Index);

	UE_LOG(LogTemp, Display, TEXT("[MATCH] PostLogin %s Team: %d"), *NewPlayerState->GetUserId(),  NewPlayerState->GetTeamNum());
	Super::PostLogin(NewPlayer);
}

void AShooterGame_TeamDeathMatch::InitGameState()
{
	Super::InitGameState();

	AShooterGameState* const MyGameState = Cast<AShooterGameState>(GameState);
	if (MyGameState)
	{
		MyGameState->NumTeams = NumTeams;
	}
}

bool AShooterGame_TeamDeathMatch::CanDealDamage(AShooterPlayerState* DamageInstigator, class AShooterPlayerState* DamagedPlayer) const
{
	return DamageInstigator && DamagedPlayer && (DamagedPlayer == DamageInstigator || DamagedPlayer->GetTeamNum() != DamageInstigator->GetTeamNum());
}

int32 AShooterGame_TeamDeathMatch::ChooseTeam(AShooterPlayerState* ForPlayerState) const
{
	TArray<int32> TeamBalance;
	TeamBalance.AddZeroed(NumTeams);

	// get current team balance
	for (int32 i = 0; i < GameState->PlayerArray.Num(); i++)
	{
		AShooterPlayerState const* const PlayerState = Cast<AShooterPlayerState>(GameState->PlayerArray[i]);
		if (PlayerState && PlayerState != ForPlayerState && TeamBalance.IsValidIndex(PlayerState->GetTeamNum()))
		{
			TeamBalance[PlayerState->GetTeamNum()]++;
		}
	}

	// find least populated one
	int32 BestTeamScore = TeamBalance[0];
	for (int32 i = 1; i < TeamBalance.Num(); i++)
	{
		if (BestTeamScore > TeamBalance[i])
		{
			BestTeamScore = TeamBalance[i];
		}
	}

	// there could be more than one...
	TArray<int32> BestTeams;
	for (int32 i = 0; i < TeamBalance.Num(); i++)
	{
		if (TeamBalance[i] == BestTeamScore)
		{
			BestTeams.Add(i);
		}
	}

	// get random from best list
	const int32 RandomBestTeam = BestTeams[FMath::RandHelper(BestTeams.Num())];
	return RandomBestTeam;
}

void AShooterGame_TeamDeathMatch::DetermineMatchWinner()
{
	AShooterGameState const* const MyGameState = Cast<AShooterGameState>(GameState);
	int32 BestScore = MIN_uint32;
	int32 BestTeam = 1;
	int32 NumBestTeams = 1;

	for (int32 i = 0; i < MyGameState->TeamScores.Num(); i++)
	{
		const int32 TeamScore = MyGameState->TeamScores[i];
		if (BestScore < TeamScore)
		{
			BestScore = TeamScore;
			BestTeam = i;
			NumBestTeams = 1;
		}
		else if (BestScore == TeamScore)
		{
			NumBestTeams++;
		}
	}

	WinnerTeam = (NumBestTeams == 1) ? BestTeam : NumTeams;
}

bool AShooterGame_TeamDeathMatch::IsWinner(AShooterPlayerState* PlayerState) const
{
	return PlayerState && !PlayerState->IsQuitter() && PlayerState->GetTeamNum() == WinnerTeam;
}

bool AShooterGame_TeamDeathMatch::IsSpawnpointAllowed(APlayerStart* SpawnPoint, AController* Player) const
{
	if (Player)
	{
		AShooterTeamStart* TeamStart = Cast<AShooterTeamStart>(SpawnPoint);
		AShooterPlayerState* PlayerState = Cast<AShooterPlayerState>(Player->PlayerState);

		if (PlayerState && TeamStart && TeamStart->SpawnTeam != PlayerState->GetTeamNum())
		{
			return false;
		}
	}

	return Super::IsSpawnpointAllowed(SpawnPoint, Player);
}

void AShooterGame_TeamDeathMatch::InitBot(AShooterAIController* AIC, int32 BotNum)
{	
	AShooterPlayerState* BotPlayerState = CastChecked<AShooterPlayerState>(AIC->PlayerState);
	const int32 TeamNum = ChooseTeam(BotPlayerState);
	BotPlayerState->SetTeamNum(TeamNum);		

	Super::InitBot(AIC, BotNum);
}

void AShooterGame_TeamDeathMatch::RestartGame()
{
	UE_LOG(LogTemp, Display, TEXT("[MATCH] RestartGame"));
	Super::RestartGame();
	MatchmakingInfo.Match_id = "";
	MatchmakingInfo.Matching_allies.Empty();
}

void AShooterGame_TeamDeathMatch::EndMatch()
{
#if UE_SERVER
	if (MatchmakingInfo.Matching_allies.Num() == 2)
	{
	DetermineMatchWinner();
	TArray<FAccelByteModelsBulkUserStatItemInc> matchResults_;
	AShooterPlayerState* MVP = nullptr;

	for (const auto& allies : MatchmakingInfo.Matching_allies)
	{
		for (const auto& party : allies.Matching_parties)
		{
			for (const auto& partyMember : party.Party_members)
			{
				int32 Rank = 0;
				int32 kill = 0;
				int32 death = 0;
				int32 match = 0;

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

						if (PlayerState)
						{
							if (PlayerState->GetTeamNum() == WinnerTeam)
							{
								Rank = 1;
							}
							else
							{
								Rank = 2;
							}
						}
						break;
					}
				}
				if (kill > 0) { matchResults_.Add({ (float)kill, partyMember.User_id, ShooterGameConfig::Get().StatisticCodeKill_ }); }
				if (match > 0) { matchResults_.Add({ (float)match, partyMember.User_id, ShooterGameConfig::Get().StatisticCodeMatch_ }); }
				if (death > 0) { matchResults_.Add({ (float)death, partyMember.User_id, ShooterGameConfig::Get().StatisticCodeDeath_ }); }
			}
		}
	}
	if (MVP != nullptr) { matchResults_.Add({ 1.0f, MVP->GetUserId(), ShooterGameConfig::Get().StatisticCodeMVP_}); }

	// Submit statistics
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

void AShooterGame_TeamDeathMatch::SetupMatch(const FAccelByteModelsMatchmakingResult& Info)
{
	// clear previous match
	//RequestFinishAndExitToMainMenu();

	// set state to WaitingToStart
	AShooterGameState* const MyGameState = Cast<AShooterGameState>(GameState);
	MyGameState->RemainingTime = WarmupTime;
	SetMatchState(MatchState::WaitingToStart);
	MatchmakingInfo = Info;
	JoinedTeam = MatchmakingInfo.Matching_allies.Num();
}

bool AShooterGame_TeamDeathMatch::IsMatchStarted()
{
	return !MatchmakingInfo.Match_id.IsEmpty();
}

FShooterMatchInfo AShooterGame_TeamDeathMatch::GetMatchInfo()
{
	FShooterMatchInfo MatchInfo;
	MatchInfo.matchmaking_info = MatchmakingInfo;
	MatchInfo.remaining_time = -1;
	AShooterGameState* const MyGameState = Cast<AShooterGameState>(GameState);
	if (MyGameState) MatchInfo.remaining_time = MyGameState->RemainingTime;
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

bool AShooterGame_TeamDeathMatch::ResetMatch(bool Force)
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
