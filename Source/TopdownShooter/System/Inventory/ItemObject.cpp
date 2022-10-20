// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemObject.h"

FIntPoint UItemObject::GetDimension()
{
	if(isRotated)
	{
		FIntPoint newDimensions;
		newDimensions.X = dimensions.Y;
		newDimensions.Y = dimensions.X;

		return newDimensions;
	}
	else
	{
		return dimensions;
	}
}

UMaterialInterface* UItemObject::GetIcon()
{
	if(isRotated)
	{
		return icon;
	}
	else
	{
		return iconRotated;
	}
}

TSubclassOf<AItem> UItemObject::GetItemClass()
{
	return itemClass;
}

void UItemObject::Rotate()
{
	isRotated = !isRotated;
}

bool UItemObject::IsRotated()
{
	return isRotated;
}

void UItemObject::Init(FIntPoint _dimensions, UMaterialInterface* _icon, UMaterialInterface* _iconRotated,
	TSubclassOf<AItem> _itemClass)
{
	dimensions = _dimensions;
}
