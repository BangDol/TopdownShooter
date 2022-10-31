// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentsUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API UEquipmentsUserWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	class UInventoryComponent* inventoryComponent;
	class UEquipmentComponent* equipmentComponent;
	
protected:
	//!@#개선 여지 있음
	UPROPERTY(meta=(BindWidget))
	class UEquipmentSlotUserWidget* equipmentSlot_Weapon1;
	UPROPERTY(meta=(BindWidget))
	class UEquipmentSlotUserWidget* equipmentSlot_Weapon2;
	UPROPERTY(meta=(BindWidget))
	class UEquipmentSlotUserWidget* equipmentSlot_Backpack;
	UPROPERTY(meta=(BindWidget))
	class UEquipmentSlotUserWidget* equipmentSlot_Helmet;
	UPROPERTY(meta=(BindWidget))
	class UEquipmentSlotUserWidget* equipmentSlot_Armor;
	
public:
	void Init(class UInventoryComponent* _inventoryComponent, class UEquipmentComponent* _equipmentComponent);
};
