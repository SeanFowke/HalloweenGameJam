// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpAbility.h"
#include "../../HalloweenGameJamCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


UJumpAbility::UJumpAbility() :UMovementAbilitiesBase() {
	boostPower = 40.f;
}


void UJumpAbility::Invoke()
{
	if (GetIsActivated()) {
		//reduce the players jump height 
		GetPlayerCharacter()->GetCharacterMovement()->JumpZVelocity = 800.0f;

		//check if the player is boosting 
		if (GetPlayerCharacter()->GetIsBoostJumping()) {

			if (boostPower > 0.f) {

				int boostMultiplyer = 350000;

				// creating new vectot for the jet pack  
				FVector jumpBoost = FVector(0.0f, 0.0f, 1.f) * boostMultiplyer;

				//adding force to the players Z axis 
				GetPlayerCharacter()->GetCharacterMovement()->AddForce(jumpBoost);

				//subtract fuel from the jetpack while player is using it 
				boostPower -= 1.f;
			}

			else {
				//set players is boosting to false when  the boost power is empty 
				GetPlayerCharacter()->SetIsBoostJumping(false);
			}

		} 

		if (!GetPlayerCharacter()->GetIsJumping() || !GetPlayerCharacter()->GetIsBoostJumping()) {
			
			// refule boost power
			if (boostPower < 40.f) {
				boostPower += 0.009f;
			}

			else {

			}
		}
	}

	else {
		// set the players jump back to normal when the ability isnt activated 
		GetPlayerCharacter()->GetCharacterMovement()->JumpZVelocity = GetOrigValue();
		boostPower = 40.f;
	}


	//just so boost power dosent go into the negatvie
	if (boostPower < -0.0f) {
		boostPower = 0.f;
	}
}


void UJumpAbility::BeginPlay()
{
	Super::BeginPlay();
	SetOrigValue(GetPlayerCharacter()->GetCharacterMovement()->JumpZVelocity);
	SetName("Jump Ability");
}

void UJumpAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Invoke();

}



 //Old Jump Ability

/*if (GetIsActivated()) {
	GetPlayerCharacter()->GetCharacterMovement()->JumpZVelocity = 1100.0f;
}

else {
	GetPlayerCharacter()->GetCharacterMovement()->JumpZVelocity = GetOrigValue();
}	  */