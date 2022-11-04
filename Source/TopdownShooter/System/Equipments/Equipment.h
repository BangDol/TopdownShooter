// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentComponent.h"
#include "TopdownShooter/System/Inventory/Item.h"
#include "Equipment.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API AEquipment : public AItem
{
	GENERATED_BODY()

protected:
	EEquipmentType equipmentType;
	//헬멧, 아머 등 소스코드 생성 후 거기서 설정할 것 -> 블루프린트에서 일일이 지정할 필요 없음
public:
	UFUNCTION(BlueprintCallable)
	EEquipmentType GetEquipmentType();
};
