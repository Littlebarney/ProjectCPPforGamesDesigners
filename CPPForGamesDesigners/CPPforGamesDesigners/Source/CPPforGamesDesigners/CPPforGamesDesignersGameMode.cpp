// Copyright Epic Games, Inc. All Rights Reserved.

#include "CPPforGamesDesignersGameMode.h"
#include "CPPforGamesDesignersCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACPPforGamesDesignersGameMode::ACPPforGamesDesignersGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
