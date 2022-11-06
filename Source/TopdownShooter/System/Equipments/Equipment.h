// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentComponent.h"
#include "TopdownShooter/System/Inventory/Item.h"
#include "Equipment.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API AEquipment : public AItem
{
	GENERATED_BODY()

protected:
	EEquipmentType equipmentType;

	APlayerCharacter* player;
	AEquipment* spawnedEquipment;

public:
	virtual void BeginPlay() override;

	void Init();
	EEquipmentType GetEquipmentType();

	virtual void OnEquip();
	virtual void OnUnequip();

protected:
	FName GetSocketName();
};
