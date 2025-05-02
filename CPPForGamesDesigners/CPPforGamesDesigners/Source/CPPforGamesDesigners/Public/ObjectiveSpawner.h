// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objective.h"
#include "Components/BoxComponent.h"
#include "ObjectiveSpawner.generated.h"

UCLASS()
class CPPFORGAMESDESIGNERS_API AObjectiveSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AObjectiveSpawner();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	int32 GetSpawnedObjectiveCount() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int32 SpawnedObjectiveCount = 0;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Reference to the Objective class 
	UPROPERTY(EditAnywhere, Category = "Objective")
	TSubclassOf<AObjective> ObjectiveClass;

	//Box Component that defines potential spawn locations
	UPROPERTY(VisibleAnywhere, Category = "Objective Spawner")
	UBoxComponent* SpawnAreaBox;

	//Chance to spawn an objective at each location (0-100)
	UPROPERTY(EditAnywhere, Category = "ObjectiveSpawning")
	int32 SpawnChance = 50; //50 is the default value

	void SpawnObjectives();

private:
	//Random Location within the spawn area box
	FVector GetRandomSpawnLocation(); 
};
