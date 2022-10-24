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

USTRUCT()
struct FMouseDirectionOnTile
{
	GENERATED_BODY()

	bool right = false;
	bool down = false;
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
	class UCanvasPanel* inventory_GridPanel;

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
	UFUNCTION()
	void Refresh();
	
	UFUNCTION()
	void OnItemRemoved(class UItemObject* itemObject);
	
	
	void CreateLineSegments();
	FMouseDirectionOnTile MousePositionInTile(FVector2D mousePosition);
	bool IsRoomAvaliableForPayload(class UItemObject* payload) const;
	int GetDraggedItemTopLeftIndex() const;
	void CalcDraggedItemTopLeftTile(UDragDropOperation* InOperation, FVector2D mousePosition, FMouseDirectionOnTile mouseDirectionOnTile);
	class UItemObject* GetPayload(UDragDropOperation* dragDropOperation) const;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
};
