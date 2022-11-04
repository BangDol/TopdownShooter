// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentSlotUserWidget.h"

#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "TopdownShooter/Character/PlayerCharacter.h"
#include "TopdownShooter/System/Inventory/InventoryComponent.h"
#include "TopdownShooter/System/Equipments//Equipment.h"
#include "TopdownShooter/System/Equipments/EquipmentComponent.h"
#include "TopdownShooter/System/Equipments/Weapon.h"
#include "TopdownShooter/System/Inventory/ItemObject.h"

void UEquipmentSlotUserWidget::Init(UInventoryComponent* _inventoryComponent, UEquipmentComponent* _equipmentComponent)
{
	inventoryComponent = _inventoryComponent;
	equipmentComponent = _equipmentComponent;
}

void UEquipmentSlotUserWidget::SetSlotEmpty()
{
	//아이템 비어있음
	itemObject = nullptr;
	equipmentComponent->RemoveEquipment(equipmentSlotType);

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

void UEquipmentSlotUserWidget::SetSlotColorToOnNotAvaliable()
{
	slotBorder->SetBrushColor(slotBorderColor_OnNotAvaliable);
}

bool UEquipmentSlotUserWidget::CheckIsEquippable(UItemObject* _itemObject)
{
	if((_itemObject != nullptr) &&											//null 체크
		(itemObject == nullptr) &&											//슬롯이 비어있으면
		(_itemObject->GetItem()->IsA(AEquipment::StaticClass())))	//장착이 가능한 Equipment인지 체크
	{
		AEquipment* equipment = Cast<AEquipment>(_itemObject->GetItem());
				
		//해당 슬롯에 맞는 타입인지 체크
		if(equipment != nullptr)
		{
			//무기 타입에 대한 예외처리..
			//!@# 개선 여지 있음
			if((equipmentSlotType == EEquipmentType::Weapon1) ||
				(equipmentSlotType == EEquipmentType::Weapon2))
			{
				if((equipment->GetEquipmentType() == EEquipmentType::Weapon1) ||
					(equipment->GetEquipmentType() == EEquipmentType::Weapon2))
				{
					return true;
				}
			}
			else if(equipment->GetEquipmentType() == equipmentSlotType)
			{
				return true;
			}
		}
	}

	return false;
}

void UEquipmentSlotUserWidget::AddEquipmentToSlot(UItemObject* _itemObject)
{
	itemObject = _itemObject;
	
	AEquipment* equipment = Cast<AEquipment>(itemObject->GetItem());
	equipmentComponent->AddEquipment(equipment, equipmentSlotType);		
}

#pragma region Native

void UEquipmentSlotUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UEquipmentSlotUserWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                                 UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);

	UItemObject* _itemObject = Cast<UItemObject>(InOperation->Payload);

	if(CheckIsEquippable(_itemObject))
	{
		SetSlotColorToOnMouseEnter();	//장비 장착 가능
	}
	else
	{
		SetSlotColorToOnNotAvaliable();	//장비 장착 불가
	}
}

void UEquipmentSlotUserWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

	SetSlotColorToNormal();
}

bool UEquipmentSlotUserWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	UItemObject* _itemObject = Cast<UItemObject>(InOperation->Payload);

	if(CheckIsEquippable(_itemObject))
	{
		//장비 슬롯에 ItemObject 등록 및 이미지 변경 등 작업
	
		//Equipment 처리
		AddEquipmentToSlot(_itemObject);		//아이템 등록 및 장비 추가

		//UI 처리
		FSlateBrush itemImage = UWidgetBlueprintLibrary::MakeBrushFromMaterial(_itemObject->GetIcon());	//이미지
		slotImage->SetBrush(itemImage);
		//!@#이미지 사이즈 조절

		//기존 아이템 UI 정보 저장
		dragVisual = InOperation->DefaultDragVisual;
	}
	else
	{
		inventoryComponent->TryAddItem(_itemObject);
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