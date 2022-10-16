// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TopdownShooterGameMode.generated.h"

UCLASS(minimalapi)
class ATopdownShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UMG)
	TSubclassOf<UUserWidget> playerUIClass;

	UPROPERTY()
	UUserWidget* playerUI;

public:
	ATopdownShooterGameMode();
	
protected:
	virtual void BeginPlay() override;	

public:
	void InitUI();

	UFUNCTION(BlueprintCallable)
	UUserWidget* GetPlayerUI();
};



