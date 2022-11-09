// Fill out your copyright notice in the Description page of Project Settings.


#include "TopdownShooter/System/Equipments/Weapon.h"

#include "TopdownShooter/Character/PlayerCharacter.h"

AWeapon::AWeapon()
{
	equipmentType = EEquipmentType::Weapon1;
	weaponType = EWeaponType::Knife;
}

void AWeapon::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("AWeapon::Attack"));
}

void AWeapon::OnEnable()
{
	UE_LOG(LogTemp, Warning, TEXT("AWeapon::OnEable"));
	
	//!@# 고려사항
	//무기 타입에 따라 애니메이션과 착용 위치가 달라져야 하고,
	//장비 타입에 따라 착용 위치가 달라져야 함
	FName socketName;
	switch (weaponType)
	{
	case EWeaponType::Knife:
		socketName = TEXT("");
		break;
		
	case EWeaponType::Rifle:
		socketName = TEXT("Weapon_Rifle");
		break;
		
	default:
		socketName = TEXT("");
		break;
	}
	
	if(player != nullptr)
	{
		spawnedEquipment->AttachToComponent(
		player->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			socketName);
	}
}

void AWeapon::OnDisable()
{
	UE_LOG(LogTemp, Warning, TEXT("AWeapon::OnDisable"));
	
	if((spawnedEquipment != nullptr) &&
		(player != nullptr))
	{
		spawnedEquipment->AttachToComponent(
		player->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			TEXT("WeaponHolster1"));
	}
}

//애니메이션 구분 등
EWeaponType AWeapon::GetWeaponType()
{
	return weaponType;
}
