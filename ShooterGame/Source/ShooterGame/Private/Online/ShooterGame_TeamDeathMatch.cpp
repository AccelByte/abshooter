// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ShooterGame.h"
#include "ShooterTeamStart.h"
#include "Online/ShooterGame_TeamDeathMatch.h"
#include "Online/ShooterPlayerState.h"
#include "Bots/ShooterAIController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"

#include "Server/ServerConfig.h"

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
		ErrorMessage = TEXT("[ERROR] Incorrect matchId");
		UE_LOG(LogOnlineGame, Display, TEXT("%s"), *ErrorMessage);
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
		ErrorMessage = TEXT("[ERROR] Incorrect matchId");
		UE_LOG(LogOnlineGame, Display, TEXT("%s"), *ErrorMessage);
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
	int32 BestTeam = -1;
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
	DetermineMatchWinner();
	TArray<FAccelByteModelsMatchmakingResult> Results;

	for (const auto& party : MatchmakingInfo.matching_parties)
	{
		FAccelByteModelsMatchmakingResult Result;
		Result.leader = party.leader_id;
		Result.party_id = party.party_id;
		for (const auto& partyMember : party.party_members)
		{
			int32 Rank = 0;
			FAccelByteModelsMatchmakingMember member;
			member.user_id = partyMember.user_id;
			// Find player
			for (int32 i = 0; i < GameState->PlayerArray.Num(); i++)
			{
				const AShooterPlayerState* const TestPlayerState = Cast<AShooterPlayerState>(GameState->PlayerArray[i]);
				if (TestPlayerState->GetUserId() == member.user_id)
				{
					member.assist = 0;
					member.kill = TestPlayerState->GetKills();
					member.death = TestPlayerState->GetDeaths();
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
			Result.members.Add(member);
			Result.rank = Rank;
		}
		Results.Add(Result);
	}
	FString Content;
	TArrayUStructToJsonString(Results, Content);
	
	if (MatchmakingInfo.matching_parties.Num() == 2)
	{
		FServerConfig::Get().GetClientAccessToken(FServerConfig::FGetClientAccessTokenSuccess::CreateLambda([Results](const AccelByte::Credentials& Credentials)
		{
			FString Authorization = FString::Printf(TEXT("Bearer %s"), *Credentials.GetClientAccessToken());
			FString Url = FString::Printf(TEXT("%s/namespaces/%s/matchresult"), *FServerConfig::Get().MatchmakingServerUrl, *Credentials.GetClientNamespace());
			FString Verb = TEXT("POST");
			FString ContentType = TEXT("application/json");
			FString Accept = TEXT("application/json");

			FString Content;
			TArrayUStructToJsonString(Results, Content);
			FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
			Request->SetURL(Url);
			Request->SetHeader(TEXT("Authorization"), Authorization);
			Request->SetVerb(Verb);
			Request->SetHeader(TEXT("Content-Type"), ContentType);
			Request->SetHeader(TEXT("Accept"), Accept);
			Request->SetContentAsString(Content);
			Request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful) {
				if (Successful && Request.IsValid())
				{
					UE_LOG(LogOnlineGame, Log, TEXT("AShooterGameSession::OnSendMatchmakingResultResponse : [%d] %s"), Response->GetResponseCode(),  *Response->GetContentAsString());
				}
			});
			Request->ProcessRequest();
		}), AccelByte::FErrorHandler::CreateLambda([](int32 ErrorCode, const FString& ErrorMessage) {
			UE_LOG(LogOnlineGame, Log, TEXT("[ERROR] SendMatchmakingResultResponse GetClientAccessToken : [%d] %s"), ErrorCode, *ErrorMessage);
		}));
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
}

bool AShooterGame_TeamDeathMatch::SetupSecondParty(const FAccelByteModelsMatchmakingInfo& Info)
{
#if SIMULATE_SETUP_MATCHMAKING
	if (MatchmakingInfo.match_id == Info.match_id)
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
	}
#endif
	return false;
}

bool AShooterGame_TeamDeathMatch::IsMatchStarted()
{
	return !MatchmakingInfo.match_id.IsEmpty();
}