// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ElTypes.h"
#include "GameFramework/PlayerController.h"
#include "ElController.generated.h"

/**
 * 
 */
UCLASS()
class EL_API AElController : public APlayerController
{
	GENERATED_BODY()

public:
	AElController();

	EControllerState::Type CurrControllerState;

	void ChangeControllerState(EControllerState::Type newtype);

	void GameOnlyState();

	void UIOnlyState();

	void GameAndUIState();
};
