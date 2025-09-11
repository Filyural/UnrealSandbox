// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleClasses/BaseGeometryActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All);

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();

	SetColor(SimpleData.Color);

	if (SimpleData.MovementType == ESimpleMovementType::Static)
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseGeometryActor::OnTimerFired, SimpleData.TimerRate, true);
	}


	//TestExampleLog1();
	//TestExampleLog2();
	//TransformLog();
}

void ABaseGeometryActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogBaseGeometry, Error, TEXT("Actor %s has been destroyed"), *GetName());
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Black, TEXT("DESTROYED"));
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovementHandle();
}

//void ABaseGeometryActor::TestExampleLog1()
//{
//	//UE_LOG(LogTemp, Display, TEXT("Hello, Unreal!"));
//	//UE_LOG(LogTemp, Warning, TEXT("Hello, Unreal!"));
//	//UE_LOG(LogTemp, Error, TEXT("Hello, Unreal!"));
//
//	UE_LOG(LogBaseGeometry, Error, TEXT("Actor name: %s"), *GetName());
//	UE_LOG(LogBaseGeometry, Warning, TEXT("Now you have %d from %i available inventory slots."), ActiveSlotsNumber, InventorySize);
//	UE_LOG(LogBaseGeometry, Warning, TEXT("Your health is %.2f. You are %s."), Health, *FString(bIsAlive ? "alive" : "dead"));
//	UE_LOG(LogBaseGeometry, Warning, TEXT("You %s sprint now!"), *FString(static_cast<int>(bCanSprint) ? "can" : "can't"));
//}

//void ABaseGeometryActor::TestExampleLog2()
//{
//	FName CompanyName = "FLT";
//	int32 EmployeesNumber = 20;
//	float CompanyRatio = 0.74f;
//	bool bIsGlobal = true;
//
//	FString CompanyNameStr = "Company name: " + CompanyName.ToString();
//	FString EmployeesNumberStr = "Number of employees: " + FString::FromInt(EmployeesNumber);
//	FString CompanyRatioStr = "Company productivity ratio: " + FString::SanitizeFloat(CompanyRatio);
//	FString IsGlobalStr = FString("Company is ") + (bIsGlobal ? "Global" : "Local");
//
//	FString LogStr = FString::Printf(TEXT(" \nAll info:\n\t%s\n\t%s\n\t%s\n\t%s"), *CompanyNameStr, *EmployeesNumberStr, *CompanyRatioStr, *IsGlobalStr);
//	UE_LOG(LogBaseGeometry, Display, TEXT("%s"), *LogStr);
//
//	if (GEngine)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Red, FString("Example Warning!"));
//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, LogStr, true, FVector2D(1.2f, 1.2f));
//	}
//}

//void ABaseGeometryActor::TransformLog()
//{
//	FTransform Transform = GetActorTransform();
//	FVector Location = Transform.GetLocation();
//	FRotator Rotation = Transform.Rotator();
//	FVector Scale = Transform.GetScale3D();
//
//	UE_LOG(LogBaseGeometry, Error, TEXT("Name: %s"), *GetName());
//	UE_LOG(LogBaseGeometry, Display, TEXT("Transform: %s"), *Transform.ToString());
//	UE_LOG(LogBaseGeometry, Display, TEXT("Location: %s"), *Location.ToString());
//	UE_LOG(LogBaseGeometry, Display, TEXT("Rotation: %s"), *Rotation.ToString());
//	UE_LOG(LogBaseGeometry, Display, TEXT("Scale: %s"), *Scale.ToString());
//	UE_LOG(LogBaseGeometry, Error, TEXT("f\nConvenient Transform:\n%s"), *Transform.ToHumanReadableString());
//
//}

void ABaseGeometryActor::MovementHandle()
{
	switch (SimpleData.MovementType)
	{
	case ESimpleMovementType::Sin:
	{
		//Location set
		FVector CurrentLocation = GetActorLocation();
		const auto World = GetWorld();
		if (!World) { return; }
		float Time = World->GetTimeSeconds();
		CurrentLocation.Z = InitialLocation.Z + SimpleData.Amplitude * FMath::Sin(SimpleData.Frequency * Time);

		SetActorLocation(CurrentLocation);


		//Color set
		FLinearColor CurrentColor;
		BaseMesh->GetMaterial(0)->GetVectorParameterValue(FHashedMaterialParameterInfo("Color"), CurrentColor);
		float R = CurrentColor.R + 0.01f;
		float G = CurrentColor.G + 0.01f;
		float B = CurrentColor.B + 0.01f;
		if (CurrentColor.R >= 1.0f)
		{
			R = 0;
			G = 0;
			B = 0;
		}

		CurrentColor = FLinearColor(R, G, B, CurrentColor.A);
		//UE_LOG(LogBaseGeometry, Warning, TEXT("%s"), *CurrentColor.ToString());
		SetColor(CurrentColor);

		break;
	}
	case ESimpleMovementType::Static:
		break;
	default:
		break;
	}

}

void ABaseGeometryActor::SetColor(const FLinearColor& ColorToSet)
{
	InitialLocation = GetActorLocation();
	if (!BaseMesh) { return; }
	UMaterialInstanceDynamic* DynMat = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMat)
	{
		DynMat->SetVectorParameterValue("Color", ColorToSet);
	}
}

void ABaseGeometryActor::OnTimerFired()
{
	if (CurrentTimerCount++ < MaxTimerCount) {
		const FLinearColor Color = FLinearColor::MakeRandomColor();
		SetColor(Color);
		OnColorChanged.Broadcast(Color, *GetName());

		UE_LOG(LogBaseGeometry, Display, TEXT("Counter = %i; Color: %s"), CurrentTimerCount, *Color.ToString());
	}
	else
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		OnTimerFinished.Broadcast(this);

		UE_LOG(LogBaseGeometry, Warning, TEXT("Timer has been stopped"));
	}
}
