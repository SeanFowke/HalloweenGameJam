// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FirstPersonCharacter.generated.h"

UCLASS()
class HALLOWEENGAMEJAM_API AFirstPersonCharacter : public ACharacter
{

public:
	// Sets default values for this character's properties
	AFirstPersonCharacter();

	GENERATED_BODY()

		/** Pawn mesh: 1st person view (arms; seen only by self) */
		//UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
		//class USkeletalMeshComponent* Mesh1P;

		/** Gun mesh: 1st person view (seen only by self) */
		/*UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FP_Gun;*/

		/** Location on gun mesh where projectiles should spawn. */



	UPROPERTY(EditAnywhere, Category = Sound)
		class UAudioComponent* audioComp;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* FP_MuzzleLocation;

	/** Gun mesh: VR view (attached to the VR controller directly, no arm, just the actual gun) */
	/*UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* VR_Gun;*/


	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;


	void SetSideScrollerRef(class AHalloweenGameJamCharacter* character_);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UWidgetComponent* widget;

	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds);


	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool holdingMirror = false;
	bool isSprinting = false;
	bool moving = false;

	class AMonsterV2* monster;
	class AInteractableObject* objectRef;
	FTimerHandle sprintTimer;
	float stamina;

	UPROPERTY(EditAnywhere)
		float maxStamina;

	FTimerHandle mirrorTimer;
	float mirrorHoldAmount;

	UPROPERTY(EditAnywhere)
		float mirrorHoldAmountMax;

	FTimerHandle footstepTimer;
	UPROPERTY(EditAnywhere)
		float footstepDelay;


public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector GunOffset;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		uint32 bUsingMotionControllers : 1;

protected:

	/** Fires a projectile. */
	void OnFire();

	void OnSprint();
	void OnWalk();

	void OnInteract();

	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false; Location = FVector::ZeroVector; }
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	//void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	//void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	//void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/*
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	//bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	//FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }


};