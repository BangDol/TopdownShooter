// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryGridUserWidget.generated.h"

USTRUCT()
struct FLine
{
	GENERATED_BODY()

	FVector2D start;
	FVector2D end;
};

UCLASS()
class TOPDOWNSHOOTER_API UInventoryGridUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Settings")
	TSubclassOf<class UItemUserWidget> itemUIClass;
	UPROPERTY(EditAnywhere, Category = "UI Settings")
	class USlateBrushAsset* brushAsset;
	
	UPROPERTY(meta = (BindWidget))
	class UGridPanel* inventory_GridPanel;

	UPROPERTY(meta = (BindWidget))
	class UBorder* inventory_GridBorder;

	class UInventoryComponent* inventoryComponent;
	float tileSize;
	TArray<FLine> lines;

	FIntPoint draggedItem_TopLeftTile;
	bool drawDropLocation;

public:
	void Init(class UInventoryComponent* inventoryComponent, float tileSize);

protected:
	void CreateLineSegments();
	void Refresh();
	void OnItemRemoved(class UItemObject* itemObject);
	void MousePositionInTile(FVector2D mousePosition, bool& _right, bool& _down);
	class UItemObject* GetPayload(UDragDropOperation* dragDropOperation);
	bool IsRoomAvaliableForPayload(class UItemObject* payload);

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual void NativePaint(FPaintContext& InContext) const override;
	void OnPaint(FPaintContext& InContext);

	float GetDraggedItemTopLeftIndex();
};
