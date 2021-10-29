#include "DefenceAbility.h"
#include "../../HalloweenGameJamCharacter.h"

UDefenceAbility::UDefenceAbility():UPassiveAbilitiesBase() {}

void UDefenceAbility::BeginPlay()
{
	UPassiveAbilitiesBase::BeginPlay();
	SetOrigStat(GetPlayerCharacter()->GetDefenceStat());
	SetStatMultiplyer(75.0f);
}

void UDefenceAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UPassiveAbilitiesBase::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Invoke();
}

void UDefenceAbility::Invoke()
{
	float newStat = -1;

	if (GetIsActivated()) {
		newStat = (GetOrigStat() / GetStatMultiplyer()) * 100;

		GetPlayerCharacter()->SetDefenceStat(FMath::Floor(newStat));
	}

	else {
		GetPlayerCharacter()->SetDefenceStat(GetOrigStat());
	}
}


