// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemUserWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Kismet/KismetMathLibrary.h"
#include "TopdownShooter/System/Inventory/ItemObject.h"

UItemUserWidget::UItemUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsFocusable = true;
}

FSlateBrush UItemUserWidget::GetIconImage()
{
	FSlateBrush newSlateBrush =
		UWidgetBlueprintLibrary::MakeBrushFromMaterial(
		itemObject->GetIcon(),
		UKismetMathLibrary::FTrunc(size.X),
		UKismetMathLibrary::FTrunc(size.Y));
	
	return newSlateBrush;
}

void UItemUserWidget::Init(float _tileSize, UItemObject* _itemObject)
{
	tileSize = _tileSize;
	itemObject = _itemObject;
	itemImage->Brush = GetIconImage();
	
	backGroundBorderColor_OnNormal = backgroundBorder->BrushColor;
}

void UItemUserWidget::Refresh()
{
	size.X = itemObject->GetDimension().X * tileSize;
	size.Y = itemObject->GetDimension().Y * tileSize;
	backgroundSizeBox->SetWidthOverride(size.X);
	backgroundSizeBox->SetHeightOverride(size.Y);
	itemImage->Brush = GetIconImage();
	
	UWidgetLayoutLibrary::SlotAsCanvasSlot(itemImage)->SetSize(size);
}

#pragma region Native

//마우스 올려두면 Border 색상 변화
void UItemUserWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	bIsFocusable = true;
	backgroundBorder->SetBrushColor(backGroundBorderColor_OnMouseEnter);
}

//마우스 빠져나오면 Border 색상 복구
void UItemUserWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	backgroundBorder->SetBrushColor(backGroundBorderColor_OnNormal);
}

void UItemUserWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                           UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	
	UDragDropOperation* dragDropOperation = NewObject<UDragDropOperation>();
	dragDropOperation->Payload = itemObject;
	dragDropOperation->DefaultDragVisual = this;

	OnRemovedDelegate.Broadcast(itemObject);
	RemoveFromParent();
	OutOperation = dragDropOperation;
}

FReply UItemUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	FEventReply eventReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	
	return eventReply.NativeReply;
}

#pragma endregion
