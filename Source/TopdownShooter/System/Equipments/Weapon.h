// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TopdownShooter/System/Equipments/Equipment.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API AWeapon : public AEquipment
{
	GENERATED_BODY()

public:
	AWeapon();
	
	virtual void Attack();
};
