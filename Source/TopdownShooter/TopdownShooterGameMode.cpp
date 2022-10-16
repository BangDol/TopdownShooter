// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopdownShooterGameMode.h"

#include "PlayerCharacter.h"
#include "PlayerCharacterController.h"
#include "TopdownShooterCharacter.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerUserWidget.h"
#include "Kismet/GameplayStatics.h"

ATopdownShooterGameMode::ATopdownShooterGameMode()
{
	//DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = APlayerCharacterController::StaticClass();
}

void ATopdownShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void ATopdownShooterGameMode::Init()
{
	player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if(player != nullptr)
	{
		InitUI();
	}
}

#pragma region UI

void ATopdownShooterGameMode::InitUI()
{
	if(playerUIClass != nullptr)
	{
		playerUI = CreateWidget<UPlayerUserWidget>(GetWorld(), playerUIClass);
		
		if (playerUI != nullptr)
		{
			playerUI->AddToViewport();
			//playerUI->SetOwner(player);
		}
	}
}

UPlayerUserWidget* ATopdownShooterGameMode::GetPlayerUI()
{
	if (playerUI != nullptr)
	{
		return playerUI;
	}

	return nullptr;
}

void ATopdownShooterGameMode::UpdateInteractUI(bool b)
{
	playerUI->OnCheckInteractable(b);
}


#pragma endregion
