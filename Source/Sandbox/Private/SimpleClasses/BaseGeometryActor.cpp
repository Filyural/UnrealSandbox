// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleClasses/BaseGeometryActor.h"

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	TestExampleLog();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseGeometryActor::TestExampleLog()
{
	UE_LOG(LogTemp, Display, TEXT("Hello, Unreal!"));
	UE_LOG(LogTemp, Warning, TEXT("Hello, Unreal!"));
	UE_LOG(LogTemp, Error, TEXT("Hello, Unreal!"));

	int InventorySize = 21;
	int ActiveSlotsNumber = 17;
	float Health = 7.3f;
	bool bIsAlive = true;
	bool bCanSprint = Health >= 3.5f;

	UE_LOG(LogTemp, Warning, TEXT("Now you have %d from %i available inventory slots."), ActiveSlotsNumber, InventorySize);
	UE_LOG(LogTemp, Warning, TEXT("Your health is %.2f. You are %s."), Health, *FString(bIsAlive ? "alive" : "dead"));
	UE_LOG(LogTemp, Warning, TEXT("You %s sprint now!"), *FString(static_cast<int>(bCanSprint) ? "can" : "can't"));
}
