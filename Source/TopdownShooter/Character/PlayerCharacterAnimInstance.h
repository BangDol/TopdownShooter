// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "TopdownShooter/Character/CharacterBaseAnimInstance.h"
#include "PlayerCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API UPlayerCharacterAnimInstance : public UCharacterBaseAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	class APlayerCharacter* player;

	UPROPERTY(BlueprintReadOnly)
	FPCState pcState;

protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
