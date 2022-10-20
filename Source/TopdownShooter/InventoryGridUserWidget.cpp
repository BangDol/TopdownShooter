// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGridUserWidget.h"

#include "EditorDirectories.h"
#include "InventoryComponent.h"
#include "ItemObject.h"
#include "ItemUserWidget.h"
#include "TopdownShooterGameMode.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/GridPanel.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetInputLibrary.h"
#include "Kismet/KismetMathLibrary.h"

void UInventoryGridUserWidget::Init(UInventoryComponent* _inventoryComponent, float _tileSize)
{
	inventoryComponent = _inventoryComponent;
	tileSize = _tileSize;

	FVector2D borderSize;
	borderSize.X = inventoryComponent->GetColumns() * tileSize;
	borderSize.Y = inventoryComponent->GetRows() * tileSize;
	UWidgetLayoutLibrary::SlotAsCanvasSlot(inventory_GridBorder)->SetSize(borderSize);

	CreateLineSegments();
	Refresh();
	//OnInventoryChanged에 이벤트 바인딩 -> Refresh()
}

void UInventoryGridUserWidget::CreateLineSegments()
{
	float x = 0;
	float y = 0;
	
	//Vertical Lines
	for(int idx = 0; idx <= inventoryComponent->GetColumns(); idx++)
	{
		x = idx * tileSize;
		
		FLine newLine;
		newLine.start.X = x;
		newLine.start.Y = 0;
		newLine.end.X = x;
		newLine.end.Y = inventoryComponent->GetRows() * tileSize;

		lines.Add(newLine);
	}

	//Horizontal Lines
	for(int idx = 0; idx <= inventoryComponent->GetRows(); idx++)
	{
		y = idx * tileSize;
		
		FLine newLine;
		newLine.start.X = 0;
		newLine.start.Y = y;
		newLine.end.X = inventoryComponent->GetColumns() * tileSize;
		newLine.end.Y = y;

		lines.Add(newLine);
	}
}

void UInventoryGridUserWidget::Refresh()
{
	inventory_GridPanel->ClearChildren();

	for(const TPair<UItemObject*, FTile>& pair : inventoryComponent->GetAllItems())
	{
		if(itemUIClass != nullptr)
		{
			//SpawnActor와 달리 위젯은 뷰포트나 부모 위젯에 추가하기 전까지 Contruct()가 실행되지 않으므로 그대로 CreateWidget() 사용 가능!
			UItemUserWidget* itemUI = CreateWidget<UItemUserWidget>(GetWorld(), itemUIClass);
			itemUI->SetVariables(tileSize, pair.Key);

			//OnRemoved에 이벤트 바인딩 -> OnItemRemoved(ItemObject)
			UCanvasPanelSlot* canvasPanelSlot = Cast<UCanvasPanelSlot>(inventory_GridPanel->AddChild(itemUI));
			
			FVector2D position;
			position.X = pair.Value.x * tileSize;
			position.Y = pair.Value.y * tileSize;
			
			canvasPanelSlot->SetAutoSize(true);
			canvasPanelSlot->SetPosition(position);
		}
	}
}

void UInventoryGridUserWidget::OnItemRemoved(UItemObject* itemObject)
{
	inventoryComponent->RemoveItem(itemObject);
}

void UInventoryGridUserWidget::MousePositionInTile(FVector2D mousePosition, bool& _right, bool& _down)
{
	bool right = _right;
	bool down = _down;
	
	//**???
	float remainder = 0.f;
	
	if(UKismetMathLibrary::FMod(mousePosition.X, tileSize, remainder) > (tileSize / 2.f))
	{
		right = true;
	}
	if(UKismetMathLibrary::FMod(mousePosition.Y, tileSize, remainder) > (tileSize / 2.f))
	{
		down = true;
	}
}

UItemObject* UInventoryGridUserWidget::GetPayload(UDragDropOperation* dragDropOperation)
{
	if(dragDropOperation != nullptr)
	{
		UItemObject* _itemObject = Cast<UItemObject>(dragDropOperation->Payload);
		return _itemObject;
	}

	return nullptr;
}

bool UInventoryGridUserWidget::IsRoomAvaliableForPayload(UItemObject* payload)
{
	if(payload != nullptr)
	{
		return inventoryComponent->IsRoomAvaliable(payload, GetDraggedItemTopLeftIndex());
	}

	return false;
}

