// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TelevisionActor.generated.h"

UCLASS()
class HALLOWEENGAMEJAM_API ATelevisionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATelevisionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//  variables

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UCameraComponent* tvCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* boxComponent;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
