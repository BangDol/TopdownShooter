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
	class UPlayerUserWidget* playerUI;

	class APlayerCharacter* player;

public:
	ATopdownShooterGameMode();
	
protected:
	virtual void BeginPlay() override;
	void Init();
	void InitUI();
	
public:
	UFUNCTION(BlueprintCallable)
	UPlayerUserWidget* GetPlayerUI();

	void UpdateInteractUI(bool b);
};



