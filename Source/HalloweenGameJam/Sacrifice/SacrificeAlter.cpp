// Fill out your copyright notice in the Description page of Project Settings.


#include "SacrificeAlter.h"
#include "../Abilities/MovementAbilitiesBase.h"
#include "../Abilities/PassiveAbilitiesBase.h"




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
}

// Called every frame
void ASacrificeAlter::Tick(float DeltaTime)
{
	AInteractable::Tick(DeltaTime);
	sacrificeUI->SetVisibility(false);

	if (GetPlayerCharacter()->GetIsInteracting()) {
		sacrificeUI->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Visible);
		GetPlayerCharacter()->GetPlyController()->SetShowMouseCursor(true);
	}
	else {
		sacrificeUI->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
		GetPlayerCharacter()->GetPlyController()->SetShowMouseCursor(false);
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

			if (UMovementAbilitiesBase* mAbl = Cast<UMovementAbilitiesBase>(allAbilities[i])) {

				if (numOfMoveAbl <= 0) {
					eMoveAbility = mAbl; 
					eMoveAbility->Invoke();
					numOfMoveAbl += 1;
				}

				else {
					continue;
				}
			}

			else if(UPassiveAbilitiesBase* pAbl = Cast<UPassiveAbilitiesBase>(allAbilities[i])) {

				if (numOfPassAbl <= 0) {
					ePassiveAbility = pAbl;
					ePassiveAbility->Invoke();
					numOfPassAbl += 1;
				}

				else {
					continue;
				}
			}

			else if (UCombatAbilitiesBase* cAbl = Cast<UCombatAbilitiesBase>(allAbilities[i])) {

				if (numOfComAbl <= 0) {
					eCombatAbility = cAbl;
					eCombatAbility->Invoke();
					numOfComAbl += 1;
				}

				else {
					continue;
				}
			}
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

void ASacrificeAlter::removeAbility(FString abilityName_)
{
	UAbilitiesBase* toRemove;
	for (int i = 0; i < inactiveAbilities.Num(); ++i) {
		if (abilityName_ == inactiveAbilities[i]->GetName()) {
			toRemove = inactiveAbilities[i];
			break;
		}
	}

	inactiveAbilities.Remove(toRemove);
}

FString ASacrificeAlter::SetMoveAbilityText()
{
	return eMoveAbility->GetName();
}

FString ASacrificeAlter::SetPassAbilityText()
{
	return ePassiveAbility->GetName();
}

FString ASacrificeAlter::SetCombAbilityText()
{
	return  eCombatAbility->GetName();
}

void ASacrificeAlter::SetMovementButtons(TArray<UTextBlock*> buttonTxt)
{
	for (int i = 0; i < buttonTxt.Num(); ++i) {

		for (int j = 0; j < inactiveAbilities.Num(); ++j) {

			if (UMovementAbilitiesBase* mAbl = Cast<UMovementAbilitiesBase>(inactiveAbilities[j]))
			{
				if (i <= 0) {
					buttonTxt[i]->SetText(FText::FromString(mAbl->GetName()));
				}

				else{
					if (buttonTxt[i - 1]->GetText().ToString() == mAbl->GetName()) {
						continue;
					}
				}
				
			}
		}
	}
}

void ASacrificeAlter::SetPassiveButtons(TArray<UTextBlock*> buttonTxt)
{

	for (int i = 0; i < buttonTxt.Num(); ++i) {
		for (int j = 0; j < inactiveAbilities.Num(); ++j) {

			if (UPassiveAbilitiesBase* pAbl = Cast<UPassiveAbilitiesBase>(inactiveAbilities[j]))
			{
				if (i <= 0) {
					buttonTxt[i]->SetText(FText::FromString(pAbl->GetName()));
				}

				else {
					if (buttonTxt[i - 1]->GetText().ToString() == pAbl->GetName()) {
						continue;
					}
				}
			}
		}
	}
}

void ASacrificeAlter::SetCombatButtons(TArray<UTextBlock*> buttonTxt)
{
	for (int i = 0; i < buttonTxt.Num(); ++i) {
		for (int j = 0; j < inactiveAbilities.Num(); ++j) {

			if (UCombatAbilitiesBase* cAbl = Cast<UCombatAbilitiesBase>(inactiveAbilities[j]))
			{
				if (i <= 0) {
					buttonTxt[i]->SetText(FText::FromString(cAbl->GetName()));
				}

				else {
					if (buttonTxt[i - 1]->GetText().ToString() == cAbl->GetName()) {
						continue;
					}
				}
			}

		}
	}

}

void ASacrificeAlter::OnButtonClicked(UTextBlock* buttonTxt)
{
	
	if (UAbilitiesBase* abl = Cast<UAbilitiesBase>(GetPlayerCharacter()->GetAbility(inactiveAbilities, buttonTxt->GetText().ToString()))) {
		//Do Check to see what ability type it is 
		//UAbilitiesBase* abl = GetPlayerCharacter()->GetAbility(inactiveAbilities, buttonTxt->GetText().ToString());
		 //remove ability from inactive list

		if (UMovementAbilitiesBase* mAbl = Cast<UMovementAbilitiesBase>(abl)) {
			removeAbility(abl->GetName());

			eMoveAbility->SetIsActivated(false);

			//call invoke to set get rid of stat boost 
			eMoveAbility->Invoke();

			inactiveAbilities.Add(eMoveAbility);

			eMoveAbility = (UMovementAbilitiesBase*)mAbl;
			eMoveAbility->SetIsActivated(true);
			eMoveAbility->Invoke();
		}

		else if (UPassiveAbilitiesBase* pAbl = Cast<UPassiveAbilitiesBase>(abl)) {
			removeAbility(pAbl->GetName());

			ePassiveAbility->SetIsActivated(false);

			//call invoke to set get rid of stat boost 
			ePassiveAbility->Invoke();

			inactiveAbilities.Add(ePassiveAbility);

			ePassiveAbility = (UPassiveAbilitiesBase*)pAbl;
			ePassiveAbility->SetIsActivated(true);
			ePassiveAbility->Invoke();
		}

		else if (UCombatAbilitiesBase* cAbl = Cast<UCombatAbilitiesBase>(abl)) {
			removeAbility(cAbl->GetName());

			eCombatAbility->SetIsActivated(false);

			//call invoke to set get rid of stat boost 
			eCombatAbility->Invoke();

			inactiveAbilities.Add(ePassiveAbility);

			eCombatAbility = (UCombatAbilitiesBase*)cAbl;
			eCombatAbility->SetIsActivated(true);
			eCombatAbility->Invoke();
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Button Clicked"));
	}
	
}




