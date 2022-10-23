// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryUserWidget.h"
#include "InventoryGridUserWidget.h"

UInventoryUserWidget::UInventoryUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bStopAction = true;
}

void UInventoryUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

bool UInventoryUserWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UInventoryUserWidget::Init(UInventoryComponent* _inventoryComponent, float _tileSize)
{
	inventoryComponent = _inventoryComponent;
	tileSize = _tileSize;

	inventoryGridUserWidget->Init(inventoryComponent, tileSize);
}