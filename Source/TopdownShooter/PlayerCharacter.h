#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

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

protected:
	class APlayerCharacterController* playerController;

	//플레이어의 상태 변수
	UPROPERTY(BlueprintReadOnly)
	bool isInteractable;

	//상호작용
	float interactTraceMaxDist;
	FHitResult interactTraceHitResult;

	//UI
	UPROPERTY(EditAnywhere, Category = UMG)
	TSubclassOf<UUserWidget> inventoryUIClass;
	class UInventoryUserWidget* inventoryUI;

public:
	APlayerCharacter();
	
protected:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void Interact();
	void ToggleInventory();
	
	void SearchForInteractable();
};