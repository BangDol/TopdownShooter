// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TopdownShooterGameMode.generated.h"

UCLASS(minimalapi)
class ATopdownShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class APlayerCharacter* playerCharacter;
	
public:
	ATopdownShooterGameMode();
};



