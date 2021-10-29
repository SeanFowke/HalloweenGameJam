// Fill out your copyright notice in the Description page of Project Settings.


#include "SacrificeAlter.h"
#include "../Abilities/MovementAbilitiesBase.h"
#include "../Abilities/PassiveAbilitiesBase.h"




// Sets default values
ASacrificeAlter::ASacrificeAlter()
{	

	alterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AlterMesh"));
	sacrificeUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("SacrificeUI"));
	confirmationUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("ConfrimationUI"));


}

// Called when the game starts or when spawned
void ASacrificeAlter::BeginPlay()
{
	AInteractable::BeginPlay();
	SetName("Sacrifice Alter");
    sacrificeUI->GetUserWidgetObject()->AddToViewport();
	confirmationUI->GetUserWidgetObject()->AddToViewport();
}

// Called every frame
void ASacrificeAlter::Tick(float DeltaTime)
{
	AInteractable::Tick(DeltaTime);
	sacrificeUI->SetVisibility(false);
	confirmationUI->SetVisibility(false);

	if (GetPlayerCharacter()->GetIsInteracting()) {
		sacrificeUI->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Visible);
		GetPlayerCharacter()->GetPlyController()->SetShowMouseCursor(true); 
	}

	else {
		sacrificeUI->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
		confirmationUI->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
		GetPlayerCharacter()->GetPlyController()->SetShowMouseCursor(false);
		newSwapAbility = nullptr;
		oldSwapAbility = nullptr;
	}

	if (allAbilities.Num() <= 0) {
		for (int i = 0; i < GetPlayerCharacter()->GetAbilities().Num(); ++i) {
			allAbilities.Add(GetPlayerCharacter()->GetAbilities()[i]);
		}

		SetActiveAbilites();
		SetInactiveAbilites();
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
	for (int i = 0; i < allAbilities.Num(); ++i) {

		if (allAbilities[i]->GetIsActivated()) {
			activeAbilities.Add(allAbilities[i]);
		}
	}
}


void ASacrificeAlter::SetInactiveAbilites()
{
	for (int i = 0; i < allAbilities.Num(); ++i) {

		if (!allAbilities[i]->GetIsActivated()) {
			inactiveAbilities.Add(allAbilities[i]);
		}
	}
}

TArray<UAbilitiesBase*> ASacrificeAlter::removeAbility(TArray<UAbilitiesBase*> abilityArray,FString abilityName_)
{
	UAbilitiesBase* toRemove;
	for (int i = 0; i < abilityArray.Num(); ++i) {
		if (abilityName_ == abilityArray[i]->GetName()) {
			toRemove = abilityArray[i];
			break;
		}
	}

	abilityArray.Remove(toRemove);

	return abilityArray;
	
}

void ASacrificeAlter::SetNewAbility(UTextBlock* textBox)
{
	if (!newSwapAbility) {
		int randNum = FMath::RandRange(0, inactiveAbilities.Num() - 1);
		newSwapAbility = inactiveAbilities[randNum];
		textBox->SetText(FText::FromString(newSwapAbility->GetName()));
	}
}

void ASacrificeAlter::OldSwapAbility(UTextBlock* textBox)			
{
	if (!oldSwapAbility) {
		int randNum = FMath::RandRange(0, activeAbilities.Num() - 1);
		oldSwapAbility = activeAbilities[randNum];
		textBox->SetText(FText::FromString(oldSwapAbility->GetName()));
	}
}

void ASacrificeAlter::SacUIOkButton()
{
	confirmationUI->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Visible);
}

void ASacrificeAlter::ConUIOkButton()
{
	if (oldSwapAbility && newSwapAbility) {

		inactiveAbilities = removeAbility(inactiveAbilities, newSwapAbility->GetName());
		activeAbilities = removeAbility(activeAbilities, oldSwapAbility->GetName());

		activeAbilities.Add(newSwapAbility);
		inactiveAbilities.Add(oldSwapAbility);

		oldSwapAbility->SetIsActivated(false);
		oldSwapAbility->Invoke();

		newSwapAbility->SetIsActivated(true);
		newSwapAbility->Invoke();

		GetPlayerCharacter()->SetIsInterActing(false);
	}
}

void ASacrificeAlter::CancelButton()
{
	GetPlayerCharacter()->SetIsInterActing(false);
}

void ASacrificeAlter::GetNewAblName(UTextBlock* Txt)
{
	Txt->SetText(FText::FromString(newSwapAbility->GetName()));
}

void ASacrificeAlter::GetOldAblName(UTextBlock* Txt)
{
	Txt->SetText(FText::FromString(oldSwapAbility->GetName()));
}
