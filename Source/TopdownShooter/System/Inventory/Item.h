// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TopdownShooter/System/Interactable.h"
#include "Item.generated.h"

UCLASS()
class TOPDOWNSHOOTER_API AItem : public AInteractable
{
	GENERATED_BODY()

protected:
	class UItemObject* itemObject;
	
	UPROPERTY(EditAnywhere, Category="Item Settings")
	FIntPoint dimensions;
	UPROPERTY(EditAnywhere, Category="Item Settings")
	UMaterialInterface* icon;
	UPROPERTY(EditAnywhere, Category="Item Settings")
	UMaterialInterface* icon_rotated;
	UPROPERTY(EditAnywhere, Category="Item Settings")
	TSubclassOf<AItem> itemClass; //**this->GetClass()?

protected:
	void BeginPlay() override;
	void OnInteract_Implementation() override;

	UFUNCTION(BlueprintImplementableEvent)
	UItemObject* GetDefaultItemObject();
	UItemObject* GetDefaultItemObject_Implementation();
};
