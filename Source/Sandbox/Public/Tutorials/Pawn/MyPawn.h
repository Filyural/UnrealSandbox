// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class SANDBOX_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* OurVisibleComponent;

	FVector CurrentVelocity = FVector(0.0f, 0.0f, 0.0f);
	bool bGrowing = false;

	virtual void BeginPlay() override;

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void StartGrowing();
	void StopGrowing();

private:

	void GrowTick(float DeltaTime);
	void MoveTick(float DeltaTime);

};
