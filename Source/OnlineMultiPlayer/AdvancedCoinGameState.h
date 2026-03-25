// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "AdvancedCoinGameState.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEMULTIPLAYER_API AAdvancedCoinGameState : public AGameState
{
	GENERATED_BODY()
	
	UPROPERTY(Replicated)
		int32 RedTeamTotal;

	UPROPERTY(Replicated)
		int32 BlueTeamTotal;

public:

	AAdvancedCoinGameState();

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "Team Score")
		int32 GetBlueTeamScore();

	UFUNCTION(BlueprintCallable, Category = "Team Score")
		int32 GetRedTeamScore();

	UFUNCTION()
		void SetTeamScore(int32 Delta, int32 teamID);

	UFUNCTION()
		void SetWinnerID(int32 winner) { winnerID = winner; }

	UFUNCTION(BlueprintCallable, Category = "Match")
		int32 GetWinnerID() { return winnerID; }

	UFUNCTION(NetMulticast, Reliable)
		void MulticastDisplayGameOverWidgets();

private:

	UPROPERTY(Replicated)
		int32 winnerID;

};
