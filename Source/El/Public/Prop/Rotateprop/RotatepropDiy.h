// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/Rotateprop/Rotateprop.h"
#include "RotatepropDiy.generated.h"

/**
 * 
 */
UCLASS()
class EL_API ARotatepropDiy : public ARotateprop
{
	GENERATED_BODY()
	ARotatepropDiy();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void DoSomethinging(float speed) override;
};
