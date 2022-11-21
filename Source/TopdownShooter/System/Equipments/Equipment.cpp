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
	SetInteractionCollsion(false);

	AttachEquipmentToPlayer();
}

void AEquipment::OnUnequip()
{
	Destroy();
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

void AEquipment::AttachEquipmentToPlayer()
{
	if(player != nullptr)
	{
		socketName = GetSocketName();

		AttachToComponent(
			player->GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			socketName);
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
