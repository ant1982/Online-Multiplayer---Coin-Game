// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedCoinGameState.h"
#include "AdvancedCoinGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "AdvPlayerController.h"


AAdvancedCoinGameState::AAdvancedCoinGameState()
{
	RedTeamTotal = 0;
	BlueTeamTotal = 0;
	winnerID = 0;
}

int32 AAdvancedCoinGameState::GetBlueTeamScore()
{
	return BlueTeamTotal;
}

int32 AAdvancedCoinGameState::GetRedTeamScore()
{
	return RedTeamTotal;
}

void AAdvancedCoinGameState::SetTeamScore(int32 Delta, int32 teamID)
{
	if (teamID == 1)
	{
		RedTeamTotal += Delta;
	}

	else if (teamID == 2)
	{
		BlueTeamTotal += Delta;
	}
}

void AAdvancedCoinGameState::MulticastDisplayGameOverWidgets_Implementation()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		AAdvPlayerController* PC = Cast<AAdvPlayerController>(It->Get());

		if (PC && PC->IsLocalController())
		{
			PC->OnMatchCompleted();
		}
	}
}

void AAdvancedCoinGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAdvancedCoinGameState, RedTeamTotal);
	DOREPLIFETIME(AAdvancedCoinGameState, BlueTeamTotal);
	DOREPLIFETIME(AAdvancedCoinGameState, winnerID);
}