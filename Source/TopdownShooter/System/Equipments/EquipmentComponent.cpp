// Fill out your copyright notice in the Description page of Project Settings.


#include "TopdownShooter/System/Equipments/EquipmentComponent.h"
#include "Equipment.h"
#include "Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "TopdownShooter/Character/PlayerCharacter.h"

UEquipmentComponent::UEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	equipments.Init(0, (int)EEquipmentType::Count - 1);
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void UEquipmentComponent::Init()
{
	//플레이어 세팅
	player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UEquipmentComponent::AddEquipment(AEquipment* _equipment, EEquipmentType _index)
{
	//Spawn 후
	FActorSpawnParameters actorSpawnParam;
	actorSpawnParam.Template = _equipment;
	
	equipments[(int)_index] = GetWorld()->SpawnActor<AEquipment>(_equipment->GetClass(), actorSpawnParam);

	//플레이어의 특정 위치에 Attach
	equipments[(int)_index]->OnEquip();
}

void UEquipmentComponent::RemoveEquipment(EEquipmentType _index)
{
	equipments[(int)_index]->OnUnequip();				//플레이어에게서 Destroy
	
	if(holdingWeapon == Cast<AWeapon>(equipments[(int)_index]))		//지우고자 하는 장비가 현재 장착 중인 무기인 경우
	{
		holdingWeapon = nullptr;	//맨손으로
	}
	
	equipments[(int)_index] = nullptr;
}

void UEquipmentComponent::SwapWeapon(EEquipmentType _weaponType)
{
	UE_LOG(LogTemp, Warning, TEXT("Tring To Swap Weapon"));

	AWeapon* weaponToSwap = Cast<AWeapon>(equipments[(int)_weaponType]);
	
	if(holdingWeapon != weaponToSwap)	// 해당 무기를 이미 장착 중인 경우에는 처리하지 않음
	{
		if(holdingWeapon != nullptr)
		{
			holdingWeapon->OnDisable();		//이전 무기 비활성화
		}
		
		if(weaponToSwap != nullptr)
		{
			holdingWeapon = weaponToSwap;	// 무기를 교체한다
			holdingWeapon->OnEnable();		//현재 무기 활성화
			
			UE_LOG(LogTemp, Warning, TEXT("Swapped Weapon"));
		}
		else
		{
			holdingWeapon = nullptr;	// 교체할 무기가 없으면 맨손으로
			
			UE_LOG(LogTemp, Warning, TEXT("Equipped Weapon is now null"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Already Equipped This Weapon"));
	}
}

AWeapon* UEquipmentComponent::GetHoldingWeapon()
{
	return holdingWeapon;
}
