// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TopdownShooter/System/Equipments/Equipment.h"
#include "Weapon.generated.h"

UENUM()
enum class EWeaponType : uint8
{
	Knife = 0		UMETA(DisplayName = "Knife"),
	Rifle			UMETA(DisplayName = "Rifle"),
	Count
};

UCLASS()
class TOPDOWNSHOOTER_API AWeapon : public AEquipment
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Settings")
	EWeaponType weaponType;
	
public:
	AWeapon();
	
	virtual void Attack();
	void OnEnable();
	void OnDisable();
};
