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

	class UAbilitiesBase* newSwapAbility;
	class UAbilitiesBase* oldSwapAbility;


	void removeAbility(TArray<UAbilitiesBase*> abilityArray, FString abilityName_);


public:	
 // UI Functions

	UFUNCTION(BlueprintCallable)
		void SetNewAbility(UTextBlock* textBox/*description at some point*/);

	UFUNCTION(BlueprintCallable)
		void OldSwapAbility(UTextBlock* textBox);

	UFUNCTION(BlueprintCallable)
		void OkButton();

	UFUNCTION(BlueprintCallable)
		void CancelButton();
	

};
