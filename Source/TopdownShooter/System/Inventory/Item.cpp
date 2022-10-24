// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "InventoryComponent.h"
#include "ItemObject.h"
#include "Kismet/GameplayStatics.h"
#include "TopdownShooter/Character/PlayerCharacter.h"

void AItem::BeginPlay()
{
	Super::BeginPlay();

	if(itemObject == nullptr)
	{
		itemObject = GetDefaultItemObject_Implementation();
	}
}

void AItem::OnInteract_Implementation()
{
	//Super::OnInteract_Implementation();
	//**override
	//** 코드에서 콜리전 세팅해두는 게 좋을 듯
	
	APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if(itemObject != nullptr)
	{
		if(player->GetInventoryComponent()->TryAddItem(itemObject))
		{
			Destroy();
		}		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AItem::OnInteract_Implementation : itemObject is null"));
	}
}

UItemObject* AItem::GetDefaultItemObject_Implementation()
{
	UItemObject* newItemObject = NewObject<UItemObject>(this);
	newItemObject->Init(dimensions, icon, icon_rotated, itemClass);
	
	return newItemObject;
}