// Fill out your copyright notice in the Description page of Project Settings.


#include "TopdownShooter/System/Chest.h"

void AChest::OnInteract_Implementation()
{
	OpenChest();
}

void AChest::OpenChest()
{
	UE_LOG(LogTemp, Warning, TEXT("Open Chest"));
}
