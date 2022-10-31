// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TopdownShooter/System/Equipments/EquipmentComponent.h"
#include "EquipmentSlotUserWidget.generated.h"

UCLASS()
class TOPDOWNSHOOTER_API UEquipmentSlotUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	class APlayerCharacter* player;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UEquipmentComponent* equipmentComponent;
	class UInventoryComponent* inventoryComponent;

	class UItemObject* itemObject;
	
protected:
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UBorder* slotBorder;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UImage* slotImage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	FLinearColor slotBorderColor_OnNormal;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	FLinearColor slotBorderColor_OnMouseEnter;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	FLinearColor slotBorderColor_OnNotAvaliable;

	UPROPERTY(EditAnywhere, Category="Settings")
	EEquipmentType equipmentType;
	
	UWidget* dragVisual;
	

public:
	void Init(class UInventoryComponent* _inventoryComponent, class UEquipmentComponent* _equipmentComponent);
	
protected:
	void SetSlotEmpty();
	void SetSlotColorToNormal();
	void SetSlotColorToOnMouseEnter();
	void SetSlotColorToOnNotAvaliable();
	bool CheckIsEquippable(UItemObject* _itemObject);
	
	virtual void NativeConstruct() override;
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
};
