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
	isInteractable = false;
	interactTraceMaxDist = 200.f;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//플레이어 컨트롤러
	playerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SearchForInteractable();
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
		
		if(playerController->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, hitResult))
		{
			FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), hitResult.Location);
			FRotator lookRotation = FRotator(0, newRotation.Yaw, 0);
			GetCapsuleComponent()->SetWorldRotation(lookRotation);
		}
	}
}

void APlayerCharacter::Interact()
{
	if(isInteractable)
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
	//BP
}

void APlayerCharacter::Attack()
{
	if(equipmentComponent->GetEquippedWeapon() != nullptr)
	{
		equipmentComponent->GetEquippedWeapon()->Attack();
	}
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
		isInteractable = true;
	}
	else
	{
		isInteractable = false;
	}

	//UI Render Opacity
	ATopdownShooterGameMode* gameMode = Cast<ATopdownShooterGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	gameMode->UpdateInteractUI(isInteractable);
}

UInventoryComponent* APlayerCharacter::GetInventoryComponent()
{
	return inventoryComponent;
}
