// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAbility.h"

UAttackAbility::UAttackAbility() {

}

void UAttackAbility::BeginPlay()
{
	Super::BeginPlay();
	SetName("Attack Ability");
}

void UAttackAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{ 
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAttackAbility::Invoke()
{
}


