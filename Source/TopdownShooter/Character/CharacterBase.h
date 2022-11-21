// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class TOPDOWNSHOOTER_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Settings")
	float health;

public:
	// Sets default values for this character's properties
	ACharacterBase();

	float GetHealth();
	
protected:
	virtual void SubHealth(float damage);
};
