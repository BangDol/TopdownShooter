// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChestInventoryUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API UChestInventoryUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UBorder* border;

public:
	UFUNCTION(BlueprintPure, BlueprintCallable)
	UBorder* GetBorder();
};
