

// Copyright Epic Games, Inc. All Rights Reserved.

#include "HalloweenGameJamCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FirstPersonCharacter.h"
#include "Abilities/MovementAbilities/JumpAbility.h"
#include "Abilities/MovementAbilities/MoveAbility.h"
#include "Abilities/PassiveAbilities/DefenceAbility.h"
#include "Abilities/PassiveAbilities/HealthAbility.h"


AHalloweenGameJamCharacter::AHalloweenGameJamCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	jumpAbility = CreateDefaultSubobject<UJumpAbility>(TEXT("JumpAbility"));
	jumpAbility->SetPlayerCharacter(this);

	moveAbility = CreateDefaultSubobject<UMoveAbility>(TEXT("MoveAbility"));
	moveAbility->SetPlayerCharacter(this);

	defenceAbility = CreateDefaultSubobject<UDefenceAbility>(TEXT("DefenceAbility"));
	defenceAbility->SetPlayerCharacter(this);

	healthAbility = CreateDefaultSubobject<UHealthAbility>(TEXT("HealthAbility"));
	healthAbility->SetPlayerCharacter(this);

	defenceStat = 100.0f;
	healthStat = 150.0f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void AHalloweenGameJamCharacter::SetFirstPersonRef(AFirstPersonCharacter* character_)
{
	fpsRef = character_;
}

void AHalloweenGameJamCharacter::FocusOnActor(AActor* focus_, float rate_)
{
	FViewTargetTransitionParams transitionParams;
	transitionParams.BlendTime = rate_;

	if (cameraManager)
	{
		cameraManager->SetViewTarget(focus_, transitionParams);
	}
}

APlayerCameraManager* AHalloweenGameJamCharacter::GetCameraManager()
{
	return cameraManager;
}

AFirstPersonCharacter* AHalloweenGameJamCharacter::getFpsCharacter()
{
	if (fpsRef)
	{
		return fpsRef;
	}


	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AHalloweenGameJamCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHalloweenGameJamCharacter::PlayerJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHalloweenGameJamCharacter::MoveRight);


}

void AHalloweenGameJamCharacter::BeginPlay()
{
	Super::BeginPlay();

	cameraManager = Cast<APlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));

	AFirstPersonCharacter* fpsRefTemp = Cast<AFirstPersonCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (fpsRefTemp)
	{
		fpsRef = fpsRefTemp;
		fpsRef->SetSideScrollerRef(this);
	}
}

void AHalloweenGameJamCharacter::MoveRight(float Value)
{
	moveAbility->Invoke();
	// add movement in that direction
	AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
}
void AHalloweenGameJamCharacter::PlayerJump() {

	jumpAbility->Invoke();
	ACharacter::Jump();
}



