// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedCoinGameMode.h"
#include "AdvancedCoinGameState.h"
#include "AdvCoinPlayerState.h"

AAdvancedCoinGameMode::AAdvancedCoinGameMode()
{
	WinningScore = 3;
	teamIndex = 1;
	WinningID = 0;
}

void AAdvancedCoinGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer)
	{
		AAdvCoinPlayerState* CoinPlayerState = Cast<AAdvCoinPlayerState>(NewPlayer->PlayerState);
		//ACoinGameState* GS = Cast<ACoinGameState>(GameState);

		//check(GS);

		if (CoinPlayerState)
		{
			uint8 NumTeamA = 0;
			uint8 NumTeamB = 0;

			for (APlayerState * It : GameState->PlayerArray)
			{
				UE_LOG(LogTemp, Warning, TEXT("%d"), GameState->PlayerArray.Num());
				AAdvCoinPlayerState* OtherPS = Cast<AAdvCoinPlayerState>(It);

				if (OtherPS)
				{

					if (NumTeamA == 0 || NumTeamA == NumTeamB)
					{
						OtherPS->SetTeamID(1);
						NumTeamA++;
					}
					else if (NumTeamA > NumTeamB)
					{
						OtherPS->SetTeamID(2);
						NumTeamB++;
					}
				}
			}
		}
	}
}

void AAdvancedCoinGameMode::CheckScore()
{
	AAdvancedCoinGameState* GS = Cast<AAdvancedCoinGameState>(GameState);

	if (GS)
	{
		if (GS->GetRedTeamScore() == WinningScore)
		{
			WinningID = 1;
			GS->SetWinnerID(WinningID);
			// call override function now available from parent class
			FinishMatch();
		}

		else if (GS->GetBlueTeamScore() == WinningScore)
		{
			WinningID = 2;
			GS->SetWinnerID(WinningID);
			FinishMatch();
		}
	}
}

void AAdvancedCoinGameMode::FinishMatch()
{
	AAdvancedCoinGameState* GS = Cast<AAdvancedCoinGameState>(GameState);

	if (GS)
	{

		UE_LOG(LogTemp, Warning, TEXT("Ending the match"));

		if (WinningID == 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Red Team Wins"));			
		}

		else if (WinningID == 2)
		{
			UE_LOG(LogTemp, Warning, TEXT("Blue Team Wins"));			
		}

		GS->MulticastDisplayGameOverWidgets();
	}	
}

void AAdvancedCoinGameMode::AddScore(int32 point, int32 teamID)
{

	UE_LOG(LogTemp, Warning, TEXT("Team ID %d, has scored a point"), teamID)

	// Update the game state to show team score information in UI

	AAdvancedCoinGameState* GS = Cast<AAdvancedCoinGameState>(GameState);

	if (GS)
	{
		GS->SetTeamScore(point, teamID);
	}

	CheckScore();
}
