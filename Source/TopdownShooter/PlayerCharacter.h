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

protected:
	class APlayerCharacterController* playerController;

	//플레이어의 상태 변수
	UPROPERTY(BlueprintReadOnly)
	bool isInteractable;
	
	float interactTraceMaxDist;
	FHitResult interactTraceHitResult;

public:
	APlayerCharacter();
	
protected:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void AddControllerYawInput(float Val) override;
	void Interact();
	
	void SearchForInteractable();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateUI();
};