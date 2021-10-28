

// Copyright Epic Games, Inc. All Rights Reserved.

#include "HalloweenGameJamCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Interactable.h"
#include "Sacrifice/SacrificeAlter.h"


AHalloweenGameJamCharacter::AHalloweenGameJamCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	interactCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractCapsule"));
	interactCapsule->InitCapsuleSize(42.f, 96.0f);
	interactCapsule->SetCollisionProfileName(TEXT("Trigger"));
	interactCapsule->SetupAttachment(RootComponent);

	interactCapsule->OnComponentBeginOverlap.AddDynamic(this, &AHalloweenGameJamCharacter::OnOverlapBegin);
	interactCapsule->OnComponentEndOverlap.AddDynamic(this, &AHalloweenGameJamCharacter::OnOverlapEnd);

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

	//attackAbility = CreateDefaultSubobject<UAttackAbility>(TEXT("AttackAbility"));
	//attackAbility->SetPlayerCharacter(this);

	defenceStat = 100.0f;
	healthStat = 150.0f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}




//////////////////////////////////////////////////////////////////////////
// Input

void AHalloweenGameJamCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AHalloweenGameJamCharacter::Interact);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHalloweenGameJamCharacter::MoveRight);
	
}

void AHalloweenGameJamCharacter::MoveRight(float Value)
{
	//moveAbility->Invoke();
	// add movement in that direction
	AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
}
void AHalloweenGameJamCharacter::PlayerJump() {

	//jumpAbility->Invoke();
	//ACharacter::Jump();
}

void AHalloweenGameJamCharacter::Interact()
{
	if (interactableInRange && !isInteracting) {
		isInteracting = true;
	}

	else {
		isInteracting = false;
	}
}

void AHalloweenGameJamCharacter::OnOverlapBegin(UPrimitiveComponent* OverLappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (otherActor && (otherActor != this) && otherComp) {

		if (AInteractable* Iobj = Cast<AInteractable>(otherActor)) {
			interactableInRange = true;

			if (ASacrificeAlter* alter = Cast<ASacrificeAlter>(Iobj)) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Began with : " + Iobj->GetName()));
			}
		}
	}									
}

void AHalloweenGameJamCharacter::OnOverlapEnd(UPrimitiveComponent* overLappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex)
{
	if (AInteractable* Iobj = Cast<AInteractable>(otherActor)) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Ended with : " + Iobj->GetName()));
		interactableInRange = false;
		isInteracting = false;
	}
}

void AHalloweenGameJamCharacter::SetDefenceStat(float value)
{
	defenceStat = value;
}

float AHalloweenGameJamCharacter::GetDefenceStat()
{
	return defenceStat;
}

void AHalloweenGameJamCharacter::SetHealthStat(float value)
{
	healthStat = value;
}

float AHalloweenGameJamCharacter::GetHealthStat()
{
	return healthStat;
}

void AHalloweenGameJamCharacter::AddAbility(UAbilitiesBase* ability)
{
	playerAbilities.Add(ability);
}

TArray<UAbilitiesBase*> AHalloweenGameJamCharacter::GetAbilities()
{
	return playerAbilities;
}

bool AHalloweenGameJamCharacter::GetIsInteracting()
{
	return isInteracting;
}





