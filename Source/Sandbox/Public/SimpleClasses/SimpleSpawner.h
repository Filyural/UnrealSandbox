// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.h"

#include "SimpleSpawner.generated.h"


USTRUCT(BlueprintType)
struct FGeometryPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "SpawnActor")
	TSubclassOf<ABaseGeometryActor> ClassToSpawn;

	UPROPERTY(EditAnywhere, Category = "ActorParams")
	FSimpleData Data;

	UPROPERTY(EditAnywhere, Category = "ActorParams")
	FTransform InitialTransform;
};

UCLASS()
class SANDBOX_API ASimpleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimpleSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, Category = "SpawnActor")
	TArray<FGeometryPayload> GeometryPayloads;

	UPROPERTY(EditAnywhere, Category = "SpawnActor")
	TSubclassOf<ABaseGeometryActor> ClassToSpawnSingle;

	void SpawnActorSingle(const FTransform& Transform, const FSimpleData& Data);
	void SpawnActorSingleDeferred(const FTransform& Transform, const FSimpleData& Data);
	void SpawnActorsArray();

	UFUNCTION()
	void OnColorChanged(const FLinearColor& Color, const FString& Name);
	void OnTimerFinished(AActor* Actor);
};
