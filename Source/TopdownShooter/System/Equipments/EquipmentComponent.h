// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	Weapon = 0		UMETA(DisplayName = "Weapon"),
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
	//class APlayerCharacter* player;

	//장비
	class AWeapon* weapon;
	TArray<class AEquipment*> equipments;
	//가방
	//헬멧
	//가슴방어구

public:	
	UEquipmentComponent();
	virtual void BeginPlay() override;

	void Init();
	UFUNCTION(BlueprintCallable)
	void AddEquipment(class AEquipment* _equipment, EEquipmentType _index);
	void RemoveEquipment(EEquipmentType _index);

	UFUNCTION(BlueprintCallable)
	AWeapon* GetEquippedWeapon();
};
