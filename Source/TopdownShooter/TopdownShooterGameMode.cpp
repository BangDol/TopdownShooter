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
	if(playerUIClass != nullptr)
	{
		playerUI = CreateWidget<UUserWidget>(GetWorld(), playerUIClass);
		
		if (playerUI != nullptr)
		{
			playerUI->AddToViewport();
		}
	}
}

UUserWidget* ATopdownShooterGameMode::GetPlayerUI()
{
	if (playerUI != nullptr)
	{
		return playerUI;
	}

	return nullptr;
}


#pragma endregion