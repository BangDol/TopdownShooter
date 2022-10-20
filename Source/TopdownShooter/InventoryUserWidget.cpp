// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryUserWidget.h"

void UInventoryUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
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
