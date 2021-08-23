// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterState.h"

void ACharacterState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);
	if (PlayerState)
	{
		ACharacterState* TestState = Cast<ACharacterState>(PlayerState);

		if (TestState)
		{
			TestState->ScoreTest = ScoreTest;
		}
	}
}

void ACharacterState::OverrideWith(APlayerState* PlayerState)
{
	Super::OverrideWith(PlayerState);
	if (PlayerState)
	{
		ACharacterState* TestState = Cast<ACharacterState>(PlayerState);

		if (TestState)
		{
			ScoreTest = TestState->ScoreTest;
		}
	}
}
