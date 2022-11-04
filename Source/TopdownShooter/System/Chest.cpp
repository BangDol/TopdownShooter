// Fill out your copyright notice in the Description page of Project Settings.


#include "TopdownShooter/System/Chest.h"

#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Inventory/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TopdownShooter/Character/PlayerCharacter.h"
#include "UI/ChestInventoryUserWidget.h"
#include "UI/InventoryGridUserWidget.h"
#include "UI/InventoryUserWidget.h"

AChest::AChest()
{
	inventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void AChest::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	inventoryGridUserWidget = Cast<UInventoryGridUserWidget>(CreateWidget(GetWorld(), inventoryGridUserWidgetClass));

	if(inventoryGridUserWidget != nullptr)
	{
		inventoryGridUserWidget->Init(inventoryComponent, 50.f);
	}
}

void AChest::OnInteract_Implementation()
{
	OpenChest();
}

void AChest::OpenChest()
{
	UE_LOG(LogTemp, Warning, TEXT("Open Chest"));

	if(inventoryGridUserWidget != nullptr)
	{
		player->GetInventoryUI()->GetChestInventoryUserWidget()->GetBorder()->AddChild(inventoryGridUserWidget);
	}
	
	player->OpenInventory();
}
