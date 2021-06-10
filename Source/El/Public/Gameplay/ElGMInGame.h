// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "El/ElGameModeBase.h"

#include "ElGMInGame.generated.h"

/**
 * 
 */
UCLASS()
class EL_API AElGMInGame : public AElGameModeBase
{
	GENERATED_BODY()
public:
	AElGMInGame();
	virtual void BeginPlay() override;
};
