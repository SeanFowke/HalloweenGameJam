// Fill out your copyright notice in the Description page of Project Settings.


// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveAbility.h"
#include "../../HalloweenGameJamCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UMoveAbility::UMoveAbility() :UMovementAbilitiesBase()
{

}


// Called when the game starts
void UMoveAbility::BeginPlay()
{
	Super::BeginPlay();
	oriDeAccel = GetPlayerCharacter()->GetCharacterMovement()->BrakingDecelerationWalking;
	oriGroundFric = GetPlayerCharacter()->GetCharacterMovement()->GroundFriction;
	SetOrigValue(GetPlayerCharacter()->GetCharacterMovement()->MaxWalkSpeed);
	SetName("Move Ability");

}


// Called every frame
void UMoveAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMoveAbility::Invoke()
{
	if (GetIsActivated()) {
		GetPlayerCharacter()->GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
		GetPlayerCharacter()->GetCharacterMovement()->BrakingDecelerationWalking = 500.0f;
		GetPlayerCharacter()->GetCharacterMovement()->GroundFriction = 0.0f;
	}

	else {
		GetPlayerCharacter()->GetCharacterMovement()->MaxWalkSpeed = GetOrigValue();
		GetPlayerCharacter()->GetCharacterMovement()->BrakingDecelerationWalking = oriDeAccel;
		GetPlayerCharacter()->GetCharacterMovement()->GroundFriction = oriGroundFric;
	}
}




