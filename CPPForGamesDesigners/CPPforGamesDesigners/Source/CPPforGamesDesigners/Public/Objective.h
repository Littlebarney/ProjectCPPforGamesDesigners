#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objective.generated.h"

UCLASS()
class CPPFORGAMESDESIGNERS_API AObjective : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AObjective();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The collision component to detect when the player collides with the objective
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionComponent;

	// Points awarded when the player reaches this objective
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
	int32 PointsToAward = 1;

	//Called when the player collides with the objective
	UFUNCTION()
	void OnObjectiveTouched(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function to initialize objective
	void InitializeObjective(int32 Points);
};