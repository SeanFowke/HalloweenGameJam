// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "HalloweenGameJamCharacter.h"
#include "Interactable.generated.h"

UCLASS()
class HALLOWEENGAMEJAM_API AInteractable : public AActor
{
	GENERATED_BODY()

	AHalloweenGameJamCharacter* playerCharacter;

	UPROPERTY(VisibleAnywhere)
	float distanceFromPlayer;

	bool playerInRange;
	
	FString name;
	
public:	
	// Sets default values for this actor's properties
	AInteractable();
	virtual void Interact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay()override;
	void SetName(FString name_);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime);
	bool GetInRange() { return playerInRange; }
	FString GetName();
	virtual void OpenUI();
	AHalloweenGameJamCharacter* GetPlayerCharacter();

};
