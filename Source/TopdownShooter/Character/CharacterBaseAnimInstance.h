// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterBaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API UCharacterBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	class ACharacterBase* owner;

	UPROPERTY(BlueprintReadOnly)
	float speed;
	UPROPERTY(BlueprintReadOnly)
	float direction;

public:
	UCharacterBaseAnimInstance();
	
protected:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;
};
