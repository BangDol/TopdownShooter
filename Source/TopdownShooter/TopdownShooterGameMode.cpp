// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopdownShooterGameMode.h"

#include "PlayerCharacter.h"
#include "PlayerCharacterController.h"
#include "TopdownShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATopdownShooterGameMode::ATopdownShooterGameMode()
{
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Assets/Characters/PlayerCharacter"));

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
	PlayerControllerClass = APlayerCharacterController::StaticClass();
}