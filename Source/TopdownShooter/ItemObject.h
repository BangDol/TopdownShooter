// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemObject.generated.h"

UCLASS()
class TOPDOWNSHOOTER_API UItemObject : public UObject
{
	GENERATED_BODY()

private:
	FIntPoint dimensions;
	bool isRotated;

public:
	class UMaterialInterface* icon;
	class UMaterialInterface* iconRotated;
	TSubclassOf<class AInteractable> itemClass;

public:
	FIntPoint GetDimension();
	UMaterialInterface* GetIcon();
	TSubclassOf<AInteractable> GetItemClass();
	
	void Rotate();
	bool IsRotated();
};
