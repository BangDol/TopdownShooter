// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopdownShooterGameMode.h"

#include "PlayerCharacter.h"
#include "PlayerCharacterController.h"
#include "TopdownShooterCharacter.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

ATopdownShooterGameMode::ATopdownShooterGameMode()
{
	//DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = APlayerCharacterController::StaticClass();
}

void ATopdownShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitUI();
}

#pragma region UI

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


#pragma endregion