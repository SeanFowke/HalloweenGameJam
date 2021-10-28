// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthAbility.h"
#include "../../HalloweenGameJamCharacter.h"

UHealthAbility::UHealthAbility() :UPassiveAbilitiesBase() {

}

void UHealthAbility::BeginPlay()
{
	UPassiveAbilitiesBase::BeginPlay();
	SetOrigStat(GetPlayerCharacter()->GetHealthStat());
	SetStatMultiplyer(75.0f);
	SetName("Health Ability");
}

void UHealthAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UPassiveAbilitiesBase::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Invoke();
}

void UHealthAbility::Invoke()
{
	float newStat = -1;

	if (GetIsActivated()) {
		newStat = (GetOrigStat() / GetStatMultiplyer()) * 100.0f;
		GetPlayerCharacter()->SetHealthStat(FMath::Floor(newStat));
	}

	else {
		GetPlayerCharacter()->SetHealthStat(GetOrigStat());
	}
}
