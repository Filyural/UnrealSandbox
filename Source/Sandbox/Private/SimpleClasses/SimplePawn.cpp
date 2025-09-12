// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleClasses/SimplePawn.h"
#include "Components/InputComponent.h"


// Sets default values
ASimplePawn::ASimplePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
}

// Called when the game starts or when spawned
void ASimplePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASimplePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!VelocityVector.IsZero())
	{
		const FVector NewLocation = GetActorLocation() + Velocity * DeltaTime * VelocityVector;
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void ASimplePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);

}


void ASimplePawn::MoveForward(float Amount)
{
	UE_LOG(LogSimplePawn, Display, TEXT("Move forward %i"), Amount);
	VelocityVector.X = Amount;
}


void ASimplePawn::MoveRight(float Amount)
{
	UE_LOG(LogSimplePawn, Display, TEXT("Move right %i"), Amount);
	VelocityVector.Y = Amount;
}
