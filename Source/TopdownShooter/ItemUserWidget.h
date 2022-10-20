// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API UItemUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UBorder* backgroundBorder;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* backgroundSizeBox;

	UPROPERTY(meta = (BindWidget))
	class UImage* itemImage;

	float tileSize;
	class UItemObject* itemObject;
	FVector2D size;
	
protected:
	FSlateBrush GetIconImage();
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
public:
	void SetVariables(float _tileSize, class UItemObject* _itemObject);
	//**OnRemoved (이벤트 디스패처)
};
