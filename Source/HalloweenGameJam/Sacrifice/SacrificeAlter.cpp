// Fill out your copyright notice in the Description page of Project Settings.


#include "SacrificeAlter.h"
#include "Math/Vector.h"
#include "../HalloweenGameJamCharacter.h"

// Sets default values
ASacrificeAlter::ASacrificeAlter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	playerCharacter = nullptr;
	distanceFromPlayer = -1.0f;
	playerInRange = false;

}

// Called when the game starts or when spawned
void ASacrificeAlter::BeginPlay()
{
	Super::BeginPlay();
	playerCharacter = Cast<AHalloweenGameJamCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void ASacrificeAlter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetDistantToPlayer();
}

void ASacrificeAlter::GetDistantToPlayer()
{
	float tmp = GetActorLocation().Y - playerCharacter->GetActorLocation().Y;
	distanceFromPlayer = FMath::Abs(tmp);
}

