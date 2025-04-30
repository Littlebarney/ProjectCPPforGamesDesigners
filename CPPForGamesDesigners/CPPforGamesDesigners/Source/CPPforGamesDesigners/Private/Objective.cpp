// Fill out your copyright notice in the Description page of Project Settings.


#include "Objective.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"

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
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AObjective::AObjective::OnObjectiveTouched);

	//Mesh
	UStaticMeshComponent* VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
	VisualMesh->SetupAttachment(RootComponent);
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
	UE_LOG(LogTemp, Warning, TEXT("Objective Touched!")); 
	
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		// Give points (you'll need to implement AddPoints() in your player character)
		Player->AddPoints(PointsToAward);

		// Optional: Visual feedback or sound
		UE_LOG(LogTemp, Log, TEXT("Objective reached! %d points awarded."), PointsToAward);

		// Destroy or deactivate objective
		Destroy();  // You can also hide or deactivate instead
	}
}


