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

private:
	class UInventoryComponent* inventoryComponent;
	float tileSize;

public:
	UInventoryUserWidget(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual void NativeOnInitialized() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

public:
	UFUNCTION(BlueprintCallable)
	void Init(class UInventoryComponent* _inventoryComponent, float _tileSize);
};