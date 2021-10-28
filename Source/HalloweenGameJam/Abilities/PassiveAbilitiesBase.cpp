// Fill out your copyright notice in the Description page of Project Settings.


#include "PassiveAbilitiesBase.h"

// Sets default values for this component's properties
UPassiveAbilitiesBase::UPassiveAbilitiesBase():UAbilitiesBase(){}


// Called when the game starts
void UPassiveAbilitiesBase::BeginPlay()
{
	UAbilitiesBase::BeginPlay();

}

void UPassiveAbilitiesBase::SetOrigStat(float value)
{
	originalStat = value;
}

float UPassiveAbilitiesBase::GetOrigStat()
{
	return originalStat;
}

void UPassiveAbilitiesBase::SetStatMultiplyer(float value)
{
	statMultiplyer = value;
}

int UPassiveAbilitiesBase::GetStatMultiplyer()
{
	return statMultiplyer;
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



