// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TopdownShooter/System/Equipments/Weapon.h"
#include "RangeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API ARangeWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	virtual void Attack() override;

protected:
	void Fire();
	void Reload();
};
