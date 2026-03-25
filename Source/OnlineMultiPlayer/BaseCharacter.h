// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class ONLINEMULTIPLAYER_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UPROPERTY(Replicated, VisibleAnywhere, Category = "Team")
		int32 TeamNumber;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float value);

	void MoveRight(float value);

	void ActionEvent();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerActionEvent();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Team")
		void SetTeamNumber(int32 teamID);

	UFUNCTION(BlueprintCallable, Category = "Team")
		int32 GetTeamNumber();

	UFUNCTION(BlueprintPure, Category = "Score")
		int32 GetCurrentScore();

	UFUNCTION(BlueprintCallable, Category = "Score")
		void SetCurrentScore(int32 DeltaScore);

private:

	UPROPERTY(Replicated, VisibleAnywhere, Category = "Score")
		int currentscore;
};
