// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.generated.h"

UCLASS()
class SANDBOX_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, Category="Inventory")
	int32 ActiveSlotsNumber = 17;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int32 InventorySize = 21;

	UPROPERTY(EditInstanceOnly, Category = "Health")
	float Health = 7.3f;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	bool bIsAlive = true;

	UPROPERTY(EditAnywhere, Category = "Movement")
	bool bCanSprint = Health >= 3.5f;

private:
	void TestExampleLog1();
	void TestExampleLog2();
};
