// Fill out your copyright notice in the Description page of Project Settings.


#include "TopdownShooter/System/Equipments/EquipmentComponent.h"
#include "Equipment.h"
#include "Weapon.h"

UEquipmentComponent::UEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	for(int i = 0; i < (int)EEquipmentType::Count; i++)
	{
		equipments.Add(0);
	}
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	//Init();
}

void UEquipmentComponent::Init()
{
	//플레이어 세팅
	//player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UEquipmentComponent::AddEquipment(AEquipment* _equipment, EEquipmentType _index)
{
	equipments.Insert(_equipment, (int)_index);
}

void UEquipmentComponent::RemoveEquipment(EEquipmentType _index)
{
	equipments.Insert(nullptr, (int)_index);
}


AWeapon* UEquipmentComponent::GetEquippedWeapon()
{
	//!@# 무기 선택 고려
	AWeapon* equippedWeapon = Cast<AWeapon>(equipments[(int)EEquipmentType::Weapon]);
	
	return equippedWeapon;
}
