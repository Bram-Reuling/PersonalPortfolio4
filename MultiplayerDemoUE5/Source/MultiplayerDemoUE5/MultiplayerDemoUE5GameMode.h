// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MultiplayerDemoUE5GameMode.generated.h"

UCLASS(minimalapi)
class AMultiplayerDemoUE5GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMultiplayerDemoUE5GameMode();

	UFUNCTION(BlueprintCallable)
	void TravelTo(FString Map);
};



