// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Server/Models/AccelByteMatchmakingModels.h"
#include "ShooterGame_TeamDeathMatch.generated.h"

class AShooterPlayerState;
class AShooterAIController;

UCLASS()
class AShooterGame_TeamDeathMatch : public AShooterGameMode
{
	GENERATED_UCLASS_BODY()

	void PreLogin(const FString & Options, const FString & Address, const FUniqueNetIdRepl & UniqueId, FString & ErrorMessage) override;

	/** setup team changes at player login */
	void PostLogin(APlayerController* NewPlayer) override;

	/** initialize replicated game data */
	virtual void InitGameState() override;

	/** can players damage each other? */
	virtual bool CanDealDamage(AShooterPlayerState* DamageInstigator, AShooterPlayerState* DamagedPlayer) const override;

	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal = TEXT("")) override;

	/** use restart game for reinit matchmaking info */
	virtual void RestartGame() override;

	/** use endmatch for set statistic values for each players, unregister the game server or shutdown game server from accelbyte armada*/
	virtual void EndMatch() override;

protected:

	int32 JoinedTeam = 0;

	/** number of teams */
	int32 NumTeams;

	/** best team */
	int32 WinnerTeam;

	/** pick team with least players in or random when it's equal */
	int32 ChooseTeam(AShooterPlayerState* ForPlayerState) const;

	/** check who won */
	virtual void DetermineMatchWinner() override;

	/** check if PlayerState is a winner */
	virtual bool IsWinner(AShooterPlayerState* PlayerState) const override;

	/** check team constraints */
	virtual bool IsSpawnpointAllowed(APlayerStart* SpawnPoint, AController* Player) const;

	/** initialization for bot after spawning */
	virtual void InitBot(AShooterAIController* AIC, int32 BotNum) override;	

	FAccelByteModelsMatchmakingInfo MatchmakingInfo;

public:
	/** initialization for a match after getting matchmaking info from lobby*/
	void SetupMatch(const FAccelByteModelsMatchmakingInfo& Info);

	bool SetupSecondParty(const FAccelByteModelsMatchmakingInfo& Info);

	/** checking whether the match has started or not */
	bool IsMatchStarted();

	/** get match related info */
	FAccelByteModelsMatchInfo GetMatchInfo();

	/** revert matchmaking info */
	bool ResetMatch(bool Force = false);
};
