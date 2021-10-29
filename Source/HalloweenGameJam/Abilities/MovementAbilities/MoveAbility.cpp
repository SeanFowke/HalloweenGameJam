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
	UMovementAbilitiesBase::BeginPlay();
	SetOrigValue(GetPlayerCharacter()->GetCharacterMovement()->MaxWalkSpeed);

}


// Called every frame
void UMoveAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UMovementAbilitiesBase::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMoveAbility::Invoke()
{
	if (GetIsActivated()) {
		GetPlayerCharacter()->GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
	}

	else {
		GetPlayerCharacter()->GetCharacterMovement()->MaxWalkSpeed = GetOrigValue();
	}
}




