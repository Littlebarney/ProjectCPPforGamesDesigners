// Copyright Epic Games, Inc. All Rights Reserved.

#include "CPPforGamesDesignersGameMode.h"
#include "CPPforGamesDesignersCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ACPPforGamesDesignersGameMode::ACPPforGamesDesignersGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/BP_PlayerCharacter"));

	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
	PrimaryActorTick.bCanEverTick = false; 
}

void ACPPforGamesDesignersGameMode::BeginPlay()
{
	Super::BeginPlay();

	RemainingTime = StartingTime;

	//Count down
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACPPforGamesDesignersGameMode::UpdateTimer, 1.0f, true);
}

void ACPPforGamesDesignersGameMode::UpdateTimer()
{
	RemainingTime -= 1.0f;
	UE_LOG(LogTemp, Log, TEXT("Time Left: %f"), RemainingTime);

	if(RemainingTime <= 0)
	{
		EndGame();
	}
}

void ACPPforGamesDesignersGameMode::AddTime(float TimeToAdd)
{
	RemainingTime += TimeToAdd;
	UE_LOG(LogTemp, Log, TEXT("Time Added: %f, New Time: %f"), TimeToAdd, RemainingTime);
}

void ACPPforGamesDesignersGameMode::EndGame()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
	UE_LOG(LogTemp, Warning, TEXT("Game Over!"));

	if(GameOverWidgetClass)
	{
		GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
		if (GameOverWidget)
		{
			GameOverWidget -> AddToViewport();

			APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (PC)
			{
				PC->bShowMouseCursor = true;

				FInputModeUIOnly InputMode;
				InputMode.SetWidgetToFocus(GameOverWidget->TakeWidget());
				InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
				PC->SetInputMode(InputMode);
			}
		}
	}
}
