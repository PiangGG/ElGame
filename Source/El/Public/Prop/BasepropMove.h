// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/Baseprop.h"
#include "BasepropMove.generated.h"

/**
 * 
 */
UCLASS()
class EL_API ABasepropMove : public ABaseprop
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void DoSomethinging(float speed) override;
	

public:
	FVector StartLocation;
	FVector EndLocation;
};
