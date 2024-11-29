// Fill out your copyright notice in the Description page of Project Settings.


#include "Tutorials/Camera/CameraManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraManager::ACameraManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACameraManager::BeginPlay()
{
	Super::BeginPlay();

	TimeToNextCameraChange = 2.0f;
}

// Called every frame
void ACameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeToNextCameraChange -= DeltaTime;
	if (TimeToNextCameraChange <= 0.0f)
	{
		TimeToNextCameraChange = CameraContainers[CurrentCameraIndex].TimeBetweenCameraChanges;
		APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);

		if (Controller && CameraContainers[CurrentCameraIndex].Camera)
		{
			Controller->SetViewTargetWithBlend(CameraContainers[CurrentCameraIndex].Camera, CameraContainers[CurrentCameraIndex].SmoothBlendTime);
		}
		CurrentCameraIndex = (CurrentCameraIndex + 1) % CameraContainers.Num();
	}

}

