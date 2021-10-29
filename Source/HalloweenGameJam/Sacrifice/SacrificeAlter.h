// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interactable.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "SacrificeAlter.generated.h"

UCLASS()
class HALLOWEENGAMEJAM_API ASacrificeAlter : public AInteractable
{
	GENERATED_BODY()

	//Max number of Active Abilities
	int maxAmtOfActAbl;

	//number of movement Abilites
	int numOfMoveAbl;

	//number of Passive Abilities	
	int numOfPassAbl;

	//number of combat abilities
	int numOfComAbl;



	UPROPERTY(VisibleAnywhere)
	TArray<class UAbilitiesBase*> activeAbilities;

	UPROPERTY(VisibleAnywhere)
	TArray<class UAbilitiesBase*> inactiveAbilities;

	
public:	
	// Sets default values for this actor's properties
	ASacrificeAlter();
	virtual void Tick(float DeltaTime) override;
	virtual void Interact() override;
	virtual void OpenUI() override;

	void SetActiveAbilites();
	void SetInactiveAbilites();

	UPROPERTY(VisibleAnywhere)
	TArray<class UAbilitiesBase*> allAbilities;
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	UWidgetComponent* sacrificeUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* alterMesh;

	// equipped Abilities
	UPROPERTY(VisibleAnywhere)
	class UMovementAbilitiesBase* eMoveAbility;

	UPROPERTY(VisibleAnywhere)
	class UPassiveAbilitiesBase* ePassiveAbility;

	UPROPERTY(VisibleAnywhere)
	class UCombatAbilitiesBase* eCombatAbility;

	void removeAbility(FString abilityName_);


public:	
 // UI Functions

	UFUNCTION(BlueprintCallable)
		FString SetMoveAbilityText(/*FString movementAby, FString passiveAby, FString combatAby*/);

	UFUNCTION(BlueprintCallable)
		FString SetPassAbilityText(/*FString movementAby, FString passiveAby, FString combatAby*/);

	UFUNCTION(BlueprintCallable)
		FString SetCombAbilityText(/*FString movementAby, FString passiveAby, FString combatAby*/);

	UFUNCTION(BlueprintCallable)
		void SetMovementButtons(TArray<UTextBlock*> buttonTxt);

	UFUNCTION(BlueprintCallable)
		void SetPassiveButtons(TArray<UTextBlock*> buttonTxt);

	UFUNCTION(BlueprintCallable)
		void SetCombatButtons(TArray<UTextBlock*> buttonTxt);

	UFUNCTION(BlueprintCallable)
		void OnButtonClicked(UTextBlock* buttonTxt);
	
	

};
