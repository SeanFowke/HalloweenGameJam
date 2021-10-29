// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../PassiveAbilitiesBase.h"
#include "DefenceAbility.generated.h"

/**
 * 
 */
UCLASS()
class HALLOWEENGAMEJAM_API UDefenceAbility : public UPassiveAbilitiesBase
{
	GENERATED_BODY()

public:
	UDefenceAbility();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Invoke()override;

protected:
	virtual void BeginPlay() override;

private:
	
};
