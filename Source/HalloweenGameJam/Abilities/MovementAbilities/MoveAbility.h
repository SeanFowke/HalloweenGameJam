
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../MovementAbilitiesBase.h"
#include "MoveAbility.generated.h"


UCLASS()
class HALLOWEENGAMEJAM_API UMoveAbility : public UMovementAbilitiesBase
{
	GENERATED_BODY()

	float oriGroundFric;
	float oriDeAccel;


public:
	// Sets default values for this component's properties
	UMoveAbility();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Invoke() override;


};
