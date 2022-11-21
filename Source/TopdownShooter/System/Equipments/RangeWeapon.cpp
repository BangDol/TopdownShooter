// Fill out your copyright notice in the Description page of Project Settings.


#include "TopdownShooter/System/Equipments/RangeWeapon.h"

#include "Kismet/KismetSystemLibrary.h"

ARangeWeapon::ARangeWeapon()
{
	gunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	gunMesh->SetupAttachment(mesh);
}

void ARangeWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ARangeWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ARangeWeapon::Attack()
{
	Fire();
	
}

void ARangeWeapon::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("ARangeWeapon::Fire"));
}

void ARangeWeapon::Reload()
{
}
