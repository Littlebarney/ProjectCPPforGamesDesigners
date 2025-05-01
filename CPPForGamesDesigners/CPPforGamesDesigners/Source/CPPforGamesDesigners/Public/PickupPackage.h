#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupPackage.generated.h"

UCLASS()
class CPPFORGAMESDESIGNERS_API APickupPackage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupPackage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Box collision to detect pickup
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionComponent;

	// Mesh to visualize the package
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* PackageMesh;

	// Called when overlapping with player
	UFUNCTION()
	void OnPackagePickedUp(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	virtual void Tick(float DeltaTime) override;
};