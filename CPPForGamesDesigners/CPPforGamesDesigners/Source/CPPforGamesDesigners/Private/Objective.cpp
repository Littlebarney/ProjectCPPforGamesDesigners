// Fill out your copyright notice in the Description page of Project Settings.


#include "Objective.h"


// Sets default values
AObjective::AObjective()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AObjective::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjective::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AObjective::OnObjectiveTouched(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the object that touched the objective is the player
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		// Award points to the player
		Player->AddPoints(PointsToAward);

		// Optionally destroy the objective after being reached
		Destroy();  // Or move it, make invisible, etc.
	}
}


