// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Math/UnrealMathUtility.h"
#include "AbilitiesBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HALLOWEENGAMEJAM_API UAbilitiesBase : public UActorComponent
{
	GENERATED_BODY()
private:
	class AHalloweenGameJamCharacter* playerCharacter;

public:	
	// Sets default values for this component's properties
	UAbilitiesBase();
	UPROPERTY(EditAnywhere)
	bool isActivated;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	inline bool GetIsActivated() { return isActivated; }
	inline class AHalloweenGameJamCharacter* GetPlayerCharacter()const { return playerCharacter; }

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetPlayerCharacter(class AHalloweenGameJamCharacter* ref_);
	inline void SetIsActivated(bool isActivated_) { isActivated = isActivated_; }
	virtual void Invoke();
		
};
