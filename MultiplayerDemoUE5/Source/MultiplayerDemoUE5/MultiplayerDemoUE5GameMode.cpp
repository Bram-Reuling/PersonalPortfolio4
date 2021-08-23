// Copyright Epic Games, Inc. All Rights Reserved.

#include "MultiplayerDemoUE5GameMode.h"
#include "MultiplayerDemoUE5Character.h"
#include "UObject/ConstructorHelpers.h"

AMultiplayerDemoUE5GameMode::AMultiplayerDemoUE5GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMultiplayerDemoUE5GameMode::TravelTo(FString Map)
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	
	bUseSeamlessTravel = true;
	World->ServerTravel(Map);
}



