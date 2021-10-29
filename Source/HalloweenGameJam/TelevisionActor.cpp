// Fill out your copyright notice in the Description page of Project Settings.


#include "TelevisionActor.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "FirstPersonCharacter.h"

// Sets default values
ATelevisionActor::ATelevisionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = mesh;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	boxComponent->SetupAttachment(RootComponent);

	tvCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	tvCameraComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATelevisionActor::BeginPlay()
{
	Super::BeginPlay();
	
	boxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATelevisionActor::OnOverlap);
	boxComponent->OnComponentEndOverlap.AddDynamic(this, &ATelevisionActor::OnOverlapEnd);
	
}

// Called every frame
void ATelevisionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATelevisionActor::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherComp)
	{
		AFirstPersonCharacter* fps = Cast<AFirstPersonCharacter>(OtherActor);

		if (fps)
		{
			fps->SetTVRef(this);
			fps->canInteractWithTV = true;
		}
	}
}

void ATelevisionActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this && OverlappedComp)
	{
		AFirstPersonCharacter* fps = Cast<AFirstPersonCharacter>(OtherActor);

		if (fps)
		{
			fps->canInteractWithTV = false;
			fps->SetTVRef(nullptr);
		}
	}
}

