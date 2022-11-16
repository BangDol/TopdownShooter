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
	FName socketNameForHolding;
	
	switch (weaponType)
	{
	case EWeaponType::Knife:
		socketNameForHolding = TEXT("Weapon_Knife");
		break;
		
	case EWeaponType::Rifle:
		socketNameForHolding = TEXT("Weapon_Rifle");
		break;
		
	default:
		socketNameForHolding = TEXT("");
		break;
	}
	
	if(player != nullptr)
	{
		spawnedEquipment->AttachToComponent(
		player->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			socketNameForHolding);
	}
}

void AWeapon::OnDisable()
{
	UE_LOG(LogTemp, Warning, TEXT("AWeapon::OnDisable"));
	
	if((spawnedEquipment != nullptr) &&
		(player != nullptr))
	{
		socketName = GetSocketName();
		
		spawnedEquipment->AttachToComponent(
		player->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			socketName);
	}
}

//애니메이션 구분 등
EWeaponType AWeapon::GetWeaponType()
{
	return weaponType;
}

FName AWeapon::GetSocketName()
{
	//!@# 양손 무기, 권총 등 추가 시 고려
	if(weaponType == EWeaponType::Knife)
	{
		socketName = TEXT("KnifeHolster");
	}
	else
	{
		if(equipmentType == EEquipmentType::Weapon1)
		{
			socketName = TEXT("WeaponHolster1");
		}
		else if (equipmentType == EEquipmentType::Weapon2)
		{
			socketName = TEXT("WeaponHolster2");
		}
	}

	return socketName;
}