bool UInventoryGridUserWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                            UDragDropOperation* InOperation)
{
	if(IsRoomAvaliableForPayload(GetPayload(InOperation)))
	{
		inventoryComponent->AddItemAt(GetPayload(InOperation), GetDraggedItemTopLeftIndex());
	}
	else
	{
		if(inventoryComponent->TryAddItem(GetPayload(InOperation)) == false)
		{
			//**수정할 것
			//ATopdownShooterGameMode* gameMode = Cast<ATopdownShooterGameMode>(UGameplayStatics::GetGameState(GetWorld()));
			//Spawn Item From Actor (GameBase)
		}
	}
	
	return true;
}

bool UInventoryGridUserWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	bool right = false;
	bool down = false;
	FVector2D mousePosition = FVector2D::ZeroVector;
	
	mousePosition = USlateBlueprintLibrary::AbsoluteToLocal(
		InGeometry,
		UKismetInputLibrary::PointerEvent_GetScreenSpacePosition(InDragDropEvent));

	MousePositionInTile(mousePosition, right, down);

	FVector2D dimension_Payload = Cast<UItemObject>(InOperation->Payload)->GetDimension();
	int value_right = 0;
	int value_down = 0;
	
	if(right)
	{
		value_right = 1;
	}
	else
	{
		value_right = 0;
	}
	if(down)
	{
		value_down = 1;
	}
	else
	{
		value_down = 0;	
	}

	int value_X = dimension_Payload.X - value_right;
	int value_Y = dimension_Payload.Y - value_down;

	FIntPoint newIntPoint1;
	newIntPoint1.X = UKismetMathLibrary::Clamp(value_X, 0, value_X);
	newIntPoint1.Y = UKismetMathLibrary::Clamp(value_Y, 0, value_Y);

	FIntPoint newIntPoint2;
	FVector2D position = mousePosition / tileSize;
	newIntPoint2.X = UKismetMathLibrary::FTrunc(position.X);
	newIntPoint2.Y = UKismetMathLibrary::FTrunc(position.Y);

	draggedItem_TopLeftTile = newIntPoint1 - newIntPoint2;
	
	return false;
}

FReply UInventoryGridUserWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if(InKeyEvent.GetKey() == EKeys::R)
	{
		UDragDropOperation* dragDropOperation = UWidgetBlueprintLibrary::GetDragDroppingContent();
		UItemObject* payload = GetPayload(dragDropOperation);
		
		if(IsValid(payload))
		{
			payload->Rotate();
			//**Cast<UItemUserWidget>(dragDropOperation->DefaultDragVisual)->Refresh();
		}
	}
	
	return UWidgetBlueprintLibrary::Handled().NativeReply;
}

void UInventoryGridUserWidget::NativePaint(FPaintContext& InContext) const
{
	Super::NativePaint(InContext);

	//OnPaint(InContext);	
}

void UInventoryGridUserWidget::OnPaint(FPaintContext& InContext)
{
	//인벤토리 칸을 구분하는 선 그리기
	for(int idx = 0; idx < lines.Num(); idx++)
	{
		FVector2D localTopLeft = inventory_GridBorder->GetCachedGeometry().GetLocalPositionAtCoordinates(FVector2D(0, 0));
		FVector2D positionA = lines[idx].start + localTopLeft;
		FVector2D positionB = lines[idx].end + localTopLeft;
		UWidgetBlueprintLibrary::DrawLine(InContext, positionA, positionB);
	}
	//드래그 & 드랍 시 놓을 지점 표시해주는 박스 그리기
	if(UWidgetBlueprintLibrary::IsDragDropping() && drawDropLocation)
	{
		UDragDropOperation* dragDropOperation = UWidgetBlueprintLibrary::GetDragDroppingContent();
		UItemObject* payload = GetPayload(dragDropOperation);

		FLinearColor boxColor;
		if(IsRoomAvaliableForPayload(payload))
		{
			boxColor = FLinearColor::Red;
		}
		else
		{
			boxColor = FLinearColor::White;
		}

		FVector2D position = draggedItem_TopLeftTile * tileSize;
		FVector2D size;
		size.X = payload->GetDimension().X * tileSize;
		size.Y = payload->GetDimension().Y * tileSize;

		UWidgetBlueprintLibrary::DrawBox(InContext, position, size, brushAsset, boxColor);
	}
}

float UInventoryGridUserWidget::GetDraggedItemTopLeftIndex()
{
	FTile draggedItemsTile;
	draggedItemsTile.x = draggedItem_TopLeftTile.X;
	draggedItemsTile.y = draggedItem_TopLeftTile.Y;
	float topLeftIndex = inventoryComponent->TileToIndex(draggedItemsTile);

	return topLeftIndex;
}
