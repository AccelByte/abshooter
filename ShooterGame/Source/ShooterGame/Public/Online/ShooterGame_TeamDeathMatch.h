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

	virtual void RestartGame() override;
	virtual void EndMatch() override;

protected:

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
	void SetupMatch(const FAccelByteModelsMatchmakingInfo& Info);
	bool SetupSecondParty(const FAccelByteModelsMatchmakingInfo& Info);
	bool IsMatchStarted();
};
