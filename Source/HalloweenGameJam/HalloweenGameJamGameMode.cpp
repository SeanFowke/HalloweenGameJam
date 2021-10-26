// Copyright Epic Games, Inc. All Rights Reserved.

#include "HalloweenGameJamGameMode.h"
#include "HalloweenGameJamCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHalloweenGameJamGameMode::AHalloweenGameJamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
