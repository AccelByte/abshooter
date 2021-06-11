// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Models/ShooterMatchInfoModels.h"
#include "Models/AccelByteMatchmakingModels.h"
#include "ShooterGame_FreeForAll.generated.h"

class AShooterPlayerState;
class AShooterAIController;

UCLASS()
class AShooterGame_FreeForAll : public AShooterGameMode
{
	GENERATED_UCLASS_BODY()

	void PreLogin(const FString & Options, const FString & Address, const FUniqueNetIdRepl & UniqueId, FString & ErrorMessage) override;


	void PostLogin(APlayerController* NewPlayer) override;

	/** initialize replicated game data */
	virtual void InitGameState() override;

	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal = TEXT("")) override;

	virtual void RestartGame() override;
	virtual void EndMatch() override;

protected:

	/** best player */
	UPROPERTY(transient)
	AShooterPlayerState* WinnerPlayerState;

	/** check who won */
	virtual void DetermineMatchWinner() override;

	/** check if PlayerState is a winner */
	virtual bool IsWinner(AShooterPlayerState* PlayerState) const override;

	FAccelByteModelsMatchmakingResult MatchmakingInfo;

public:
	void SetupMatch(const FAccelByteModelsMatchmakingResult& Info);
	bool IsMatchStarted();
	void GetSessionData();
	FShooterMatchInfo GetMatchInfo();

	bool ResetMatch(bool Force = false);
};
