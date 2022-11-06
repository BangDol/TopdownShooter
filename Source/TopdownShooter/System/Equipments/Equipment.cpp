// Fill out your copyright notice in the Description page of Project Settings.


#include "TopdownShooter/System/Equipments/Equipment.h"

#include "Kismet/GameplayStatics.h"
#include "TopdownShooter/Character/PlayerCharacter.h"

void AEquipment::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void AEquipment::Init()
{
	//플레이어 세팅
	player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

EEquipmentType AEquipment::GetEquipmentType()
{
	return equipmentType;
}

void AEquipment::OnEquip()
{
	if(player != nullptr)
	{
		FName socketName = GetSocketName();
		FActorSpawnParameters actorSpawnParam;
		
		spawnedEquipment = GetWorld()->SpawnActor<AEquipment>(this->GetClass(), actorSpawnParam);
		spawnedEquipment->AttachToComponent(
			player->GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			socketName);
	}
}

void AEquipment::OnUnequip()
{
	spawnedEquipment->Destroy();
}

FName AEquipment::GetSocketName()
{
	FName socketName;
	
	switch(equipmentType)
	{
	case EEquipmentType::Weapon1:
		socketName = TEXT("WeaponHolster1");
		break;
			
	case EEquipmentType::Weapon2:
		socketName = TEXT("WeaponHolster2");
		break;
			
	case EEquipmentType::Backpack:
		socketName = TEXT("");
		break;
			
	case EEquipmentType::Helmet:
		socketName = TEXT("");
		break;
			
	case EEquipmentType::Armor:
		socketName = TEXT("");
		break;
			
	default:
		socketName = TEXT("");
		break;
	}

	return socketName;
}