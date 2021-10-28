// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interactable.h"
#include "Components/WidgetComponent.h"
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

	TArray<class UAbilitiesBase*> activeAbilities;
	TArray<class UAbilitiesBase*> deactiveAbilities;

	UPROPERTY(VisibleAnywhere)
	TArray<class UAbilitiesBase*> allAbilities;

	
public:	
	// Sets default values for this actor's properties
	ASacrificeAlter();
	virtual void Tick(float DeltaTime) override;
	virtual void Interact() override;
	virtual void OpenUI() override;

	void SetActiveAbilites();

	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	UWidgetComponent* sacrificeUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* alterMesh;

	class UMovmentAbilitiesBase* equipedMoveAbility;
	class UPassiveAbilitiesBase* equipedPassiveAbility;
	class UCombatAbilitiesBase*  equipedCombatAbility;


public:	
 // UI Functions

	UFUNCTION(BlueprintCallable)
		void SetActiveAbilitiesText(FString movementAby, FString passiveAby, FString combatAby);
	
	

};
