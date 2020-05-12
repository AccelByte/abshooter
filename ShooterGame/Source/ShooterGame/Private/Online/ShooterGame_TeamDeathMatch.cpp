// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ShooterGame.h"
#include "ShooterTeamStart.h"
#include "Online/ShooterGame_TeamDeathMatch.h"
#include "Online/ShooterPlayerState.h"
#include "Bots/ShooterAIController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "ShooterGameConfig.h"
#include "Core/AccelByteRegistry.h"
#include "GameServerApi/AccelByteServerDSMApi.h"
#include "GameServerApi/AccelByteServerStatisticApi.h"

#define MOCK_MATCHMAKING 0

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

#if MOCK_MATCHMAKING
	//temporary set matchmaking info from joined user
	if (MatchmakingInfo.match_id.IsEmpty())
	{
		MatchmakingInfo.match_id = MatchIdOpt;
		UE_LOG(LogTemp, Display, TEXT("[MATCH] Set current matchId: %s"), *MatchIdOpt);
	}
	else if (MatchmakingInfo.match_id != MatchIdOpt)
	{
		UE_LOG(LogTemp, Display, TEXT("[ERROR] Incorrect matchId"));
		return "";
	}


	if (!PartyIdOpt.IsEmpty())
	{
		bool Found = false;
		for (int32 i = 0; i < MatchmakingInfo.matching_parties.Num(); i++)
		{
			if (MatchmakingInfo.matching_parties[i].party_id == PartyIdOpt)
			{
				MatchmakingInfo.matching_parties[i].party_members.Add({ UserIdOpt });
				Found = true;
				break;
			}
		}

		if (!Found)
		{
			if (MatchmakingInfo.matching_parties.Num() >= NumTeams)
			{
				UE_LOG(LogTemp, Display, TEXT("[ERROR] Max number of parties reached !!!!!!"));
				return "";
			}
			else
			{
				FAccelByteModelsMatchmakingParty Party;
				Party.party_id = PartyIdOpt;
				//Party.leader_id = UserIdOpt;
				Party.party_members.Add({ UserIdOpt });
				MatchmakingInfo.matching_parties.Add(Party);
			}
		}
	}
