#include "PlayerCharacter.h"

#include "PhysXInterfaceWrapperCore.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "TopdownShooter/Game/TopdownShooterGameMode.h"
#include "TopdownShooter/System/Interactable.h"
#include "TopdownShooter/System/Equipments/EquipmentComponent.h"
#include "TopdownShooter/System/Equipments/Weapon.h"
#include "TopdownShooter/System/Inventory/InventoryComponent.h"
#include "TopdownShooter/System/UI/InventoryUserWidget.h"

//**다른 헤더로..
#define AddDebugMessage(time, text) (GEngine->AddOnScreenDebugMessage(-1, time, FColor::Red, text))

APlayerCharacter::APlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	GetCharacterMovement()->bOrientRotationToMovement = true;	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;	
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	inventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	equipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComponent"));

	// 변수 초기화
	interactTraceMaxDist = 200.f;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//플레이어 컨트롤러
	playerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

	//UI
	inventoryUI = CreateWidget<UInventoryUserWidget>(playerController, inventoryUIClass);
	if(inventoryUI != nullptr)
	{
		inventoryUI->Init(inventoryComponent, equipmentComponent, 50.f);
	}
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SearchForInteractable();
	//UpdatePCState();
}

#pragma region 조작 관련

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
	PlayerInputComponent->BindAction("ToggleInventory", IE_Pressed, this, &APlayerCharacter::ToggleInventory);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::Attack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &APlayerCharacter::StopAttack);
	PlayerInputComponent->BindAction("SwapToWeapon1", IE_Pressed, this, &APlayerCharacter::SwapToWeapon1);
	PlayerInputComponent->BindAction("SwapToWeapon2", IE_Pressed, this, &APlayerCharacter::SwapToWeapon2);
}		


void APlayerCharacter::MoveForward(float Value)
{
	if ((playerController != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = playerController->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ( (playerController != nullptr) && (Value != 0.0f) )
	{
		const FRotator Rotation = playerController->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::Turn(float Value)
{
	if(playerController != nullptr)
	{
		FHitResult hitResult;
		ETraceTypeQuery mouseTraceType = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel2);
		
		if(playerController->GetHitResultUnderCursorByChannel(mouseTraceType, true, hitResult))
		{
			FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), hitResult.Location);
			FRotator lookRotation = FRotator(0, newRotation.Yaw, 0);
			GetCapsuleComponent()->SetWorldRotation(lookRotation);
		}
	}
}

void APlayerCharacter::Interact()
{
	if(pcState.isInteractable)
	{
		if(interactTraceHitResult.Actor.IsValid())
		{
			AInteractable* obj = Cast<AInteractable>(interactTraceHitResult.Actor.Get());
			obj->OnInteract();
		}
	}
}

void APlayerCharacter::ToggleInventory()
{
	if(inventoryUI->IsInViewport() == false)
	{
		inventoryUI->AddToViewport();
	}
}

void APlayerCharacter::Attack()
{
	if(equipmentComponent->GetHoldingWeapon() != nullptr)
	{
		equipmentComponent->GetHoldingWeapon()->Attack();
		//pcState.isShooting = true;
	}
}

void APlayerCharacter::StopAttack()
{
	if(equipmentComponent->GetHoldingWeapon() != nullptr)
	{
		//equipmentComponent->GetHoldingWeapon()->Attack();
		//pcState.isShooting = false;
		
	}
}

void APlayerCharacter::SwapToWeapon1()
{
	//equipmentComponent->SwapToWeapon1();
	equipmentComponent->SwapWeapon(EEquipmentType::Weapon1);
}

void APlayerCharacter::SwapToWeapon2()
{
	//equipmentComponent->SwapToWeapon2();
	equipmentComponent->SwapWeapon(EEquipmentType::Weapon2);
}

#pragma endregion

void APlayerCharacter::SearchForInteractable()
{
	TArray<AActor*> actorsToIgnore;
	ETraceTypeQuery interactableTraceType = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel1);
	FVector traceStart = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 50.f);
	FVector traceEnd = traceStart + (GetActorForwardVector() * interactTraceMaxDist);

	//Line Trace
	//전용 트레이스 채널로 Interactable만 충돌
	//Interactable 메시에 대해 콜리전 설정 확인할 것
	UKismetSystemLibrary::SphereTraceSingle(
		GetWorld(),
		traceStart,
		traceEnd,
		30.f,
		interactableTraceType,
		false,
		actorsToIgnore,
		EDrawDebugTrace::ForOneFrame,
		interactTraceHitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green);

	//Interactable 오브젝트 체크
	if(interactTraceHitResult.bBlockingHit)
	{
		pcState.isInteractable = true;
	}
	else
	{
		pcState.isInteractable = false;
	}

	//UI Render Opacity
	ATopdownShooterGameMode* gameMode = Cast<ATopdownShooterGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	gameMode->UpdateInteractUI(pcState.isInteractable);
}

UInventoryComponent* APlayerCharacter::GetInventoryComponent()
{
	return inventoryComponent;
}

UInventoryUserWidget* APlayerCharacter::GetInventoryUI()
{
	return inventoryUI;
}

APlayerCharacterController* APlayerCharacter::GetPlayerController()
{
	return playerController;
}

//FPCState APlayerCharacter::GetPCState()
//{
//	return pcState;
//}

EWeaponType APlayerCharacter::GetHoldingWeaponType()
{
	if(equipmentComponent->GetHoldingWeapon() != nullptr)
	{
		return equipmentComponent->GetHoldingWeapon()->GetWeaponType();
	}

	return EWeaponType::None;
}

//void APlayerCharacter::UpdatePCState()
//{
//	if(equipmentComponent->GetHoldingWeapon() != nullptr)
//	{
//		pcState.isArmed = true;
//	}
//	else
//	{
//		pcState.isArmed = false;
//	}
//}

void APlayerCharacter::OpenInventory()
{
	ToggleInventory();
}
