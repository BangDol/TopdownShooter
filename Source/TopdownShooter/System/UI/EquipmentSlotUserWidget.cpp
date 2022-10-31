// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentSlotUserWidget.h"

#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Kismet/KismetMathLibrary.h"
#include "TopdownShooter/System/Inventory/ItemObject.h"

void UEquipmentSlotUserWidget::Init()
{
	
}

void UEquipmentSlotUserWidget::SetSlotEmpty()
{
	itemObject = nullptr;

	//이미지 비어있음
	FSlateBrush slotImage_Empty = UWidgetBlueprintLibrary::MakeBrushFromMaterial(nullptr);
	slotImage->SetBrush(slotImage_Empty);
}

void UEquipmentSlotUserWidget::SetSlotColorToNormal()
{
	
	slotBorder->SetBrushColor(slotBorderColor_OnNormal);
}

void UEquipmentSlotUserWidget::SetSlotColorToOnMouseEnter()
{
	slotBorder->SetBrushColor(slotBorderColor_OnMouseEnter);
}

#pragma region Native

void UEquipmentSlotUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Init();
}

void UEquipmentSlotUserWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                                 UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);

	SetSlotColorToOnMouseEnter();
}

void UEquipmentSlotUserWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

	SetSlotColorToNormal();
}

bool UEquipmentSlotUserWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	//슬롯이 비어있으면
	if(itemObject == nullptr)
	{
		UItemObject* _itemObject = Cast<UItemObject>(InOperation->Payload);

		//장비 슬롯에 ItemObject 등록 및 이미지 변경 등 작업
		if(_itemObject != nullptr)
		{
			//아이템 등록
			itemObject = _itemObject;
			
			//이미지
			FSlateBrush itemImage = UWidgetBlueprintLibrary::MakeBrushFromMaterial(_itemObject->GetIcon());
			slotImage->SetBrush(itemImage);

			//기존 아이템 UI 정보 저장
			dragVisual = InOperation->DefaultDragVisual;
		}
		
	}
	//슬롯이 비어있지 않다면
	else
	{
		//아이템 원위치로
		return false;
	}

	//항상 색상은 원래대로
	SetSlotColorToNormal();
	
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UEquipmentSlotUserWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if(itemObject != nullptr)
	{
		//드래그 드랍 오퍼레이션 생성
		UDragDropOperation* dragDropOperation = NewObject<UDragDropOperation>();
		dragDropOperation->Payload = itemObject;
		dragDropOperation->DefaultDragVisual = dragVisual;
		OutOperation = dragDropOperation;

		//비어있음 처리
		SetSlotEmpty();
	}
	
}

FReply UEquipmentSlotUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	FEventReply eventReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	
	return eventReply.NativeReply;
}

void UEquipmentSlotUserWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if(itemObject != nullptr)
	{
		SetSlotColorToOnMouseEnter();
	}
}

void UEquipmentSlotUserWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	SetSlotColorToNormal();
}

#pragma endregion 
