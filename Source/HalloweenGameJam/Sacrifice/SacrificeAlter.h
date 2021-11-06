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



/*
* TODO:
* Change so that it can handle when the player has no abilities 
* when the player enters for the first time 3 random abilities will be given 
*/

UCLASS()
class HALLOWEENGAMEJAM_API ASacrificeAlter : public AInteractable
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	TArray<class UAbilitiesBase*> activeAbilities;

	UPROPERTY(VisibleAnywhere)
	TArray<class UAbilitiesBase*> inactiveAbilities;

	bool noActiveAbilities;

	//used when the player clicks ok on the new UI and agrees to the 3 random abilities given 
	bool OkClickedNewUI; 

	
public:	
	// Sets default values for this actor's properties
	ASacrificeAlter();
	virtual void Tick(float DeltaTime) override;
	virtual void Interact() override;

	void SetActiveAbilites();
	void SetInactiveAbilites();

	void SetRandStarterAbl(); // sets the 3 random starter abilities 

	UPROPERTY(VisibleAnywhere)
	TArray<class UAbilitiesBase*> allAbilities;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	UWidgetComponent* sacrificeUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	UWidgetComponent* confirmationUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	UWidgetComponent* newAbilityUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* alterMesh;


	class UAbilitiesBase* newSwapAbility;
	class UAbilitiesBase* oldSwapAbility;


	// 3 Random Abilities
	class UAbilitiesBase* randAbl_0;
	class UAbilitiesBase* randAbl_1;
	class UAbilitiesBase* randAbl_2;

	TArray<UAbilitiesBase*> removeAbility(TArray<UAbilitiesBase*> abilityArray, FString abilityName_);


public:	
 // UI Functions

	UFUNCTION(BlueprintCallable)
	void SetNewAbility(UTextBlock* textBox/*description at some point*/);

	UFUNCTION(BlueprintCallable)
	void OldSwapAbility(UTextBlock* textBox);

	UFUNCTION(BlueprintCallable)
	void SacUIOkButton();	  // used for the sacrifice UI 

	UFUNCTION(BlueprintCallable)
	void ConUIOkButton();	  // used for the confirmation UI 

	UFUNCTION(BlueprintCallable)
	void CancelButton();

	UFUNCTION(BlueprintCallable)
	void NewUIOkButton();	  // used for the New Ability UI 

	UFUNCTION(BlueprintCallable)
	void GetNewAblName(UTextBlock* Txt);

	UFUNCTION(BlueprintCallable)
	void GetOldAblName(UTextBlock* Txt);

	UFUNCTION(BlueprintCallable)
	void RandAbl0(UTextBlock* textBox);

	UFUNCTION(BlueprintCallable)
	void RandAbl1(UTextBlock* textBox);

	UFUNCTION(BlueprintCallable)
	void RandAbl2(UTextBlock* textBox);

	

};
