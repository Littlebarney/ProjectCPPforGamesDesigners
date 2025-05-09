// Fill out your copyright notice in the Description page of Project Settings.


#include "PackageSpawner.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
APackageSpawner::APackageSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APackageSpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(CheckAndSpawnTimerHandle, this, &APackageSpawner::CheckAndSpawn, CheckInterval, true);

	CheckAndSpawn();
}


void APackageSpawner::CheckAndSpawn()
{
	if (!PackageToSpawn)
	{
		UE_LOG(LogTemp, Error, TEXT("PackageToSpawn is NULL!"));
		return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FOUND PACKAGE"));
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PackageToSpawn, FoundActors);

	UE_LOG(LogTemp, Warning, TEXT("Found %d existing package(s)"), FoundActors.Num());

	if (FoundActors.Num() == 0)
	{
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = FRotator::ZeroRotator;

		GetWorld()->SpawnActor<AActor>(PackageToSpawn, SpawnLocation, SpawnRotation);
		UE_LOG(LogTemp, Warning, TEXT("Spawned a Package"));
	}
}



void APackageSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}




