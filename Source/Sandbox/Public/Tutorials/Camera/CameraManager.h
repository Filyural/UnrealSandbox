// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraManager.generated.h"

USTRUCT(BlueprintType)
struct FCameraContainer
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Time")
	AActor* Camera;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Time")
	float TimeBetweenCameraChanges = 2.0f;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Time")
	float SmoothBlendTime = 0.75f;

};

UCLASS()
class SANDBOX_API ACameraManager : public AActor
{
	GENERATED_BODY()
	
public:	

	ACameraManager();

	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TArray<FCameraContainer> CameraContainers;

	float TimeToNextCameraChange;
	int32 CurrentCameraIndex = 0;

	virtual void BeginPlay() override;

};
