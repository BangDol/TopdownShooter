#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

USTRUCT(BlueprintType)
struct FPCState
{
	GENERATED_BODY()

	bool isInteractable = false;
	
	UPROPERTY(BlueprintReadOnly)
	bool isArmed = false;
};

UCLASS(config=Game)
class APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UMG, meta= (AllowPrivateAccess = "true"))
	class UInventoryComponent* inventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UMG, meta= (AllowPrivateAccess = "true"))
	class UEquipmentComponent* equipmentComponent;

protected:
	class APlayerCharacterController* playerController;

	//플레이어의 상태 변수
	UPROPERTY(BlueprintReadOnly)
	FPCState pcState;

	//상호작용
	float interactTraceMaxDist;
	FHitResult interactTraceHitResult;

	//UI
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<class UInventoryUserWidget> inventoryUIClass;
	class UInventoryUserWidget* inventoryUI;

public:
	APlayerCharacter();
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

protected:
	//Input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void Interact();
	void ToggleInventory();
	void Attack();
	void SwapToWeapon1();
	void SwapToWeapon2();
	
	void SearchForInteractable();

public:
	UInventoryComponent* GetInventoryComponent();
	UInventoryUserWidget* GetInventoryUI();
	APlayerCharacterController* GetPlayerController();
	FPCState GetPCState();
	void UpdatePCState();
	void OpenInventory();
};