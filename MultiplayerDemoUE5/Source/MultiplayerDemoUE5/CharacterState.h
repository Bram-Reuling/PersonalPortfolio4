// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CharacterState.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERDEMOUE5_API ACharacterState : public APlayerState
{
	GENERATED_BODY()
	
public:
	virtual void CopyProperties(APlayerState* PlayerState) override;
	virtual void OverrideWith(APlayerState* PlayerState) override;

	UPROPERTY(BlueprintReadWrite)
	int ScoreTest = 0;
};
