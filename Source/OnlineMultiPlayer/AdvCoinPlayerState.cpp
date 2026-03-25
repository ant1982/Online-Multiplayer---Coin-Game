// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvCoinPlayerState.h"
#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"

AAdvCoinPlayerState::AAdvCoinPlayerState()
{
	teamID = 1;
	playerScore = 0;
}

void AAdvCoinPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAdvCoinPlayerState, teamID);
	DOREPLIFETIME(AAdvCoinPlayerState, playerScore);

	// optimise for client/server usage by setting condition on one object

	//DOREPLIFETIME_CONDITION(AFPSCharacter, bIsCarryingObjective, COND_OwnerOnly);
}
