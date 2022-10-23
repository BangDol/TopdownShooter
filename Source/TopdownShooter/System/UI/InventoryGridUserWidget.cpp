// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGridUserWidget.h"

#include <string>

#include "EditorDirectories.h"
#include "IDetailTreeNode.h"
#include "ItemUserWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/GridPanel.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetInputLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Slate/SlateBrushAsset.h"
#include "TopdownShooter/System/Inventory/InventoryComponent.h"
#include "TopdownShooter/System/Inventory/ItemObject.h"

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
	
	inventoryComponent->OnInventoryChangedDelegate.AddDynamic(this, &UInventoryGridUserWidget::Refresh);
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

	for(const TPair<UItemObject*, FTile>& pair : inventoryComponent->GetAllItemObjects())
	{
		if(itemUIClass != nullptr)
		{
			//SpawnActor와 달리 위젯은 뷰포트나 부모 위젯에 추가하기 전까지 Construct()가 실행되지 않으므로 그대로 CreateWidget() 사용 가능!
			UItemUserWidget* itemUI = CreateWidget<UItemUserWidget>(GetWorld(), itemUIClass);
			itemUI->Init(tileSize, pair.Key);
			itemUI->Refresh();
			//OnRemoved에 이벤트 바인딩 -> OnItemRemoved(ItemObject)
			itemUI->OnRemovedDelegate.AddDynamic(this, &UInventoryGridUserWidget::OnItemRemoved);

			FVector2D position;
			position.X = pair.Value.x * tileSize;
			position.Y = pair.Value.y * tileSize;
			
			inventory_GridPanel->AddChild(itemUI);
			UCanvasPanelSlot* canvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(itemUI);
			
			if(canvasPanelSlot != nullptr)
			{
				canvasPanelSlot->SetAutoSize(true);
				canvasPanelSlot->SetPosition(position);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("canvasPaneSlot is null"));
			}
		}
	}
}

void UInventoryGridUserWidget::OnItemRemoved(UItemObject* itemObject)
{
	inventoryComponent->RemoveItem(itemObject);
}

FMouseDirectionOnTile UInventoryGridUserWidget::MousePositionInTile(FVector2D mousePosition)
{
	FMouseDirectionOnTile mouseDirectionOnTile;

	if(FMath::Fmod(mousePosition.X, tileSize) > (tileSize / 2.f))
	{
		mouseDirectionOnTile.right = true;
	}
	if(FMath::Fmod(mousePosition.Y, tileSize) > (tileSize / 2.f))
	{
		mouseDirectionOnTile.down = true;
	}

	return mouseDirectionOnTile;
}

UItemObject* UInventoryGridUserWidget::GetPayload(UDragDropOperation* dragDropOperation) const
{
	if(dragDropOperation != nullptr)
	{
		UItemObject* _itemObject = Cast<UItemObject>(dragDropOperation->Payload);
		return _itemObject;
	}

	return nullptr;
}

bool UInventoryGridUserWidget::IsRoomAvaliableForPayload(UItemObject* payload) const
{
	if(payload != nullptr)
	{
		return inventoryComponent->IsRoomAvaliable(payload, GetDraggedItemTopLeftIndex());
	}

	return false;
}

int UInventoryGridUserWidget::GetDraggedItemTopLeftIndex() const
{
	FTile draggedItemsTile;
	draggedItemsTile.x = draggedItem_TopLeftTile.X;
	draggedItemsTile.y = draggedItem_TopLeftTile.Y;
	int topLeftIndex = inventoryComponent->TileToIndex(draggedItemsTile);
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow,
	//	TEXT("Dragging Item Top Left Index") + FString::FromInt(topLeftIndex));

	return topLeftIndex;
}

