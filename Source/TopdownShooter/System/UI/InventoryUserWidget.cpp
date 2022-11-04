// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryUserWidget.h"

#include "EquipmentsUserWidget.h"
#include "InventoryGridUserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "TopdownShooter/System/Equipments/EquipmentComponent.h"

UInventoryUserWidget::UInventoryUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bStopAction = true;
}

void UInventoryUserWidget::Init(UInventoryComponent* _inventoryComponent, UEquipmentComponent* _equipmentComponent, float _tileSize)
{
	inventoryComponent = _inventoryComponent;
	equipmentComponent = _equipmentComponent;
	tileSize = _tileSize;

	inventoryGridUserWidget->Init(inventoryComponent, tileSize);
	equipmentsUserWidget->Init(inventoryComponent, equipmentComponent);
	//chestInventoryGridUserWidget->RenderOpacity = 0.f;
}

UChestInventoryUserWidget* UInventoryUserWidget::GetChestInventoryUserWidget()
{
	return chestInventoryUserWidget;
}

#pragma region Native

bool UInventoryUserWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	//!@#인벤 밖에만 드랍하면 아이템 드랍인지 등 기획에 따라 아이템 드랍 방식 변경할 것
	

	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

#pragma endregion
