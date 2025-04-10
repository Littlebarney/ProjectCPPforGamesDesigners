// Copyright Epic Games, Inc. All Rights Reserved.

#include "CPPforGamesDesignersGameMode.h"
#include "CPPforGamesDesignersCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACPPforGamesDesignersGameMode::ACPPforGamesDesignersGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/BP_PlayerCharacter"));

	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
