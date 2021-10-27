// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Abilities/AbilitiesBase.h"
#include "HalloweenGameJamCharacter.generated.h"


UCLASS(config = Game)
class AHalloweenGameJamCharacter : public ACharacter
{
	GENERATED_BODY()

		/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	class UJumpAbility* jumpAbility;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	class UMoveAbility* moveAbility;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	class UDefenceAbility* defenceAbility;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	class UHealthAbility* healthAbility;
	
	UPROPERTY(VisibleAnywhere)
	TArray<UAbilitiesBase*> playerAbilities;

protected:

	/** Called for side to side input */
	void MoveRight(float Val);
	void PlayerJump();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(VisibleAnywhere)
	float defenceStat;

	UPROPERTY(VisibleAnywhere)
	float healthStat;


public:
	AHalloweenGameJamCharacter();
	
	inline void SetDefenceStat(float value) { defenceStat = value; }
	inline float GetDefenceStat() { return defenceStat; }

	inline void SetHealthStat(float value) { healthStat = value; }
	inline float GetHealthStat() { return healthStat; }

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	inline void AddAbility(UAbilitiesBase* ability) { playerAbilities.Add(ability); }
};
