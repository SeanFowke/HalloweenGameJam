// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatAbilitiesBase.h"

UCombatAbilitiesBase::UCombatAbilitiesBase(){}

void UCombatAbilitiesBase::BeginPlay()
{
	UAbilitiesBase::BeginPlay();

}

void UCombatAbilitiesBase::SetOrigStat(float value)
{

	originalStat = value; 
}

float UCombatAbilitiesBase::GetOrigStat()
{
	return originalStat;
}

void UCombatAbilitiesBase::SetStatMultiplyer(float value)
{
	statMultiplyer = value;
}

float UCombatAbilitiesBase::GetStatMultiplyer()
{
	return statMultiplyer;
}




// Called every frame
void UCombatAbilitiesBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UAbilitiesBase::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatAbilitiesBase::Invoke()
{
}

