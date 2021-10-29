// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Abilities/AbilitiesBase.h"
#include "Abilities/MovementAbilities/JumpAbility.h"
#include "Abilities/MovementAbilities/MoveAbility.h"
#include "Abilities/PassiveAbilities/DefenceAbility.h"
#include "Abilities/PassiveAbilities/HealthAbility.h"
#include "Abilities/CombatAbilities/AttackAbility.h"
#include "HalloweenGameJamCharacter.generated.h"


UCLASS(config = Game)
class AHalloweenGameJamCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	class UJumpAbility* jumpAbility;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	class UMoveAbility* moveAbility;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	class UDefenceAbility* defenceAbility;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	class UHealthAbility* healthAbility;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	class UAttackAbility* attackAbility;
	
	UPROPERTY(VisibleAnywhere)
	TArray<UAbilitiesBase*> playerAbilities;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* interactCapsule;

	UPROPERTY(VisibleAnywhere)
	bool isInteracting;

	UPROPERTY(VisibleAnywhere)
	bool interactableInRange;

	FTimerHandle delayedBeginPlay;

protected:

	/** Called for side to side input */
	void MoveRight(float Val);
	void PlayerJump();
	void Interact(); 
	float moveY;
	bool canJump;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(VisibleAnywhere)
	float defenceStat;

	UPROPERTY(VisibleAnywhere)
	float healthStat;

	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);



	class AFirstPersonCharacter* fpsRef;
	APlayerCameraManager* cameraManager;

public:
	AHalloweenGameJamCharacter();
	
	void SetDefenceStat(float value);
	float GetDefenceStat();

	void SetHealthStat(float value);
	float GetHealthStat();

	void ExitTVView();

	APlayerController* GetPlyController();

	//void AddAbility(UAbilitiesBase* ability);
	TArray<UAbilitiesBase*> GetAbilities();
	UAbilitiesBase* GetAbility(TArray<UAbilitiesBase*> abilityArray_,FString name_);

	bool GetIsInteracting();
	inline void SetIsInterActing(bool isInteracting_) { isInteracting = isInteracting_; }

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	void SetFirstPersonRef(class AFirstPersonCharacter* character_);

	void FocusOnActor(AActor* focus_, float rate_);

	APlayerCameraManager* GetCameraManager();

	class AFirstPersonCharacter* getFpsCharacter();

	inline void AddAbility(UAbilitiesBase* ability) { playerAbilities.Add(ability); }
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverLappedComp, AActor* otherActor, UPrimitiveComponent* otherComp,
						int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* overLappedComp, AActor* otherActor, 
					  UPrimitiveComponent* otherComp, int32 otherBodyIndex);
};
