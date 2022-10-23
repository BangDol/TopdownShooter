// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "ItemObject.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	columns = 0;
	rows = 0;
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	items.SetNum(columns * rows);	// = BP - RESIZE 노드
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(isDirty)
	{
		isDirty = false;
		OnInventoryChangedDelegate.Broadcast();
	}
}

FTile UInventoryComponent::IndexToTile(int index) const
{
	FTile tile;
	tile.x = index % columns;
	tile.y = index / columns;

	return tile;
}

int UInventoryComponent::TileToIndex(FTile tile) const
{
	return tile.x + (tile.y * columns);
}

TMap<UItemObject*, FTile> UInventoryComponent::GetAllItemObjects() const
{
	TMap<UItemObject*, FTile> allItems;
	
	for (int idx = 0; idx < items.Num(); idx++)
	{
		UItemObject*  currentItemObject = items[idx];
		if(currentItemObject != nullptr)
		{
			if(allItems.Contains(currentItemObject) == false)
			{
				allItems.Add(currentItemObject, IndexToTile(idx));
			}
		}
	}

	return allItems;
}

UItemObject* UInventoryComponent::GetItemAtIndex(int index)
{
	if(index >= 0 && index < items.Num())
	{
		return items[index];
	}

	return nullptr;
}

void UInventoryComponent::AddItemAt(UItemObject* itemObject, int topLeftIndex)
{
	if(itemObject != nullptr)
	{
		int startIdx_X = IndexToTile(topLeftIndex).x;
		int endIdx_X = startIdx_X + (itemObject->GetDimension().X - 1);

		int startIdx_Y = IndexToTile(topLeftIndex).y;
		int endIdx_Y = startIdx_Y + (itemObject->GetDimension().Y - 1);

		for (startIdx_X; startIdx_X <= endIdx_X; startIdx_X++)
		{
			for(startIdx_Y; startIdx_Y <= endIdx_Y; startIdx_Y++)
			{
				FTile tile;
				tile.x = startIdx_X;
				tile.y = startIdx_Y;

				int index = TileToIndex(tile);
				items[index] = itemObject;
			}
		}
	
		isDirty = true;
	}
	else
	{
		
	}
}

bool UInventoryComponent::TryAddItem(UItemObject* itemObject)
{
	if(itemObject != nullptr)
	{
		for(int count = 1; count <= 2; count ++)
		{
			for(int idx = 0 ; idx < items.Num(); idx++)
			{
				if(IsRoomAvaliable(itemObject, idx))
				{
					AddItemAt(itemObject, idx);

					return true;
				}
			}
			itemObject->Rotate();	
		}
	}
	
	return false;
}

void UInventoryComponent::RemoveItem(UItemObject* itemObject)
{
	if(itemObject != nullptr)
	{
		for (int idx = 0; idx < items.Num(); idx++)
		{
			if(items[idx] == itemObject)
			{
				items[idx] = nullptr;
				isDirty = true;
			}
		}
	}
}

bool UInventoryComponent::IsRoomAvaliable(UItemObject* itemObject, int topLeftIndex)
{
	if(itemObject != nullptr)
	{
		int startIdx_X = IndexToTile(topLeftIndex).x;
		int endIdx_X = startIdx_X + (itemObject->GetDimension().X - 1);

		int startIdx_Y = IndexToTile(topLeftIndex).y;
		int endIdx_Y = startIdx_Y + (itemObject->GetDimension().Y - 1);
	
		for (startIdx_X; startIdx_X <= endIdx_X; startIdx_X++)
		{
			for(startIdx_Y; startIdx_Y <= endIdx_Y; startIdx_Y++)
			{
				FTile tile;
				tile.x = startIdx_X;
				tile.y = startIdx_Y;
			
				int index = TileToIndex(tile);
			
				if(tile.x >= 0 &&
					tile.y >= 0 &&
					tile.x < columns &&
					tile.y < rows)
				{
					if(IsValid(GetItemAtIndex(index)) == false)
					{
						return true;	//모든 조건 통과 시 true
					}
					else
					{
						return false;	//해당 인덱스에 아이템이 존재할 때
					}
				}
				else
				{
					return false;	//아이템을 놓을 자리의 타일 중 하나라도 유효하지 않을때
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryComponent::IsRoomAvaliable : Item Object is null"));
	}
	
	return false;
}

int UInventoryComponent::GetColumns() const
{
	return columns;
}

int UInventoryComponent::GetRows() const
{
	return rows;
}
