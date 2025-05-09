// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioZone.h"

#include "NavigationSystemTypes.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAudioZone::AAudioZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;

	//Box Trigger Setup
	_Box = CreateDefaultSubobject<UBoxComponent>(TEXT("AudioZoneBox"));
	_Box->SetupAttachment(_Root);
	_Box->InitBoxExtent(FVector(300.f, 300.f, 200.f));
	_Box->SetHiddenInGame(false);

	_Box->OnComponentBeginOverlap.AddDynamic(this, &AAudioZone::OnOverlapBegin);
	_Box->OnComponentEndOverlap.AddDynamic(this, &AAudioZone::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AAudioZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAudioZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAudioZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == UGameplayStatics::GetPlayerPawn(this, 0)) //Check it is the Player 0 Pawn Overlapping.
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Overlap Audio Zone Begin"));
		_AudioComponent = UGameplayStatics::SpawnSound2D(this, AudioSoundtrack, 1.0f, 1.0f, 0.0f, nullptr, false, true);
	}
}

void AAudioZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == UGameplayStatics::GetPlayerPawn(this, 0)) //Check it is the Player 0 Pawn Overlap
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Overlap Audio Zone End"));
		if (_AudioComponent){_AudioComponent->FadeOut(5.0f, 0.0f, EAudioFaderCurve::Linear);}
	}
}


