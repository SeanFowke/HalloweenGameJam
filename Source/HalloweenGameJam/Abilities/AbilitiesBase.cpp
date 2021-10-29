// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitiesBase.h"

// Sets default values for this component's properties
UAbilitiesBase::UAbilitiesBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbilitiesBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbilitiesBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAbilitiesBase::SetPlayerCharacter(AHalloweenGameJamCharacter* ref_)
{
	playerCharacter = ref_;
}

void UAbilitiesBase::Invoke()
{
}

