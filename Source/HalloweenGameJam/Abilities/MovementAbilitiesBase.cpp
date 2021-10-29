// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementAbilitiesBase.h"
#include "Kismet/GameplayStatics.h"



// Sets default values for this component's properties
UMovementAbilitiesBase::UMovementAbilitiesBase():UAbilitiesBase(){}


// Called when the game starts
void UMovementAbilitiesBase::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UMovementAbilitiesBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMovementAbilitiesBase::Invoke()
{
}




