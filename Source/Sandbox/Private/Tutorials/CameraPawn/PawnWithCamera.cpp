// Fill out your copyright notice in the Description page of Project Settings.


#include "Tutorials/CameraPawn/PawnWithCamera.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
APawnWithCamera::APawnWithCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	StaticMesh->SetupAttachment(RootComponent);
	SpringArmComp->SetupAttachment(StaticMesh);
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	SpringArmComp->TargetArmLength = 400.0f;
	//SpringArmComp->SocketOffset = FVector(0.0f, 20.0f, 50.0f);
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 3.0f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APawnWithCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//ZOOM
	if (bZoomingIn)
	{
		ZoomFactor += DeltaTime / 0.5f;
	}
	else
	{
		ZoomFactor -= DeltaTime / 0.25f;
	}
	ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);

	CameraComp->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
	SpringArmComp->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);

	//TURN RIGHT
	FRotator NewRotationX = GetActorRotation();
	NewRotationX.Yaw += CameraInput.X;
	SetActorRotation(NewRotationX);

	//LOOK UP
	FRotator NewRotationY = SpringArmComp->GetComponentRotation();
	NewRotationY.Pitch = FMath::Clamp(NewRotationY.Pitch + CameraInput.Y, -80.0f, -15.0f);
	SpringArmComp->SetWorldRotation(NewRotationY);

	//MOVING
	if (!MovementInput.IsZero())
	{
		MovementInput = MovementInput.GetSafeNormal() * 100.0f;
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
		NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;

		SetActorLocation(NewLocation);
	}

}

// Called to bind functionality to input
void APawnWithCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APawnWithCamera::ZoomIn);
	InputComponent->BindAction("ZoomIn", IE_Released, this, &APawnWithCamera::ZoomOut);

	InputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);
	InputComponent->BindAxis("LookUp", this, &ThisClass::LookUp);
	InputComponent->BindAxis("TurnRight", this, &ThisClass::TurnRight);
}

void APawnWithCamera::MoveForward(float Amount)
{
	MovementInput.X = FMath::Clamp<float>(Amount, -1.0f, 1.0f);
}

void APawnWithCamera::MoveRight(float Amount)
{
	MovementInput.Y = FMath::Clamp<float>(Amount, -1.0f, 1.0f);
}

void APawnWithCamera::LookUp(float Amount)
{
	CameraInput.Y = Amount;
}

void APawnWithCamera::TurnRight(float Amount)
{
	CameraInput.X = Amount;
}

void APawnWithCamera::ZoomIn()
{
	bZoomingIn = true;
}

void APawnWithCamera::ZoomOut()
{
	bZoomingIn = false;
}