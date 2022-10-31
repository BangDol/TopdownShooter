// Fill out your copyright notice in the Description page of Project Settings.


#include "TopdownShooter/System/Equipments/RangeWeapon.h"

void ARangeWeapon::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("ARangeWeapon::Attack"));

	Fire();
}

void ARangeWeapon::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("ARangeWeapon::Fire"));
}

void ARangeWeapon::Reload()
{
}
