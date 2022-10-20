// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBaseAnimInstance.h"

#include "CharacterBase.h"
#include "Kismet/KismetMathLibrary.h"

UCharacterBaseAnimInstance::UCharacterBaseAnimInstance()
{
	speed = 0.f;
	direction = 0.f;
}

void UCharacterBaseAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	
	owner = Cast<ACharacterBase>(TryGetPawnOwner());
}

void UCharacterBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	

	if(owner != nullptr)
	{
		speed = owner->GetVelocity().Size();
		direction = CalculateDirection(owner->GetVelocity(), owner->GetActorRotation());
	}
}
