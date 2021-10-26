// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonCharacter.h"

// Sets default values
AFirstPersonCharacter::AFirstPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AFirstPersonCharacter::SetSideScrollerRef(AHalloweenGameJamCharacter* character_)
{
}

// Called when the game starts or when spawned
void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFirstPersonCharacter::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AFirstPersonCharacter::MoveForward(float Val)
{
}

void AFirstPersonCharacter::MoveRight(float Val)
{
}

void AFirstPersonCharacter::TurnAtRate(float Rate)
{
}

void AFirstPersonCharacter::LookUpAtRate(float Rate)
{
}

// Called to bind functionality to input
void AFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFirstPersonCharacter::OnFire()
{

}

void AFirstPersonCharacter::OnSprint()
{
}

void AFirstPersonCharacter::OnWalk()
{
}

void AFirstPersonCharacter::OnInteract()
{
}

void AFirstPersonCharacter::OnResetVR()
{
}
