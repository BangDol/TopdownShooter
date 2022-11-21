// Fill out your copyright notice in the Description page of Project Settings.


#include "TopdownShooter/Character/PlayerCharacterAnimInstance.h"

#include "PlayerCharacter.h"

UPlayerCharacterAnimInstance::UPlayerCharacterAnimInstance()
{
}

void UPlayerCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	player = Cast<APlayerCharacter>(owner);
}

void UPlayerCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//애니메이션을 위한 플레이어 상태
	if(player != nullptr)
	{
		//pcState = player->GetPCState();
		holdingWeaponType = player->GetHoldingWeaponType();
	}
}
