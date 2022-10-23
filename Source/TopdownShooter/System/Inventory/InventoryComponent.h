// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryComponentDelegate);

USTRUCT()
struct FTile
{
	GENERATED_BODY()

	int x;
	int y;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNSHOOTER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	TArray<class UItemObject*> items;	// 아이템들을 저장하는 컨테이너
	bool isDirty;	// 인벤토리 상태 변화를 알리기 위함
	
protected:
	UPROPERTY(EditAnywhere, Category = "Inventory Settings")
	int columns;
	
	UPROPERTY(EditAnywhere, Category = "Inventory Settings")
	int rows;

public:
	FInventoryComponentDelegate OnInventoryChangedDelegate;
	
public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UItemObject* GetItemAtIndex(int index);

public:
	FTile IndexToTile(int index) const;
	int TileToIndex(FTile tile) const;
	
	TMap<UItemObject*, FTile> GetAllItemObjects() const;
	void AddItemAt(UItemObject* itemObject, int topLeftIndex);
	bool TryAddItem(UItemObject* itemObject);
	void RemoveItem(UItemObject* itemObject);
	bool IsRoomAvaliable(UItemObject* itemObject, int topLeftIndex);

	int GetColumns() const;
	int GetRows() const;
};	

