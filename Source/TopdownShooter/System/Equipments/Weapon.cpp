// Fill out your copyright notice in the Description page of Project Settings.


#include "TopdownShooter/System/Equipments/Weapon.h"

AWeapon::AWeapon()
{
	equipmentType = EEquipmentType::Weapon1;
}

void AWeapon::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("AWeapon::Attack"));
}
