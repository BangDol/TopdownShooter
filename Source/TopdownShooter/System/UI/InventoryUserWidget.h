// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API UInventoryUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UInventoryGridUserWidget* inventoryGridUserWidget;

	UPROPERTY(meta = (BindWidget))
	class UEquipmentsUserWidget* equipmentsUserWidget;

private:
	class UInventoryComponent* inventoryComponent;
	class UEquipmentComponent* equipmentComponent;
	float tileSize;

public:
	UInventoryUserWidget(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION(BlueprintCallable)
	void Init(class UInventoryComponent* _inventoryComponent, UEquipmentComponent* _equipmentComponent, float _tileSize);
	
protected:
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};