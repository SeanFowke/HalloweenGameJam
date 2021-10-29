// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilitiesBase.h"
#include "CombatAbilitiesBase.generated.h"

/**
 * 
 */
UCLASS()
class HALLOWEENGAMEJAM_API UCombatAbilitiesBase : public UAbilitiesBase
{
	GENERATED_BODY()

	float originalStat;
	float statMultiplyer; // Should never be equal to or above 100

public:

	UCombatAbilitiesBase();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Invoke() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void SetOrigStat(float value);
	float GetOrigStat();

	void SetStatMultiplyer(float value);
	float GetStatMultiplyer();

};
