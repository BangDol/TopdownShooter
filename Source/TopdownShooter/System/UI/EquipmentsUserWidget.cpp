// Fill out your copyright notice in the Description page of Project Settings.


#include "TopdownShooter/System/UI/EquipmentsUserWidget.h"

#include "EquipmentSlotUserWidget.h"

void UEquipmentsUserWidget::Init(UInventoryComponent* _inventoryComponent, UEquipmentComponent* _equipmentComponent)
{
	inventoryComponent = _inventoryComponent;
	equipmentComponent = _equipmentComponent;

	equipmentSlot_Weapon1->Init(inventoryComponent, equipmentComponent);
	equipmentSlot_Weapon2->Init(inventoryComponent, equipmentComponent);
	equipmentSlot_Backpack->Init(inventoryComponent, equipmentComponent);
	equipmentSlot_Helmet->Init(inventoryComponent, equipmentComponent);
	equipmentSlot_Armor->Init(inventoryComponent, equipmentComponent);
}
