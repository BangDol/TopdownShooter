// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUserWidget.h"

void UPlayerUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UPlayerUserWidget::OnCheckInteractable(bool isInteractable)
{
	if(isInteractable)
	{
		WBP_Interact->SetRenderOpacity(1.f);
	}
	else
	{
		WBP_Interact->SetRenderOpacity(0.f);
	}
}

//void UPlayerUserWidget::SetOwner(APlayerCharacter* player)
//{
//	owningPlayer = player;
//}