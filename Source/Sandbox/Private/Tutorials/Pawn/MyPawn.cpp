// Fill out your copyright notice in the Description page of Project Settings.


#include "Tutorials/Pawn/MyPawn.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleMesh"));

	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GrowTick(DeltaTime);
	MoveTick(DeltaTime);
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Grow", IE_Pressed, this, &ThisClass::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &ThisClass::StopGrowing);

	InputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);

}

void AMyPawn::MoveForward(float Amount)
{
	CurrentVelocity.X = FMath::Clamp(Amount, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::MoveRight(float Amount)
{
	CurrentVelocity.Y = FMath::Clamp(Amount, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::StartGrowing()
{
	bGrowing = true;
}

void AMyPawn::StopGrowing()
{
	bGrowing = false;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ALO"));
}

void AMyPawn::GrowTick(float DeltaTime)
{
	float CurrentScale = OurVisibleComponent->GetComponentScale().X;

	if (bGrowing)
	{
		CurrentScale += DeltaTime;
	}
	else
	{
		CurrentScale -= (DeltaTime * 0.5f);
	}

	CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
	OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));
}

void AMyPawn::MoveTick(float DeltaTime)
{
	if (!CurrentVelocity.IsZero()) 
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
}