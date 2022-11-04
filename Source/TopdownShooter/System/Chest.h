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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UMG, meta= (AllowPrivateAccess = "true"))
	class UInventoryComponent* inventoryComponent;
	
protected:	
	virtual void OnInteract_Implementation() override;
	
	void OpenChest();
};
