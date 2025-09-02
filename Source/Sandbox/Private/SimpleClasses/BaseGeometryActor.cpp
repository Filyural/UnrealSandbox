// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleClasses/BaseGeometryActor.h"
#include "Engine/Engine.h"

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

	//TestExampleLog1();
	//TestExampleLog2();

	//TransformLog();

	InitialLocation = GetActorLocation();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	const auto World = GetWorld();
	if (!World) { return; }
	float Time = World->GetTimeSeconds();
	CurrentLocation.Z = InitialLocation.Z + MovementData.Amplitude * FMath::Sin(MovementData.Frequency * Time);
	
	SetActorLocation(CurrentLocation);
}

void ABaseGeometryActor::TestExampleLog1()
{
	//UE_LOG(LogTemp, Display, TEXT("Hello, Unreal!"));
	//UE_LOG(LogTemp, Warning, TEXT("Hello, Unreal!"));
	//UE_LOG(LogTemp, Error, TEXT("Hello, Unreal!"));
	
	UE_LOG(LogBaseGeometry, Error, TEXT("Actor name: %s"), *GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Now you have %d from %i available inventory slots."), ActiveSlotsNumber, InventorySize);
	UE_LOG(LogBaseGeometry, Warning, TEXT("Your health is %.2f. You are %s."), Health, *FString(bIsAlive ? "alive" : "dead"));
	UE_LOG(LogBaseGeometry, Warning, TEXT("You %s sprint now!"), *FString(static_cast<int>(bCanSprint) ? "can" : "can't"));
}

void ABaseGeometryActor::TestExampleLog2()
{
	FName CompanyName = "FLT";
	int32 EmployeesNumber = 20;
	float CompanyRatio = 0.74f;
	bool bIsGlobal = true;

	FString CompanyNameStr = "Company name: " + CompanyName.ToString();
	FString EmployeesNumberStr = "Number of employees: " + FString::FromInt(EmployeesNumber);
	FString CompanyRatioStr = "Company productivity ratio: " + FString::SanitizeFloat(CompanyRatio);
	FString IsGlobalStr = FString("Company is ") + (bIsGlobal ? "Global" : "Local");

	FString LogStr = FString::Printf(TEXT(" \nAll info:\n\t%s\n\t%s\n\t%s\n\t%s"), *CompanyNameStr, *EmployeesNumberStr, *CompanyRatioStr, *IsGlobalStr);
	UE_LOG(LogBaseGeometry, Display, TEXT("%s"), *LogStr);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Red, FString("Example Warning!"));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, LogStr, true, FVector2D(1.2f, 1.2f));
	}
}

void ABaseGeometryActor::TransformLog()
{
	FTransform Transform = GetActorTransform();
	FVector Location = Transform.GetLocation();
	FRotator Rotation = Transform.Rotator();
	FVector Scale = Transform.GetScale3D();

	UE_LOG(LogBaseGeometry, Error, TEXT("Name: %s"), *GetName());
	UE_LOG(LogBaseGeometry, Display, TEXT("Transform: %s"), *Transform.ToString());
	UE_LOG(LogBaseGeometry, Display, TEXT("Location: %s"), *Location.ToString());
	UE_LOG(LogBaseGeometry, Display, TEXT("Rotation: %s"), *Rotation.ToString());
	UE_LOG(LogBaseGeometry, Display, TEXT("Scale: %s"), *Scale.ToString());
	UE_LOG(LogBaseGeometry, Error, TEXT("f\nConvenient Transform:\n%s"), *Transform.ToHumanReadableString());

}
