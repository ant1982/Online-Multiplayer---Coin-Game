// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AdvancedCoinGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "AdvCoinPlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	TeamNumber = 0;
	currentscore = 0;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	TeamNumber = GetTeamNumber();
}

void ABaseCharacter::MoveForward(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void ABaseCharacter::MoveRight(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, value);
	}
}

void ABaseCharacter::ActionEvent()
{
	ServerActionEvent();
}

void ABaseCharacter::ServerActionEvent_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Game mode found"));

	AAdvancedCoinGameMode* GM = Cast<AAdvancedCoinGameMode>(GetWorld()->GetAuthGameMode());

	if (GM)
	{
		UE_LOG(LogTemp, Warning, TEXT("Use Action event"));		
	}
}

bool ABaseCharacter::ServerActionEvent_Validate()
{
	return true;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind Axis events

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &ABaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ABaseCharacter::AddControllerPitchInput);

	// Bind Action events

	PlayerInputComponent->BindAction("Use", IE_Pressed, this, &ABaseCharacter::ActionEvent);
}

void ABaseCharacter::SetTeamNumber(int32 teamID)
{
	TeamNumber = teamID;
}

int32 ABaseCharacter::GetTeamNumber()
{
	AAdvCoinPlayerState* PS = Cast<AAdvCoinPlayerState>(GetPlayerState());

	if (PS)
	{
		TeamNumber = PS->GetTeamID();
	}

	return TeamNumber;
}

int32 ABaseCharacter::GetCurrentScore()
{
	return currentscore;
}

void ABaseCharacter::SetCurrentScore(int32 DeltaScore)
{
	if (HasAuthority())
	{
		currentscore += DeltaScore;
	}
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseCharacter, TeamNumber);
	DOREPLIFETIME(ABaseCharacter, currentscore);

	// optimise for client/server usage by setting condition on one object

	//DOREPLIFETIME_CONDITION(AFPSCharacter, bIsCarryingObjective, COND_OwnerOnly);
}