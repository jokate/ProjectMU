// Copyright Epic Games, Inc. All Rights Reserved.

#include "MoonUGameMode.h"
#include "MoonUCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMoonUGameMode::AMoonUGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
