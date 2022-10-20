// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUserWidget.generated.h"

UCLASS()
class TOPDOWNSHOOTER_API UPlayerUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	//class APlayerCharacter* owningPlayer;
	
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;
	
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* StaminaBar;

	UPROPERTY(meta = (BindWidget))
	class UUserWidget* WBP_Interact;

protected:
	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	

public:
	//void SetOwner(class APlayerCharacter* player);	
	void OnCheckInteractable(bool isInteractable);
};
