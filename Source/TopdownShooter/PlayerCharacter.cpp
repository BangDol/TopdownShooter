#include "PlayerCharacter.h"

#include "Interactable.h"
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

	// 변수 초기화
	interactableTraceMaxDist = 200.f;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

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
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::AddControllerYawInput);
}		


void APlayerCharacter::MoveForward(float Value)
{
	if ((playerController != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = playerController->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ( (playerController != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = playerController->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::AddControllerYawInput(float Val)
{
	Super::AddControllerYawInput(Val);

	FHitResult hitResult;
	
	if(playerController->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, hitResult))
	{
		FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), hitResult.Location);
		FRotator lookRotation = FRotator(0, newRotation.Yaw, 0);
		GetCapsuleComponent()->SetWorldRotation(lookRotation);
	}
}

#pragma endregion

void APlayerCharacter::SearchForInteractable()
{
	FHitResult hitResult;
	TArray<AActor*> actorsToIgnore;
	ETraceTypeQuery interactableTraceType = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel1);
	FVector traceStart = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 50.f);
	FVector traceEnd = traceStart + (GetActorForwardVector() * interactableTraceMaxDist);

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
		hitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green);

	//Interactable 오브젝트 체크
	if(hitResult.bBlockingHit)
	{
		AddDebugMessage(2.f, "Interactable Object!");
	}
}