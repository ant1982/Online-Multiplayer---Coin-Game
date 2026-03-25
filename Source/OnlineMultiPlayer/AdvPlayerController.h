// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AdvPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEMULTIPLAYER_API AAdvPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> HUDOverlayAsset;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		UUserWidget* HUDOverlay;

	UFUNCTION()
		void SetTeamID(int32 teamID) { currentTeamID = teamID; }

	UFUNCTION()
		int32 GetTeamID() { return currentTeamID; }

	UFUNCTION(BlueprintImplementableEvent, Category = "Match States")
		void OnMatchCompleted();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "Team Variable")
		int32 currentTeamID;
};
