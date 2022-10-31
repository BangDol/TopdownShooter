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

UMaterialInterface* UItemObject::GetIcon() const
{
	if(!isRotated)
	{
		return icon;
	}
	else
	{
		return iconRotated;
	}
}

AItem* UItemObject::GetItem()
{
	return item;
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
	AItem* _item)
{
	dimensions = _dimensions;
	icon = _icon;
	iconRotated = _iconRotated;
	item = _item;
}
