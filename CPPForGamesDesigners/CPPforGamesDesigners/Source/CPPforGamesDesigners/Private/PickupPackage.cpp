// Package.cpp

#include "PickupPackage.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerCharacter.h" // Your player class

APickupPackage::APickupPackage()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create collision component
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetBoxExtent(FVector(50.f));
	CollisionComponent->SetCollisionProfileName(TEXT("Trigger"));

	// Bind overlap event
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APickupPackage::OnPackagePickedUp);

	// Create visual mesh
	PackageMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PackageMesh"));
	PackageMesh->SetupAttachment(RootComponent);
}

void APickupPackage::BeginPlay()
{
	Super::BeginPlay();
}

void APickupPackage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickupPackage::OnPackagePickedUp(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		Player->PickupPackage(); //Talking to the function on the player
		Destroy();
	}
}
