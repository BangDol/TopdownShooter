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
	equipments[(int)_index] = _equipment;
	
	if(equippedWeapon == nullptr)						//현재 손에 들려있는 무기가 없으면 무기 장착
	{
		equippedWeapon = Cast<AWeapon>(_equipment);
	}
}

void UEquipmentComponent::RemoveEquipment(EEquipmentType _index)
{
	if(equippedWeapon == Cast<AWeapon>(equipments[(int)_index]))		//지우고자 하는 장비가 현재 장착 중인 무기인 경우
	{
		if(_index == EEquipmentType::Weapon1)			//1번 무기 지우면 2번 무기로
		{
			SwapWeapon(EEquipmentType::Weapon2);
		}
		else if(_index == EEquipmentType::Weapon2)		//2번 무기 지우면 1번 무기로
		{
			SwapWeapon(EEquipmentType::Weapon1);
		}
	}
	
	equipments[(int)_index] = nullptr;
}

void UEquipmentComponent::SwapWeapon(EEquipmentType _weaponType)
{
	UE_LOG(LogTemp, Warning, TEXT("Tring To Swap Weapon"));

	AWeapon* weaponToSwap = Cast<AWeapon>(equipments[(int)_weaponType]);
	
	if(equippedWeapon != weaponToSwap)	// 해당 무기를 이미 장착 중인 경우에는 처리하지 않음
	{
		if(weaponToSwap != nullptr)
		{
			equippedWeapon = weaponToSwap;	// 무기를 교체한다
			UE_LOG(LogTemp, Warning, TEXT("Swapped Weapon"));
		}
		else
		{
			equippedWeapon = nullptr;	// 교체할 무기가 없으면 맨손으로
			UE_LOG(LogTemp, Warning, TEXT("Equipped Weapon is now null"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Already Equipped Weapon2"));
	}
}

AWeapon* UEquipmentComponent::GetEquippedWeapon()
{
	return equippedWeapon;
}
