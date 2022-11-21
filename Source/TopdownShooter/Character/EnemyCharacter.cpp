// Fill out your copyright notice in the Description page of Project Settings.


#include "TopdownShooter/Character/EnemyCharacter.h"

AEnemyCharacter::AEnemyCharacter()
{
	
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	UE_LOG(LogTemp, Warning, TEXT("AEnemyCharacter : Hit"));
	SubHealth(damage);

	if(GetHealth() <= 0)
	{
		Destroy();
	}
	
	return damage;
}