// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HalloweenGameJamCharacter.h"
#include "TelevisionActor.h"

// Sets default values
AFirstPersonCharacter::AFirstPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());// Position the camera
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// create a hidden object component

	audioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	audioComp->SetupAttachment(GetCapsuleComponent());

	widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));

}

void AFirstPersonCharacter::SetSideScrollerRef(AHalloweenGameJamCharacter* character_)
{
	sideScrollerRef = character_;
}

void AFirstPersonCharacter::SetTVRef(ATelevisionActor* tv_)
{
	tvRef = tv_;
}

AHalloweenGameJamCharacter* AFirstPersonCharacter::GetSideScrollerRef()
{
	return sideScrollerRef;
}

// Called when the game starts or when spawned
void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AFirstPersonCharacter::OnOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AFirstPersonCharacter::OnOverlapEnd);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AFirstPersonCharacter::OnHit);


	controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	controller->bAutoManageActiveCameraTarget = false;
	
}

// Called every frame
void AFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFirstPersonCharacter::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void AFirstPersonCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*if (OtherActor && OtherActor != this && OverlappedComp)
	{
		ATelevisionActor* tv = Cast<ATelevisionActor>(OtherActor);

		if (tv)
		{
			canInteractWithTV = false;
		}
	}*/
}

void AFirstPersonCharacter::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	/*if (OtherActor && OtherActor != this && OtherComp)
	{
		ATelevisionActor* tv = Cast<ATelevisionActor>(OtherActor);

		if (tv)
		{
			tvRef = tv;
			canInteractWithTV = true;
		}
	}*/
}

void AFirstPersonCharacter::MoveForward(float Val)
{
	if (Val != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Val);
		//UE_LOG(LogTemp, Warning, TEXT("Moving Forward"));	
	}

	// if we wanna add in footstep sounds

	//if ((GetVelocity().X > 2.0f || GetVelocity().X < -2.0f || GetVelocity().Y > 2.0f || GetVelocity().Y < -2.0f) && GetVelocity().Z == 0)
	//{
	//	if (!moving)
	//	{
	//		moving = true;
	//		GetWorld()->GetTimerManager().SetTimer(footstepTimer, this, &AFirstPersonCharacter::PlayFootstepSound, footstepDelay, true);
	//		//UE_LOG(LogTemp, Warning, TEXT("Played Sound"));
	//	}
	//}
	//else
	//{
	//	moving = false;
	//	GetWorld()->GetTimerManager().ClearTimer(footstepTimer);
	//	//UE_LOG(LogTemp, Warning, TEXT("Cleared Timer"));
	//}


}

void AFirstPersonCharacter::MoveRight(float Val)
{
	if (Val != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Val);
		//UE_LOG(LogTemp, Warning, TEXT("Moving Right"));
	}
}

void AFirstPersonCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFirstPersonCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

// Called to bind functionality to input
void AFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind the sprint event
	/*PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AFirstPersonCharacter::OnSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AFirstPersonCharacter::OnWalk);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFirstPersonCharacter::OnInteract);*/

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AFirstPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFirstPersonCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFirstPersonCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFirstPersonCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFirstPersonCharacter::OnInteract);
	PlayerInputComponent->BindAction("Exit", IE_Pressed, this, &AFirstPersonCharacter::OnEscape);

}

void AFirstPersonCharacter::OnSprint()
{
}

void AFirstPersonCharacter::OnWalk()
{
}

void AFirstPersonCharacter::OnInteract()
{
	if (tvRef && sideScrollerRef && canInteractWithTV)
	{
		controller->Possess(sideScrollerRef);
		controller->ClientSetCameraFade(true, FColor::Black, FVector2D(1.5, 0.0f), 2.0f);
		controller->SetViewTargetWithBlend(tvRef, 0.45f);
	}
}

void AFirstPersonCharacter::OnEscape()
{
	if (canInteractWithTV)
	{
		controller->Possess(this);
		controller->ClientSetCameraFade(true, FColor::Black, FVector2D(1.5f, 0.0f), 2.0f);
		controller->SetViewTargetWithBlend(this, 0.45f);
	}
}

