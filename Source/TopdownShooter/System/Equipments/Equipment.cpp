// Fill out your copyright notice in the Description page of Project Settings.


#include "TopdownShooter/System/Equipments/Equipment.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TopdownShooter/Character/PlayerCharacter.h"

AEquipment::AEquipment()
{
	socketName = TEXT("");
}

void AEquipment::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void AEquipment::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
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
	SpawnEquipmentOnPlayer();
}

void AEquipment::OnUnequip()
{
	if(spawnedEquipment != nullptr)
	{
		spawnedEquipment->Destroy();
	}
}

FName AEquipment::GetSocketName()
{
	switch(equipmentType)
	{
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

void AEquipment::SpawnEquipmentOnPlayer()
{
	if(player != nullptr)
	{
		socketName = GetSocketName();
		FActorSpawnParameters actorSpawnParam;

		//###주의###
		//spawnedEquipment는 다른 객체이므로 정보 전달 필수
		//!@# 스폰 방식을 다르게 하는 등 개선 여지 있음
		spawnedEquipment = GetWorld()->SpawnActor<AEquipment>(this->GetClass(), actorSpawnParam);
		spawnedEquipment->AttachToComponent(
			player->GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			socketName);
		
		spawnedEquipment->SetInteractionCollsion(false);
	}
}

void AEquipment::SetInteractionCollsion(bool isInteractable)
{
	if(isInteractable)
	{
		interactionCollision->SetCollisionResponseToChannel(
			ECollisionChannel::ECC_GameTraceChannel1,
			ECollisionResponse::ECR_Block);
	}
	else
	{
		interactionCollision->SetCollisionResponseToChannel(
			ECollisionChannel::ECC_GameTraceChannel1,
			ECollisionResponse::ECR_Ignore);
	}	
}
