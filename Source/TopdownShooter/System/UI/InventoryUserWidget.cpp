// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryUserWidget.h"
#include "InventoryGridUserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

UInventoryUserWidget::UInventoryUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bStopAction = true;
}

void UInventoryUserWidget::Init(UInventoryComponent* _inventoryComponent, float _tileSize)
{
	inventoryComponent = _inventoryComponent;
	tileSize = _tileSize;

	inventoryGridUserWidget->Init(inventoryComponent, tileSize);
}

#pragma region Native

bool UInventoryUserWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	//**인벤 밖에만 드랍하면 아이템 드랍인지 등 기획에 따라 아이템 드랍 방식 변경할 것

	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

#pragma endregion
