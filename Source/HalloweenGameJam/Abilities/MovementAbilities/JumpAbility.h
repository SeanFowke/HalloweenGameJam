// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MovementAbilitiesBase.h"
#include "JumpAbility.generated.h"

/**
 *
 */
UCLASS()
class HALLOWEENGAMEJAM_API UJumpAbility : public UMovementAbilitiesBase
{
	GENERATED_BODY()
private:


public:
	UJumpAbility();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Invoke() override;

protected:
	virtual void BeginPlay() override;


};
