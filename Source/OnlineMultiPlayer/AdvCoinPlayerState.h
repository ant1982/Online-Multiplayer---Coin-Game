// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AdvCoinPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEMULTIPLAYER_API AAdvCoinPlayerState : public APlayerState
{
	GENERATED_BODY()

		AAdvCoinPlayerState();

public:

	UFUNCTION(BlueprintCallable, Category = "Team")
		int32 GetTeamID() { return teamID; }

	void SetTeamID(int32 team) { teamID = team; }

	void SetPlayerScore(int32 delta) { playerScore += delta; }

	UFUNCTION(BlueprintCallable, Category = "Player Score")
		int32 GetPlayerScore() { return playerScore; }

private:

	UPROPERTY(Transient, Replicated)
		int32 teamID;

	UPROPERTY(Replicated)
		int32 playerScore;
	
};
