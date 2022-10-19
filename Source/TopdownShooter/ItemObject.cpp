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

TSubclassOf<AInteractable> UItemObject::GetItemClass()
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
