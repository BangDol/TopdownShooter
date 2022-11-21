// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TopdownShooter/Character/CharacterBaseAnimInstance.h"
#include "EnemyCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API UEnemyCharacterAnimInstance : public UCharacterBaseAnimInstance
{
	GENERATED_BODY()

public:
	UEnemyCharacterAnimInstance();
	
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
