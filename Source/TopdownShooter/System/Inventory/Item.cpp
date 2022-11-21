// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "InventoryComponent.h"
#include "ItemObject.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TopdownShooter/Character/PlayerCharacter.h"

AItem::AItem()
{
	mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

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
	newItemObject->Init(dimensions, icon, icon_rotated, this);
	
	return newItemObject;
}