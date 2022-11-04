// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TopdownShooter/System/Equipments/Weapon.h"
#include "MeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API AMeleeWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	virtual void Attack() override;

protected:
	void MeleeAttack();
};
