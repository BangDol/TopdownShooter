// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopdownShooterGameMode.h"
#include "TopdownShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATopdownShooterGameMode::ATopdownShooterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Assets/Characters/PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}