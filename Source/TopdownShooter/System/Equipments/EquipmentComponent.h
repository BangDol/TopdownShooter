// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	Weapon1 = 0		UMETA(DisplayName = "Weapon1"),
	Weapon2			UMETA(DisplayName = "Weapon2"),
	Backpack		UMETA(DisplayName = "Backpack"),
	Helmet			UMETA(DisplayName = "Helmet"),
	Armor			UMETA(DisplayName = "Armor"),
	Count
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNSHOOTER_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	class APlayerCharacter* player;

	//장비
	TArray<class AEquipment*> equipments;
	class AWeapon* equippedWeapon;

public:	
	UEquipmentComponent();
	virtual void BeginPlay() override;

	void Init();
	UFUNCTION(BlueprintCallable)
	void AddEquipment(class AEquipment* _equipment, EEquipmentType _index);
	
	void RemoveEquipment(EEquipmentType _index);
	void SwapWeapon(EEquipmentType _weaponType);

	UFUNCTION(BlueprintCallable)
	AWeapon* GetEquippedWeapon();
};
