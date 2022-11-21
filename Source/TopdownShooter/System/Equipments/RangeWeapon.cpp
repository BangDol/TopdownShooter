// Fill out your copyright notice in the Description page of Project Settings.


#include "TopdownShooter/System/Equipments/RangeWeapon.h"

#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TopdownShooter/Character/EnemyCharacter.h"
#include "TopdownShooter/Character/PlayerCharacter.h"

ARangeWeapon::ARangeWeapon()
{
	//Components
	gunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	gunMesh->SetupAttachment(mesh);

	//Variables
	damage = 30.f;
	fireRange = 1000.f;
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
	FHitResult enemyTraceHitResult;
	TArray<AActor*> actorsToIgnore;
	
	muzzleTransform = gunMesh->GetSocketTransform(TEXT("MuzzleSocket"));
	
	ETraceTypeQuery traceType = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel3);
	FVector traceStart = muzzleTransform.GetLocation();
	FVector traceEnd = traceStart + (muzzleTransform.GetRotation().GetForwardVector() * fireRange);

	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		traceStart,
		traceEnd,
		traceType,
		false,
		actorsToIgnore,
		EDrawDebugTrace::ForDuration,
		enemyTraceHitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green);
	
	if(enemyTraceHitResult.GetActor() != nullptr)
	{
		AEnemyCharacter* enemy = Cast<AEnemyCharacter>(enemyTraceHitResult.GetActor());

		if(enemy != nullptr)
		{
			UGameplayStatics::ApplyDamage(
			enemyTraceHitResult.GetActor(),
			damage,
			player->GetController(),
			player,
			nullptr);
		}
	}
}

void ARangeWeapon::Reload()
{
}
