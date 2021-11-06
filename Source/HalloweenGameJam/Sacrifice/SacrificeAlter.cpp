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
	newAbilityUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("NewAbilityUI"));
	noActiveAbilities = true;
	OkClickedNewUI = false;

}

// Called when the game starts or when spawned
void ASacrificeAlter::BeginPlay()
{
	Super::BeginPlay();

	SetName("Sacrifice Alter");

    sacrificeUI->GetUserWidgetObject()->AddToViewport();
	confirmationUI->GetUserWidgetObject()->AddToViewport();
	newAbilityUI->GetUserWidgetObject()->AddToViewport();

	sacrificeUI->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
	confirmationUI->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
	newAbilityUI->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);

	/*
	*                          TODO:
	* need to set both noActiveAbilities and OkClickedNEwUI here  
	* no active abilities will be set depending on if the player has active abilities 
	* OkClickedNEwUI Will be set on it the first bool is true or false 
	* if noActiveAbilities is false then OkClickedNEwUI would be true
	* May need to do this in tick as allabilities are set there and not in beginplay
	* 
	*/


}

// Called every frame
void ASacrificeAlter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Set the visibilty of both Sacrifice UI and Confermation UI to false
	sacrificeUI->SetVisibility(false);
	confirmationUI->SetVisibility(false);
	newAbilityUI->SetVisibility(false);

	//if all abilities is empty fill it with all the abilities in that the player has active or inactive
	if (allAbilities.Num() <= 0) {
		for (int i = 0; i < GetPlayerCharacter()->GetAbilities().Num(); ++i) {
			allAbilities.Add(GetPlayerCharacter()->GetAbilities()[i]);
		}

		SetInactiveAbilites();
	}

	Interact();
}


void ASacrificeAlter::Interact()
{
	if (GetPlayerCharacter()->GetIsInteracting()) {

		//if ok was clicked in the new ability UI
		if (!OkClickedNewUI) {

			//if there are no active abilities 
			if (noActiveAbilities)
			{
				//set the 3 abilities from the all abilities array 
				SetRandStarterAbl();

				//active abilities are now set 
				noActiveAbilities = false;
			}

			//make new ability UI Visible 
			newAbilityUI->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Visible);

			//show the mouse 
			GetPlayerCharacter()->GetPlyController()->SetShowMouseCursor(true);
		}

		else {
			// set the UI tp visible and show the mouse cursor on screen
			sacrificeUI->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Visible);
			GetPlayerCharacter()->GetPlyController()->SetShowMouseCursor(true);
		}
	}

	else {
		//otherwise hide bothe sacrifice UI and confirmation UI if thats visible  and hide cursor
		sacrificeUI->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
		confirmationUI->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
		GetPlayerCharacter()->GetPlyController()->SetShowMouseCursor(false);

		//set the swap abilities to nullptr since the UI isnt open 
		newSwapAbility = nullptr;
		oldSwapAbility = nullptr;
	}	
}


void ASacrificeAlter::SetActiveAbilites()
{
	//sets all abilities in the active array from the all abilities array 
	for (int i = 0; i < allAbilities.Num(); ++i) {

		if (allAbilities[i]->GetIsActivated()) {
			activeAbilities.Add(allAbilities[i]);
		}
	}
}

void ASacrificeAlter::SetInactiveAbilites()
{
	//sets all abilities in the Inactive array from the all abilities array 
	for (int i = 0; i < allAbilities.Num(); ++i) {

		if (!allAbilities[i]->GetIsActivated()) {
			inactiveAbilities.Add(allAbilities[i]);
		}
	}
}

void ASacrificeAlter::SetRandStarterAbl()
{
	// temp array that holds all the player abilities 
	TArray<UAbilitiesBase*> tmpAbilityArray = allAbilities;

	//get a random int for from 0  to length of the array 
	int randNum_0 = FMath::RandRange(0, tmpAbilityArray.Num() - 1);

	// set rand ability  to a random one in 
	randAbl_0 = tmpAbilityArray[randNum_0];

	//remove that ability from the array 
	tmpAbilityArray.RemoveAt(randNum_0);

	//random ability 2
	int randNum_1 = FMath::RandRange(0, tmpAbilityArray.Num() - 1);

	randAbl_1 = tmpAbilityArray[randNum_1];

	tmpAbilityArray.RemoveAt(randNum_1);

	//random ability 2
	int randNum_2 = FMath::RandRange(0, tmpAbilityArray.Num() - 1);

	randAbl_2 = tmpAbilityArray[randNum_2];

	tmpAbilityArray.RemoveAt(randNum_2);

	randAbl_0->SetIsActivated(true);
	randAbl_1->SetIsActivated(true);
	randAbl_2->SetIsActivated(true);

	randAbl_0->Invoke();
	randAbl_1->Invoke();
	randAbl_2->Invoke();

	SetActiveAbilites();
}

