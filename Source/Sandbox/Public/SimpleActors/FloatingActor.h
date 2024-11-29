// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h"

UCLASS()
class SANDBOX_API AFloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AFloatingActor();

	virtual void Tick(float DeltaTime) override;


protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float Amplitude = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float RotationSpeed = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float FloatingSpeed = 2.0f;

	virtual void BeginPlay() override;

private:
	float RunningTime = 0.0f;
	FVector BeginLocation;
};
