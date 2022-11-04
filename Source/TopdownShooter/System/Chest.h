// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TopdownShooter/System/Interactable.h"
#include "Chest.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API AChest : public AInteractable
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UMG)
	class UInventoryComponent* inventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<class UInventoryGridUserWidget> inventoryGridUserWidgetClass; 
	class UInventoryGridUserWidget* inventoryGridUserWidget;

	class APlayerCharacter* player;

public:
	AChest();
	
protected:
	virtual void BeginPlay() override;
	virtual void OnInteract_Implementation() override;
	
	void OpenChest();
};
