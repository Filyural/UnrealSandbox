// Copyright Epic Games, Inc. All Rights Reserved.


#include "SandboxGameModeBase.h"
#include "SimpleClasses/SimplePawn.h"


ASandboxGameModeBase::ASandboxGameModeBase()
{
	DefaultPawnClass = ASimplePawn::StaticClass();

}