// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ShooterGame.h"
#include "ShooterGame_FreeForAll.h"
#include "ShooterPlayerState.h"
#include "Bots/ShooterAIController.h"
#include "Core/AccelByteRegistry.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "ShooterGameConfig.h"
#include "GameServerApi/AccelByteServerDSMApi.h"
#include "GameServerApi/AccelByteServerStatisticApi.h"


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

	if (this->MatchmakingInfo.match_id.IsEmpty())
	{
		ErrorMessage = TEXT("[ERROR] Match is not initialized");
		UE_LOG(LogOnlineGame, Display, TEXT("%s"), *ErrorMessage);
		return;
	}

	if (this->MatchmakingInfo.match_id != MatchIdOpt)
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

	// GameSession can be NULL if the match is over
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
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

	AShooterPlayerState* NewPlayerState = CastChecked<AShooterPlayerState>(NewPlayerController->PlayerState);
	NewPlayerState->SetPartyId(PartyIdOpt);
	NewPlayerState->SetUserId(UserIdOpt);

	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}

void AShooterGame_FreeForAll::RestartGame()
{
	UE_LOG(LogTemp, Display, TEXT("[MATCH] RestartGame"));
	Super::RestartGame();
	MatchmakingInfo.match_id = "";
	MatchmakingInfo.matching_parties.Empty();
}

void AShooterGame_FreeForAll::EndMatch()
{
	if (MatchmakingInfo.matching_parties.Num() > 0)
	{
		// This is called on the Super after EndMatch in ShooterGameMode::FinishMatch(), should we move it there instead to prevent double calling, or remove the one at FinishMatch()
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
					AShooterPlayerState* PlayerState = Cast<AShooterPlayerState>(GameState->PlayerArray[i]);
					if (PlayerState->GetUserId() == member.user_id)
					{
						// Fill the data for Statistic Reporting
						member.match = 1;
						member.kill = PlayerState->GetKills();
						member.death = PlayerState->GetDeaths();

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
				if (member.kill > 0) 
				{ 
					matchResults_.Add({ (float)member.kill, member.user_id, ShooterGameConfig::Get().StatisticCodeKill_ }); 
				}
				if (member.match > 0) 
				{
					matchResults_.Add({ (float)member.match, member.user_id, ShooterGameConfig::Get().StatisticCodeMatch_ }); 
				}
				if (member.death > 0) 
				{
					matchResults_.Add({ (float)member.death, member.user_id, ShooterGameConfig::Get().StatisticCodeDeath_ }); 
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

			FRegistry::ServerDSM.SendShutdownToDSM(true, MatchmakingInfo.match_id,
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

	UE_LOG(LogTemp, Display, TEXT("[MATCH] EndMatch"));
	Super::EndMatch();
	MatchmakingInfo.match_id = "";
	MatchmakingInfo.matching_parties.Empty();
}

void AShooterGame_FreeForAll::DetermineMatchWinner()
{
	AShooterGameState const* const MyGameState = CastChecked<AShooterGameState>(GameState);
	float BestScore = MIN_flt;
	int32 BestPlayer = -1;
	int32 NumBestPlayers = 0;

	for (int32 i = 0; i < MyGameState->PlayerArray.Num(); i++)
	{
		const float PlayerScore = MyGameState->PlayerArray[i]->Score;
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

void AShooterGame_FreeForAll::SetupMatch(const FAccelByteModelsMatchmakingInfo & Info)
{
	// clear previous match
	RequestFinishAndExitToMainMenu();

	// set state to WaitingToStart
	AShooterGameState* const MyGameState = Cast<AShooterGameState>(GameState);
	MyGameState->RemainingTime = WarmupTime;
	SetMatchState(MatchState::WaitingToStart);
	MatchmakingInfo = Info;
}

bool AShooterGame_FreeForAll::IsMatchStarted()
{
	return !MatchmakingInfo.match_id.IsEmpty();
}

FAccelByteModelsMatchInfo AShooterGame_FreeForAll::GetMatchInfo()
{
	FAccelByteModelsMatchInfo MatchInfo;
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
			FAccelByteModelsMatchPlayer Player;
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
				MatchmakingInfo.match_id = "";
				MatchmakingInfo.matching_parties.Empty();
			}
			return true;
		}
	}
	return false;
}
