// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "SacrificeAlter.generated.h"

UCLASS()
class HALLOWEENGAMEJAM_API ASacrificeAlter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASacrificeAlter();
	virtual void Tick(float DeltaTime) override;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	class AHalloweenGameJamCharacter* playerCharacter;

	UPROPERTY(VisibleAnywhere)
	float distanceFromPlayer;

	bool playerInRange;

	void GetDistantToPlayer();
	
	

};
