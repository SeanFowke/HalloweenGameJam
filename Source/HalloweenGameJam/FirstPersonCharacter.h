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
	void SetTVRef(class ATelevisionActor* tv_);

	class AHalloweenGameJamCharacter* GetSideScrollerRef();

	bool canInteractWithTV = false;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UWidgetComponent* widget;

	APlayerController* controller;

	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds);


	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	bool isSprinting = false;
	bool moving = false;


	class AHalloweenGameJamCharacter* sideScrollerRef;
	class ATelevisionActor* tvRef;


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

protected:

	void OnSprint();
	void OnWalk();

	void OnInteract();

	void OnEscape();


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

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;


public:

	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }


};
