// Fill out your copyright notice in the Description page of Project Settings.


#include "PassiveAbilitiesBase.h"

// Sets default values for this component's properties
UPassiveAbilitiesBase::UPassiveAbilitiesBase():UAbilitiesBase(){}


// Called when the game starts
void UPassiveAbilitiesBase::BeginPlay()
{
	UAbilitiesBase::BeginPlay();

}


// Called every frame
void UPassiveAbilitiesBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UAbilitiesBase::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPassiveAbilitiesBase::Invoke()
{
}



