// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AdvancedCoinGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEMULTIPLAYER_API AAdvancedCoinGameMode : public AGameMode
{
	GENERATED_BODY()

		int32 teamIndex;

protected:

	AAdvancedCoinGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	
	int32 PlayerTeamOne;
	int32 PlayerTeamTwo;

	int32 TeamOneScore;
	int32 TeamTwoScore;

	int32 WinningScore;
	int32 WinningID;


private:

	void CheckScore();

	void FinishMatch();

public:

	void AddScore(int32 point, int32 teamID);

};
