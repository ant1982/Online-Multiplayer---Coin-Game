// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AdvancedCoinGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "BaseCharacter.h"
#include "AdvPlayerController.h"
#include "AdvCoinPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "AdvancedCoinGameState.h"

// Sets default values
ACoinActor::ACoinActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));

	RootComponent = TriggerSphere;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	MeshComponent->SetupAttachment(GetRootComponent());

	bRotate = false;

	RotationRate = 30.0f;

	CoinValue = 1;

	scoringTeamID = 0;

	SetReplicates(true);
}

// Called when the game starts or when spawned
void ACoinActor::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &ACoinActor::OnOverlapBegin);
}

// Called every frame
void ACoinActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRotate)
	{
		FRotator Rotation = GetActorRotation();
		Rotation.Yaw += DeltaTime * RotationRate;
		SetActorRotation(Rotation);
	}
}

void ACoinActor::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Role == ROLE_Authority)
	{
		AAdvancedCoinGameMode* GM = Cast<AAdvancedCoinGameMode>(GetWorld()->GetAuthGameMode());

		ABaseCharacter* CoinCharacter = Cast<ABaseCharacter>(OtherActor);

		if (CoinCharacter)
		{
			//CoinCharacter->SetCurrentScore(CoinValue);

			AAdvCoinPlayerState* PS = Cast<AAdvCoinPlayerState>(CoinCharacter->GetPlayerState());

			if (PS)
			{
				int32 teamID = PS->GetTeamID();
				PS->SetPlayerScore(CoinValue);

				UE_LOG(LogTemp, Warning, TEXT("Team ID %d picked up a coin"), teamID);

				if (GM)
				{
					GM->AddScore(CoinValue, teamID);
				}
			}
		}
	}

	SetLifeSpan(0.2f);
}

void ACoinActor::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACoinActor, CoinValue);
}