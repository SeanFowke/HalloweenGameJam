#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilitiesBase.h"
#include "MovementAbilitiesBase.generated.h"


/*
* /////TODO/////
* 
* Add a Description variable and a setter for it 
* 
*/

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HALLOWEENGAMEJAM_API UMovementAbilitiesBase : public UAbilitiesBase
{
	GENERATED_BODY()
private:
	float originalValue;


public:
	// Sets default values for this component's properties
	UMovementAbilitiesBase();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	inline void SetOrigValue(float value) { originalValue = value; }
	inline float GetOrigValue() { return originalValue; }
	



public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Invoke() override;
	
	




};