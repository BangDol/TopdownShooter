// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemObject.generated.h"

USTRUCT()
struct FItemSettings
{
	GENERATED_BODY()

	//**아이템 이미지, 타일 등 속성
};

UCLASS()
class TOPDOWNSHOOTER_API UItemObject : public UObject
{
	GENERATED_BODY()

protected:
	FIntPoint dimensions;
	bool isRotated;
	
	class UMaterialInterface* icon;
	class UMaterialInterface* iconRotated;
	class AItem* item;

public:
	FIntPoint GetDimension();
	UMaterialInterface* GetIcon() const;
	AItem* GetItem();

	UFUNCTION(BlueprintCallable)
	void Rotate();
	bool IsRotated();

	void Init(FIntPoint _dimensions, UMaterialInterface* _icon, UMaterialInterface* _iconRotated, AItem* _item);
};
