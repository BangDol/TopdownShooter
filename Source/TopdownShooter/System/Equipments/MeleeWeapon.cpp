// Fill out your copyright notice in the Description page of Project Settings.


#include "TopdownShooter/System/Equipments/MeleeWeapon.h"

void AMeleeWeapon::Attack()
{
	MeleeAttack();
}

void AMeleeWeapon::MeleeAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("AMeleeWeapon::MeleeAttack"));
}