#else
	bool AllJoined = true;
	for (auto& Party : MatchmakingInfo.matching_parties)
	{
		if (Party.party_id == PartyIdOpt)
		{
			for (auto& Member : Party.party_members)
			{
				if (Member.user_id == UserIdOpt)
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
#endif

	AShooterPlayerState* NewPlayerState = CastChecked<AShooterPlayerState>(NewPlayerController->PlayerState);
	NewPlayerState->SetPartyId(PartyIdOpt);
	NewPlayerState->SetUserId(UserIdOpt);

	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}

void AShooterGame_TeamDeathMatch::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	UE_LOG(LogOnlineGame, Log, TEXT("AShooterGame_TeamDeathMatch::PreLogin: %s"), *Options);
	
	FString PartyIdOpt = UGameplayStatics::ParseOption(Options, TEXT("PartyId"));
	FString MatchIdOpt = UGameplayStatics::ParseOption(Options, TEXT("MatchId"));
	FString UserIdOpt = UGameplayStatics::ParseOption(Options, TEXT("UserId"));

#if MOCK_MATCHMAKING
	if (MatchIdOpt.IsEmpty())
	{
		ErrorMessage = TEXT("[ERROR] MatchId required");
		UE_LOG(LogOnlineGame, Display, TEXT("%s"), *ErrorMessage);
		return;
	}

	if (PartyIdOpt.IsEmpty())
	{
		ErrorMessage = TEXT("[ERROR] PartyId required");
		UE_LOG(LogOnlineGame, Display, TEXT("%s"), *ErrorMessage);
		return;
	}

	if (UserIdOpt.IsEmpty())
	{
		ErrorMessage = TEXT("[ERROR] UserId required");
		UE_LOG(LogOnlineGame, Display, TEXT("%s"), *ErrorMessage);
		return;
	}

	if (!this->MatchmakingInfo.match_id.IsEmpty() && this->MatchmakingInfo.match_id != MatchIdOpt)
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
	}

	if (this->MatchmakingInfo.matching_parties.Num() >= NumTeams)
	{
		ErrorMessage = TEXT("[ERROR] Max number of party reached");
		UE_LOG(LogOnlineGame, Display, TEXT("%s"), *ErrorMessage);
		return;
	}
#else
	if (this->MatchmakingInfo.match_id.IsEmpty())
	{
		ErrorMessage = TEXT("[ERROR] Match is not initialized");
		UE_LOG(LogOnlineGame, Display, TEXT("%s"), *ErrorMessage);
		return;
	}

	if(this->MatchmakingInfo.match_id != MatchIdOpt)
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
	for (const auto& Party : MatchmakingInfo.matching_parties)
	{
		if (Party.party_id == PartyIdOpt)
		{
			for (const auto& Member : Party.party_members)
			{
				if (Member.user_id == UserIdOpt)
				{
					UserFound = true;
					break;
				}
			}
			if (Party.leader_id == UserIdOpt)
			{
				UserFound = true;
				break;
			}
		}
	}

	if (!UserFound)
	{
		ErrorMessage = TEXT("[ERROR] User not found in current match");
		UE_LOG(LogOnlineGame, Display, TEXT("%s"), *ErrorMessage);
		return;
	}

#endif

	// GameSession can be NULL if the match is over
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

void AShooterGame_TeamDeathMatch::PostLogin(APlayerController* NewPlayer)
{
	// Place player on a team before Super (VoIP team based init, findplayerstart, etc)
	AShooterPlayerState* NewPlayerState = CastChecked<AShooterPlayerState>(NewPlayer->PlayerState);
#if MOCK_MATCHMAKING
	if (NewPlayerState->GetPartyId().IsEmpty())
	{
		const int32 TeamNum = ChooseTeam(NewPlayerState);
		NewPlayerState->SetTeamNum(TeamNum);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("[MATCH] GetTeam by PartyId: %s"), *NewPlayerState->GetPartyId());
		int32 Index = -1;
		for (int32 i = 0; i < MatchmakingInfo.matching_parties.Num(); i++)
		{
			if (MatchmakingInfo.matching_parties[i].party_id == NewPlayerState->GetPartyId())
			{
				Index = i;
				break;
			}
		}
		NewPlayerState->SetTeamNum(Index);
	}
#else
	int32 Index = -1;
	for (int32 i = 0; i < MatchmakingInfo.matching_parties.Num(); i++)
	{
		if (MatchmakingInfo.matching_parties[i].party_id == NewPlayerState->GetPartyId())
		{
			Index = i;
			break;
		}
	}
	NewPlayerState->SetTeamNum(Index);
#endif
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
		AShooterPlayerState const* const TestPlayerState = Cast<AShooterPlayerState>(GameState->PlayerArray[i]);
		if (TestPlayerState && TestPlayerState != ForPlayerState && TeamBalance.IsValidIndex(TestPlayerState->GetTeamNum()))
		{
			TeamBalance[TestPlayerState->GetTeamNum()]++;
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
	MatchmakingInfo.match_id = "";
	MatchmakingInfo.matching_parties.Empty();
}

void AShooterGame_TeamDeathMatch::EndMatch()
{
#if UE_SERVER
	if (MatchmakingInfo.matching_parties.Num() == 2)
	{
	DetermineMatchWinner();
	TArray<FAccelByteModelsBulkUserStatItemInc> matchResults_;
	AShooterPlayerState* MVP = nullptr;

	for (const auto& party : MatchmakingInfo.matching_parties)
	{
		for (const auto& partyMember : party.party_members)
		{
			int32 Rank = 0;
			FAccelByteModelsMatchmakingMember member;
			member.user_id = partyMember.user_id;
			// Find player
			for (int32 i = 0; i < GameState->PlayerArray.Num(); i++)
			{
				AShooterPlayerState* TestPlayerState = Cast<AShooterPlayerState>(GameState->PlayerArray[i]);
				if (TestPlayerState->GetUserId() == member.user_id)
				{
					member.match = 1;
					member.kill = TestPlayerState->GetKills();
					member.death = TestPlayerState->GetDeaths();

					if (TestPlayerState->GetScore() > 0)
					{
						if (MVP == nullptr)
						{
							MVP = TestPlayerState;
						} else if (MVP->GetScore() < TestPlayerState->GetScore())
						{
							MVP = TestPlayerState;
						}
					}

					if (TestPlayerState)
					{
						if (TestPlayerState->GetTeamNum() == WinnerTeam)
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
			if (member.kill > 0) { matchResults_.Add({ (float) member.kill, member.user_id, ShooterGameConfig::Get().StatisticCodeKill_ }); }
			if (member.match > 0){ matchResults_.Add({ (float) member.match, member.user_id, ShooterGameConfig::Get().StatisticCodeMatch_ }); }
			if (member.death > 0) { matchResults_.Add({ (float) member.death, member.user_id, ShooterGameConfig::Get().StatisticCodeDeath_ }); }
		}
	}
	if (MVP != nullptr) { matchResults_.Add({ 1.0f, MVP->GetUserId(), ShooterGameConfig::Get().StatisticCodeMVP_}); }

	//Submit statistic
	FRegistry::ServerStatistic.IncrementManyUsersStatItems(matchResults_,
		THandler<TArray<FAccelByteModelsBulkStatItemOperationResult>>::CreateLambda([](const TArray<FAccelByteModelsBulkStatItemOperationResult>& submittedResult) {}),
		AccelByte::FErrorHandler::CreateLambda([](int32 ErrorCode, const FString& ErrorMessage) { UE_LOG(LogTemp, Log, TEXT("Failed to submit player's match statistic result.")); }));

	//Shutdown anyway
	if (ShooterGameConfig::Get().IsLocalMode_)
	{
		FRegistry::ServerDSM.DeregisterLocalServerFromDSM(ShooterGameConfig::Get().LocalServerName_, 
			FVoidHandler::CreateLambda([]() { FGenericPlatformMisc::RequestExitWithStatus(false, 0); }),
			AccelByte::FErrorHandler::CreateLambda([](int32 ErrorCode, const FString& ErrorMessage) { FGenericPlatformMisc::RequestExitWithStatus(false, ErrorCode); }));
	}
	else
	{
		FRegistry::ServerDSM.SendShutdownToDSM(true, MatchmakingInfo.match_id, 
			FVoidHandler::CreateLambda([]() { FGenericPlatformMisc::RequestExitWithStatus(false, 0); }),
			AccelByte::FErrorHandler::CreateLambda([](int32 ErrorCode, const FString& ErrorMessage) { FGenericPlatformMisc::RequestExitWithStatus(false, ErrorCode); }));
	}
	}
#endif

	UE_LOG(LogTemp, Display, TEXT("[MATCH] EndMatch"));
	Super::EndMatch();
	MatchmakingInfo.match_id = "";
	MatchmakingInfo.matching_parties.Empty();
}

void AShooterGame_TeamDeathMatch::SetupMatch(const FAccelByteModelsMatchmakingInfo& Info)
{
	// clear previous match
	RequestFinishAndExitToMainMenu();

	// set state to WaitingToStart
	AShooterGameState* const MyGameState = Cast<AShooterGameState>(GameState);
	MyGameState->RemainingTime = WarmupTime;
	SetMatchState(MatchState::WaitingToStart);
	MatchmakingInfo = Info;
	JoinedTeam = MatchmakingInfo.matching_parties.Num();
}

bool AShooterGame_TeamDeathMatch::SetupSecondParty(const FAccelByteModelsMatchmakingInfo& Info)
{
#ifdef SIMULATE_SETUP_MATCHMAKING
	if (MatchmakingInfo.match_id == Info.match_id)
	{
		if (JoinedTeam < 2)
		{
			FAccelByteModelsMatchmakingParty InParty;

			for (const FAccelByteModelsMatchmakingParty& Party : Info.matching_parties)
			{
				if (!Party.party_id.IsEmpty())
				{
					InParty = Party;
					break;
				}
			}

			if (!InParty.party_id.IsEmpty() && InParty.party_members.Num() > 0)
			{
				if (MatchmakingInfo.matching_parties.Num() >= 2)
				{
					for (FAccelByteModelsMatchmakingParty& Party : MatchmakingInfo.matching_parties)
					{
						if (Party.party_id.IsEmpty() || Party.party_id == InParty.party_id)
						{
							for (const FAccelByteModelsMatchmakingPartyMember& Member : Party.party_members)
							{
								if (InParty.party_members[0].user_id == Member.user_id)
								{
									Party.party_id = InParty.party_id;
									return true;
								}
							}
						}
					}
				}
				else
				{
					MatchmakingInfo.matching_parties.Add(InParty);
					JoinedTeam++;
					return true;
				}
			}
		}
		else
		{
			return false;
		}
	}
#endif
	return false;
}

bool AShooterGame_TeamDeathMatch::IsMatchStarted()
{
	return !MatchmakingInfo.match_id.IsEmpty();
}

FAccelByteModelsMatchInfo AShooterGame_TeamDeathMatch::GetMatchInfo()
{
	FAccelByteModelsMatchInfo MatchInfo;
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
			FAccelByteModelsMatchPlayer Player;
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
				MatchmakingInfo.match_id = "";
				MatchmakingInfo.matching_parties.Empty();
			}
			return true;
		}
	}
	return false;
}