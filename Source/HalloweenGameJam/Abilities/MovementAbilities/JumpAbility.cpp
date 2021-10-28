// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpAbility.h"
#include "../../HalloweenGameJamCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


UJumpAbility::UJumpAbility() :UMovementAbilitiesBase() {
}


void UJumpAbility::Invoke()
{
	if (GetIsActivated()) {
		GetPlayerCharacter()->GetCharacterMovement()->JumpZVelocity = 1100.0f;
	}

	else {
		GetPlayerCharacter()->GetCharacterMovement()->JumpZVelocity = GetOrigValue();
	}
}


void UJumpAbility::BeginPlay()
{
	UMovementAbilitiesBase::BeginPlay();
	SetOrigValue(GetPlayerCharacter()->GetCharacterMovement()->JumpZVelocity);
	SetName("Jump Ability");
}

void UJumpAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UMovementAbilitiesBase::TickComponent(DeltaTime, TickType, ThisTickFunction);

}