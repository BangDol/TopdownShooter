// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	health = 100.f;
}

float ACharacterBase::GetHealth()
{
	return health;
}

void ACharacterBase::SubHealth(float damage)
{
	health -= damage;
}