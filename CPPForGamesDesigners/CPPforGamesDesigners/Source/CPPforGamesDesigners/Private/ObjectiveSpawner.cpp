// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveSpawner.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"

// Sets default values
AObjectiveSpawner::AObjectiveSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creating the Box Component to show the engine where it can spawn an objective.
	SpawnAreaBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnAreaBox"));
	RootComponent = SpawnAreaBox;
	SpawnAreaBox->SetCollisionProfileName(TEXT("No Collision"));
	SpawnAreaBox->SetBoxExtent(FVector(500.0f, 500.0f, 500.0f));
}

// Called when the game starts or when spawned
void AObjectiveSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnObjectives();
}

// Called every frame
void AObjectiveSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AObjectiveSpawner::SpawnObjectives()
{
	if(ObjectiveClass)
	{
		for (int i = 0; i < 3; i++)
		{
			//Generate random positions within the box
			FVector SpawnLocation = GetRandomSpawnLocation();

			//Random number between 0 and 100
			int32 RandomValue = FMath::RandRange(0, 100);

			//if randomValue is less than the spawn chance, spawn an objective.
			if (RandomValue < SpawnChance)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;

				//Spawn the objective actor at the random locations
				AObjective* NewObjective = GetWorld()->SpawnActor<AObjective>(ObjectiveClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);

				if (NewObjective)
				{
					NewObjective->InitializeObjective(1);
				}

				SpawnedObjectiveCount++;
			}
		}
	}
}

FVector AObjectiveSpawner::GetRandomSpawnLocation()
	{
		if (SpawnAreaBox)
		{
		//Getting the size of the box
		FVector BoxCentre = SpawnAreaBox->GetComponentLocation();
		FVector BoxExtent = SpawnAreaBox->GetScaledBoxExtent();

		//Generate random points within the boxs extent
		float RandomX = FMath::RandRange(BoxCentre.X - BoxExtent.X, BoxCentre.X + BoxExtent.X);
		float RandomY = FMath::RandRange(BoxCentre.Y - BoxExtent.Y, BoxCentre.Y + BoxExtent.Y);
		float RandomZ = FMath::RandRange(BoxCentre.Z - BoxExtent.Z, BoxExtent.Z + BoxExtent.Z);
		return FVector(RandomX, RandomY, RandomZ);
		}

	return FVector::ZeroVector;
	}

int32 AObjectiveSpawner::GetSpawnedObjectiveCount() const
{
	UE_LOG(LogTemp, Log, TEXT("Current Objective Count: %d"), GetSpawnedObjectiveCount());
	
	return SpawnedObjectiveCount;
}

	


