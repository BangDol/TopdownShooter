// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopdownShooterGameMode.h"
#include "TopdownShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATopdownShooterGameMode::ATopdownShooterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	// 테스트
	}
}
