// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemUserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemUserWidgetDelegate, class UItemObject*, itemObject);

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

public:
	FItemUserWidgetDelegate OnRemovedDelegate;
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	FSlateBrush GetIconImage();
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
public:
	void Init(float _tileSize, class UItemObject* _itemObject);
	void Refresh();
};
