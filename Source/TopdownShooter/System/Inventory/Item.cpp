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
	//** 코드에서 콜리전 세팅해두는 게 좋을 듯
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("OnInteract"));
	
	APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if(player->GetInventoryComponent()->TryAddItem(itemObject))
	{
		Destroy();
	}
}

UItemObject* AItem::GetDefaultItemObject_Implementation()
{
	UItemObject* newItemObject = NewObject<UItemObject>(this);
	newItemObject->Init(dimensions, icon, icon_rotated, itemClass);
	
	return newItemObject;
}