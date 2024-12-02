// Copyright Epic Games, Inc. All Rights Reserved.


#include "SandboxGameModeBase.h"

void ASandboxGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Hello world, this is FPSGameMode"));
}
