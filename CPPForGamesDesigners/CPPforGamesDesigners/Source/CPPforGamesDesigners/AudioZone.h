// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioZone.generated.h"

class UBoxComponent;
class USoundBase;
class UAudioComponent;

UCLASS()
class CPPFORGAMESDESIGNERS_API AAudioZone : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAudioZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) //Root setup
	TObjectPtr<USceneComponent>_Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) //Box Collision
	TObjectPtr<UBoxComponent>_Box;
	TObjectPtr<UAudioComponent>_AudioComponent; //AudioPlayerRef

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TObjectPtr<USoundBase> AudioSoundtrack; //Sound to play.

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
