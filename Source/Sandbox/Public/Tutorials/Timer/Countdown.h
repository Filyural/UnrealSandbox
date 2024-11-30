// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Countdown.generated.h"

UCLASS()
class SANDBOX_API ACountdown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountdown();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	//Base duration value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	int32 CountdownTime;
	UTextRenderComponent* CountdownText;

	FTimerHandle CountdownTimerHandle;

	UFUNCTION(BlueprintNativeEvent)
	void CountdownHasFinished();
	virtual void CountdownHasFinished_Implementation();

	void AdvanceTimer();
	void UpdateTimerDisplay();


};
