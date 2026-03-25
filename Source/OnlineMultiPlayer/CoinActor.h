// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoinActor.generated.h"

UCLASS()
class ONLINEMULTIPLAYER_API ACoinActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
		int32 scoringTeamID;
	
public:	
	// Sets default values for this actor's properties
	ACoinActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Coin")
		class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Coin")
		class USphereComponent* TriggerSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
		bool bRotate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Coin")
		float RotationRate;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay")
		int32 CoinValue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
