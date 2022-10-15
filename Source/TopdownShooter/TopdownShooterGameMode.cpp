// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopdownShooterGameMode.h"

#include "PlayerCharacter.h"
#include "PlayerCharacterController.h"
#include "TopdownShooterCharacter.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

ATopdownShooterGameMode::ATopdownShooterGameMode()
{
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Assets/Characters/PlayerCharacter"));

	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
	PlayerControllerClass = APlayerCharacterController::StaticClass();
}

void ATopdownShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitUI();
}

void ATopdownShooterGameMode::InitUI()
{
	if(playerUI != nullptr)
	{
		currentUI = CreateWidget<UUserWidget>(GetWorld(), playerUI);
		
		if (currentUI != nullptr)
		{
			currentUI->AddToViewport();
		}
	}
}

UUserWidget* ATopdownShooterGameMode::GetCurrentUI()
{
	if (currentUI != nullptr)
	{
		return currentUI;
	}

	return nullptr;
}
