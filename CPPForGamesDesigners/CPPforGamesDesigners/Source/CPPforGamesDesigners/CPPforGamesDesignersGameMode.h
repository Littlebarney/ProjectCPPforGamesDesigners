// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "CPPforGamesDesignersGameMode.generated.h"


UCLASS(minimalapi)
class ACPPforGamesDesignersGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACPPforGamesDesignersGameMode();

	virtual void BeginPlay() override;

	void AddTime(float TimeToAdd); //Call when completed

protected:
	void UpdateTimer(); // Called each second
	void EndGame();		//Called when time reaches 0.

private:
	FTimerHandle TimerHandle;
	float RemainingTime;

	UPROPERTY(EditAnywhere, Category = "Game Timer")
	float StartingTime = 3.0f; //Time given to the player at the start of the game.

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UUserWidget* GameOverWidget;
};



