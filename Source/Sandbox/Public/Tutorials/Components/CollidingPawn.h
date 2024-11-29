// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CollidingMovementComponent.h"
#include "CollidingPawn.generated.h"

UCLASS()
class SANDBOX_API ACollidingPawn : public APawn
{
	GENERATED_BODY()

public:

	ACollidingPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCollidingMovementComponent* OurMovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UParticleSystemComponent* OurParticleSystem;

	virtual void BeginPlay() override;

	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void TurnRight(float Amount);
	void ParticleToggle();

};
