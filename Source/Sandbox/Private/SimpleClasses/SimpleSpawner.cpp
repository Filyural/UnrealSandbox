// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleClasses/SimpleSpawner.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogSimpleSpawner, All, All)

// Sets default values
ASimpleSpawner::ASimpleSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASimpleSpawner::BeginPlay()
{
	Super::BeginPlay();

	//SpawnActorSingle(FTransform(FRotator::ZeroRotator, FVector::ZeroVector), FSimpleData());
	//SpawnActorSingleDeferred(FTransform(FRotator::ZeroRotator, FVector::ZeroVector), FSimpleData());
	SpawnActorsArray();
}

// Called every frame
void ASimpleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASimpleSpawner::SpawnActorSingle(const FTransform& Transform, const FSimpleData& Data)
{
	UWorld* World = GetWorld();
	if (!World) { return; }

	ABaseGeometryActor* Actor = World->SpawnActor<ABaseGeometryActor>(ClassToSpawnSingle, Transform);
	if (!Actor) { return; }

	//Set data after spawning
	Actor->SetSimpleData(Data);

}

void ASimpleSpawner::SpawnActorSingleDeferred(const FTransform& Transform, const FSimpleData& Data)
{
	UWorld* World = GetWorld();
	if (!World) { return; }

	ABaseGeometryActor* Actor = World->SpawnActorDeferred<ABaseGeometryActor>(ClassToSpawnSingle, Transform);
	if (!Actor) { return; }

	//Set data before spawning
	Actor->SetSimpleData(Data);

	Actor->FinishSpawning(Transform);

}

void ASimpleSpawner::SpawnActorsArray()
{
	UWorld* World = GetWorld();
	if (!World) { return; }

	for (const FGeometryPayload& Payload : GeometryPayloads)
	{
		ABaseGeometryActor* Actor = World->SpawnActorDeferred<ABaseGeometryActor>(Payload.ClassToSpawn, Payload.InitialTransform);
		if (!Actor) { continue; }

		Actor->SetSimpleData(Payload.Data);
		Actor->OnColorChanged.AddDynamic(this, &ThisClass::OnColorChanged);
		Actor->OnTimerFinished.AddUObject(this, &ASimpleSpawner::OnTimerFinished);
		Actor->FinishSpawning(Payload.InitialTransform);
	}
}

void ASimpleSpawner::OnColorChanged(const FLinearColor& Color, const FString& Name)
{
	UE_LOG(LogSimpleSpawner, Warning, TEXT("Actor name: %s, Color %i"), *Name, *Color.ToString());
}

void ASimpleSpawner::OnTimerFinished(AActor* Actor)
{
	if (!Actor) { return; }
	UE_LOG(LogSimpleSpawner, Error, TEXT("Timer finished: %s"), *Actor->GetName());

	ABaseGeometryActor* SimpleActor = Cast<ABaseGeometryActor>(Actor);
	if (!SimpleActor) { return; }
	UE_LOG(LogSimpleSpawner, Error, TEXT(" \nSimple Data: %s"), *(SimpleActor->GetSimpleData().ToString()));

	SimpleActor->Destroy();
	//SimpleActor->SetLifeSpan(2.9f);
}

