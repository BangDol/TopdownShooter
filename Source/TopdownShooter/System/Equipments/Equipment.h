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
	UPROPERTY()
	EEquipmentType equipmentType;

	UPROPERTY()
	APlayerCharacter* player;
	
	UPROPERTY()
	FName socketName;

public:
	AEquipment();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void Init();
	EEquipmentType GetEquipmentType();

	virtual void OnEquip();
	virtual void OnUnequip();

protected:
	virtual FName GetSocketName();
	void AttachEquipmentToPlayer();
	void SetInteractionCollsion(bool isInteractable);
};
