// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CombatAbilitiesBase.h"
#include "AttackAbility.generated.h"

/**
 * 
 */
UCLASS()
class HALLOWEENGAMEJAM_API UAttackAbility : public UCombatAbilitiesBase
{
	GENERATED_BODY()

public:
	UAttackAbility();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Invoke()override;

protected:
	virtual void BeginPlay() override;

private:
	
};
