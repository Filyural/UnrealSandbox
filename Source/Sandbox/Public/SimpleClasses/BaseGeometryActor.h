// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

#include "BaseGeometryActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChangedSignature, const FLinearColor&, Color, const FString&, Name);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinishedSignature, AActor*);

UENUM(BlueprintType)
enum class ESimpleMovementType : uint8
{
	Static,
	Sin
};

USTRUCT(BlueprintType)
struct FSimpleData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	ESimpleMovementType MovementType = ESimpleMovementType::Static;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	FLinearColor Color = FLinearColor::Black;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Movement", meta = (EditCondition = "MovementType == ESimpleMovementType::Sin"))
	float Amplitude = 50.0f;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Movement", meta = (EditCondition = "MovementType == ESimpleMovementType::Sin"))
	float Frequency = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Design", meta = (EditCondition = "MovementType == ESimpleMovementType::Static"))
	float TimerRate = 3.0f;

	FString ToString() const
	{
		FString MainStr = FString::Printf(TEXT(" \nMovementType: %s; Color: %s;\n"), *FString(MovementType == ESimpleMovementType::Static ? "Static" : "Sin"), *Color.ToString());
		FString AdditionalStr = FString::Printf(TEXT("Amplitude: %.2f; Frequency: %.2f; TimeRate: %.2f;"), Amplitude, Frequency, TimerRate);

		return MainStr + (MovementType == ESimpleMovementType::Static ? AdditionalStr : FString(""));
	}
};

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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	UPROPERTY(BlueprintAssignable)
	FOnColorChangedSignature OnColorChanged;

	FOnTimerFinishedSignature OnTimerFinished;

	void SetSimpleData(const FSimpleData& Data) { SimpleData = Data; }

	UFUNCTION(BlueprintCallable)
	FSimpleData GetSimpleData() const { return SimpleData; }
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	//Components
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	//BaseFields
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Data")
	FSimpleData SimpleData;

	UPROPERTY(EditAnywhere, Category = "Timer", meta = (ToolTip = "-1 equals infinity"))
	int32 MaxTimerCount = 5;

	//UPROPERTY(EditAnywhere, Category="Inventory")
	//int32 ActiveSlotsNumber = 17;

	//UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	//int32 InventorySize = 21;

	//UPROPERTY(EditInstanceOnly, Category = "Health")
	//float Health = 7.3f;

	//UPROPERTY(VisibleAnywhere, Category = "Health")
	//bool bIsAlive = true;

	//UPROPERTY(EditAnywhere, Category = "Movement")
	//bool bCanSprint = Health >= 3.5f;

private:

	FVector InitialLocation;
	FTimerHandle TimerHandle;

	int32 CurrentTimerCount = 0;

	//void TestExampleLog1();
	//void TestExampleLog2();
	//void TransformLog();
	void MovementHandle();
	void SetColor(const FLinearColor& ColorToSet);

	void OnTimerFired();
};