void UInventoryGridUserWidget::CalcDraggedItemTopLeftTile(UDragDropOperation* InOperation, FVector2D mousePosition, FMouseDirectionOnTile mouseDirectionOnTile)
{
	// MousePositionInTile()도 체크
	// draggedItemTopLeftTile이 이상하게 찍힘
	
	FVector2D dimension_Payload = Cast<UItemObject>(InOperation->Payload)->GetDimension();
	int value_right = 0;
	int value_down = 0;
	
	if(mouseDirectionOnTile.right)
	{
		value_right = 1;
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, TEXT("right = true"));
	}
	else
	{
		value_right = 0;
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, TEXT("right = false"));
	}
	if(mouseDirectionOnTile.down)
	{
		value_down = 1;
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, TEXT("down = true"));
	}
	else
	{
		value_down = 0;
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, TEXT("down = false"));
	}

	int value_X = dimension_Payload.X - value_right;
	int value_Y = dimension_Payload.Y - value_down;

	FIntPoint newIntPoint1;
	FVector2D position = mousePosition / tileSize;
	newIntPoint1.X = UKismetMathLibrary::FTrunc(position.X);
	newIntPoint1.Y = UKismetMathLibrary::FTrunc(position.Y);

	FIntPoint newIntPoint2;
	newIntPoint2.X = UKismetMathLibrary::Clamp(value_X, 0, value_X);
	newIntPoint2.Y = UKismetMathLibrary::Clamp(value_Y, 0, value_Y);
	newIntPoint2 /= 2.f;

	draggedItem_TopLeftTile = newIntPoint1 - newIntPoint2;
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
	FVector2D mousePosition = FVector2D::ZeroVector;
	
	mousePosition = USlateBlueprintLibrary::AbsoluteToLocal(
		InGeometry,
		UKismetInputLibrary::PointerEvent_GetScreenSpacePosition(InDragDropEvent));

	//아이템의 왼쪽 위 타일 위치를 계산
	CalcDraggedItemTopLeftTile(InOperation, mousePosition, MousePositionInTile(mousePosition));
	
	return false;
}

void UInventoryGridUserWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);

	drawDropLocation = true;
}

void UInventoryGridUserWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

	drawDropLocation = false;
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
			UItemUserWidget* itemUI = Cast<UItemUserWidget>(dragDropOperation->DefaultDragVisual);
			itemUI->Refresh();
		}
	}
	
	return UWidgetBlueprintLibrary::Handled().NativeReply;
}

int32 UInventoryGridUserWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	int32 maxLayer = LayerId;
	maxLayer++;
	
	//인벤토리 칸을 구분하는 선 그리기
	for(int idx = 0; idx < lines.Num(); idx++)
	{
		FVector2D localTopLeft = inventory_GridBorder->GetCachedGeometry().GetLocalPositionAtCoordinates(FVector2D(0, 0));
		FVector2D positionA = lines[idx].start + localTopLeft;
		FVector2D positionB = lines[idx].end + localTopLeft;
		//UWidgetBlueprintLibrary::DrawLine(InContext, positionA, positionB);
		
		//Draw Line
		TArray<FVector2D> points;
		points.Add(positionA);
		points.Add(positionB);

		FSlateDrawElement::MakeLines(
			OutDrawElements,
			maxLayer,
			AllottedGeometry.ToPaintGeometry(),
			points,
			ESlateDrawEffect::None,
			FLinearColor(0.5f, 0.5f, 0.5f, 0.5f),
			true,
			1.f);
	}
	
	//드래그 & 드랍 시 놓을 지점 표시해주는 박스 그리기
	if(UWidgetBlueprintLibrary::IsDragDropping() && drawDropLocation)
	{
		UDragDropOperation* dragDropOperation = UWidgetBlueprintLibrary::GetDragDroppingContent();
		UItemObject* payload = GetPayload(dragDropOperation);

		FLinearColor boxColor;
		if(IsRoomAvaliableForPayload(payload))
		{
			boxColor = FLinearColor(1.f, 1.f, 1.f, 0.5f);	//드랍이 가능할 때
		}
		else
		{
			boxColor = FLinearColor(1.f, 0.f, 0.f, 0.3f);	//드랍이 불가할 때
		}

		FVector2D position = draggedItem_TopLeftTile * tileSize;
		FVector2D size;
		size.X = payload->GetDimension().X * tileSize;
		size.Y = payload->GetDimension().Y * tileSize;
		//UWidgetBlueprintLibrary::DrawBox(InContext, position, size, brushAsset, boxColor);

		//Draw Box
		FSlateDrawElement::MakeBox(
			OutDrawElements,
			maxLayer,
			AllottedGeometry.ToPaintGeometry(position, size),
			&brushAsset->Brush,
			ESlateDrawEffect::None,
			boxColor);
	}

	return Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle,
						  bParentEnabled);
}