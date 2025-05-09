// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PackageSpawner.generated.h"

UCLASS()
class CPPFORGAMESDESIGNERS_API APackageSpawner : public AActor
{
	GENERATED_BODY()

	FTimerHandle CheckAndSpawnTimerHandle;

public:
	// Sets default values for this actor's properties
	APackageSpawner();

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> PackageToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float CheckInterval = 3.0f; //How often to check (Seconds)

	UFUNCTION()
	void CheckAndSpawn();
	
protected:
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
