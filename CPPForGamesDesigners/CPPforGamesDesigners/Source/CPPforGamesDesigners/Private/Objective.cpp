// Fill out your copyright notice in the Description page of Project Settings.


#include "Objective.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"
#include "CPPforGamesDesigners/CPPforGamesDesignersGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObjective::AObjective()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create and set collision component as Root
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetBoxExtent(FVector(100.f));
	CollisionComponent->SetCollisionProfileName("Trigger");

	//Bind overlap event
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AObjective::OnObjectiveTouched);


	//Mesh
	UStaticMeshComponent* VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
	VisualMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AObjective::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Objective Spawned"));
	
}

// Called every frame
void AObjective::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AObjective::OnObjectiveTouched(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACPPforGamesDesignersGameMode* GameMode = Cast<ACPPforGamesDesignersGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->AddTime(10.0f);
		UE_LOG(LogTemp, Warning, TEXT("10 Seconds Added")); 
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Objective Touched!")); 
	UE_LOG(LogTemp, Warning, TEXT("Objective overlapped with: %s"), *OtherActor->GetName());
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Successfully cast to APlayerCharacter"));

		if (Player->PackagesInVan > 0)
		{
			Player->AddPoints(PointsToAward);
			Player->PackagesInVan--; //Decreases number of packages
			UE_LOG(LogTemp, Log, TEXT("Package delivered! %d packages remaining."), Player->PackagesInVan);

			Destroy();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No packages to deliver!"))
		}
	}
}

void AObjective::InitializeObjective(int32 Points)
{
	PointsToAward = Points;
}



