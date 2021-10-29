// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"



// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	playerCharacter = nullptr;
	distanceFromPlayer = -1.0f;
	playerInRange = false;
	name = "";

}

void AInteractable::Interact()
{
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	playerCharacter = Cast<AHalloweenGameJamCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
}

void AInteractable::SetName(FString name_)
{
	name = name_;
}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AInteractable::OpenUI() {

}

FString AInteractable::GetName()
{
	return name;
}


inline AHalloweenGameJamCharacter* AInteractable::GetPlayerCharacter()
{
	return playerCharacter;
}


