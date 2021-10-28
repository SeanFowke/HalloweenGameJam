// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAbility.h"

void UAttackAbility::BeginPlay()
{
	UCombatAbilitiesBase::BeginPlay();
}

void UAttackAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UCombatAbilitiesBase::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAttackAbility::Invoke()
{
}


