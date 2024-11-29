// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleActors/FloatingActor.h"
#include "Components/StaticMeshComponent.h"

AFloatingActor::AFloatingActor()
{
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (CubeVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
}

void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();

	BeginLocation = GetActorLocation();

}

void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//float RunningTime = GetGameTimeSinceCreation();
	RunningTime += DeltaTime;
	//FVector NewLocation = FVector(BeginLocation.X, BeginLocation.Y, BeginLocation.Z + FMath::Sin(RunningTime) * Multiplier);
	FVector NewLocation = BeginLocation + FVector(0.0f, 0.0f, FMath::Sin(RunningTime * FloatingSpeed) * Amplitude);
	FRotator NewRotation = GetActorRotation() + FRotator(0.0f, RotationSpeed, 0.0f);

	SetActorLocationAndRotation(NewLocation, NewRotation);
}