TArray<UAbilitiesBase*> ASacrificeAlter::removeAbility(TArray<UAbilitiesBase*> abilityArray,FString abilityName_)
{
	//remove ability the inactive or active array
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
	//ceheck if new swap Ability is null 
	if (!newSwapAbility) {

		//get a random int for from 0  to length of the array 
		int randNum = FMath::RandRange(0, inactiveAbilities.Num() - 1);

		//assign a Inactive abilities to the new  swap ability 
		newSwapAbility = inactiveAbilities[randNum];

		//set the text of the old ability in the UI
		textBox->SetText(FText::FromString(newSwapAbility->GetName()));
	}
}

void ASacrificeAlter::OldSwapAbility(UTextBlock* textBox)			
{
	//ceheck if old swap Ability is null
	if (activeAbilities.Num() > 0) {
		if (!oldSwapAbility) {

			//get a random int for from 0  to length of the array 
			int randNum = FMath::RandRange(0, activeAbilities.Num() - 1);

			//assign a active abilities to the old swap ability 
			oldSwapAbility = activeAbilities[randNum];

			//set the text of the old ability in the UI
			textBox->SetText(FText::FromString(oldSwapAbility->GetName()));
		}
	}
}

void ASacrificeAlter::SacUIOkButton()
{
	//set the sacrifice UI To visible 
	confirmationUI->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Visible);
}

void ASacrificeAlter::ConUIOkButton()
{
	// new and old swap abilites are set to an ability 
	if (oldSwapAbility && newSwapAbility) {

		//remove  new ability from the inactive array
		inactiveAbilities = removeAbility(inactiveAbilities, newSwapAbility->GetName()); 

		//remove the old ability from active array
		activeAbilities = removeAbility(activeAbilities, oldSwapAbility->GetName());  

		// add the new active ability to the active array 
		activeAbilities.Add(newSwapAbility);

		//add the swaped ability to the inactive array 
		inactiveAbilities.Add(oldSwapAbility);

		//set the old ability to not active 
		oldSwapAbility->SetIsActivated(false);

		//call invoke, this is needed for some abilities to set stats back to their original values
		oldSwapAbility->Invoke();

		//set new ability to active 
		newSwapAbility->SetIsActivated(true);

		//call invoke to set new abilities stats to player 
		newSwapAbility->Invoke();

		//set the players interacting bool to false to help close sacrifice menu 
		GetPlayerCharacter()->SetIsInterActing(false);
	}
}

void ASacrificeAlter::NewUIOkButton() 
{
	GetPlayerCharacter()->SetIsInterActing(false);
	newAbilityUI->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
	OkClickedNewUI = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Ok Button on New UI Was Pressed"));
}

void ASacrificeAlter::CancelButton()
{
	GetPlayerCharacter()->SetIsInterActing(false);
}

void ASacrificeAlter::GetNewAblName(UTextBlock* Txt)
{
	if (newSwapAbility)
	{
		Txt->SetText(FText::FromString(newSwapAbility->GetName()));
	}
}

void ASacrificeAlter::GetOldAblName(UTextBlock* Txt)
{
	if (oldSwapAbility)
	{
		Txt->SetText(FText::FromString(oldSwapAbility->GetName()));
	}
}

void ASacrificeAlter::RandAbl0(UTextBlock* textBox)
{
	if (randAbl_0) 
	{
		textBox->SetText(FText::FromString(randAbl_0->GetName()));
	}
}

void ASacrificeAlter::RandAbl1(UTextBlock* textBox)
{
	if (randAbl_1) 
	{
		textBox->SetText(FText::FromString(randAbl_1->GetName()));
	}
}

void ASacrificeAlter::RandAbl2(UTextBlock* textBox)
{
	if (randAbl_2) 
	{
		textBox->SetText(FText::FromString(randAbl_2->GetName()));
	}
}
