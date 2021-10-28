// Fill out your copyright notice in the Description page of Project Settings.


#include "SacrificeAlter.h"
#include "../Abilities/MovementAbilities/JumpAbility.h"
#include "../Abilities/MovementAbilities/MoveAbility.h"

#include "../Abilities/PassiveAbilities/DefenceAbility.h"
#include "../Abilities/PassiveAbilities/HealthAbility.h"


// Sets default values
ASacrificeAlter::ASacrificeAlter()
{	
	maxAmtOfActAbl = 3;
	numOfMoveAbl   = 0;
	numOfPassAbl   = 0;
	numOfComAbl    = 0;

	alterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AlterMesh"));
	sacrificeUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("SacrificeUI"));


}

// Called when the game starts or when spawned
void ASacrificeAlter::BeginPlay()
{
	AInteractable::BeginPlay();
	SetName("Sacrifice Alter");

	sacrificeUI->GetUserWidgetObject()->AddToViewport();

	allAbilities = GetPlayerCharacter()->GetAbilities();

	for (int i = 0; i < allAbilities.Num(); ++i) {

		if (allAbilities[i]->GetIsActivated()) {
			activeAbilities.Add(allAbilities[i]);
		}
		else {
			deactiveAbilities.Add(allAbilities[i]);
		}
	}
}



// Called every frame
void ASacrificeAlter::Tick(float DeltaTime)
{
	AInteractable::Tick(DeltaTime);
	sacrificeUI->SetVisibility(false);

	if (GetPlayerCharacter()->GetIsInteracting()) {
		sacrificeUI->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		sacrificeUI->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
	}
}



void ASacrificeAlter::Interact()
{
}

void ASacrificeAlter::OpenUI()
{
	
}

void ASacrificeAlter::SetActiveAbilites()
{
	//check how many active Abilities there are 
	if (activeAbilities.Num() == maxAmtOfActAbl) {

	}
}

void ASacrificeAlter::SetActiveAbilitiesText(FString movementAby, FString passiveAby, FString combatAby)
{
	//movementAby = 
}





