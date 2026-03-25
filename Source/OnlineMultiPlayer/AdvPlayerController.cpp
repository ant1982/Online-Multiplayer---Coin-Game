// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "AdvCoinPlayerState.h"
#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"

void AAdvPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Widget begin play"));

	AAdvCoinPlayerState* PS = Cast<AAdvCoinPlayerState>(PlayerState);

	if (PS)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player State found"));
		int32 widgetID = PS->GetTeamID();
		UE_LOG(LogTemp, Warning, TEXT("widgetID: %d"), widgetID);
		SetTeamID(widgetID);
	}

}

void AAdvPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAdvPlayerController, currentTeamID);
}