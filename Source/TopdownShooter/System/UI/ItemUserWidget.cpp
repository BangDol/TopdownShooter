// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemUserWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "TopdownShooter/System/Inventory/ItemObject.h"

FSlateBrush UItemUserWidget::GetIconImage()
{
	FSlateBrush newSlateBrush =
		UWidgetBlueprintLibrary::MakeBrushFromMaterial(
		itemObject->GetIcon(),
		UKismetMathLibrary::FTrunc(size.X),
		UKismetMathLibrary::FTrunc(size.Y));

	return newSlateBrush;
}

void UItemUserWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	//**생성 방법?
	UDragDropOperation dragDropOperation;
	dragDropOperation.Payload = itemObject;
	dragDropOperation.DefaultDragVisual = this;

	//OnRemoved 호출
	RemoveFromParent();
	//**operation 리턴?
}

FReply UItemUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
}

void UItemUserWidget::SetVariables(float _tileSize, UItemObject* _itemObject)
{
	tileSize = _tileSize;
	itemObject = _itemObject;
}
