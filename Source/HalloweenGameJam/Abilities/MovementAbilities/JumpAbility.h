// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MovementAbilitiesBase.h"
#include "JumpAbility.generated.h"

/**
 *
 * This Ability was altered so that it now gives a boost when the player presses jump while already jumping giving the 
 * player a jet pack like ability 
 */

UCLASS()
class HALLOWEENGAMEJAM_API UJumpAbility : public UMovementAbilitiesBase
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere)
	float boostPower;  // the fuel for the jetpack
public:
	UJumpAbility();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Invoke() override;
	inline float GetBoostPower() { return boostPower; }

protected:
	virtual void BeginPlay() override;


};
