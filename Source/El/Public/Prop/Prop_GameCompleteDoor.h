// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/Baseprop.h"
#include "Prop_GameCompleteDoor.generated.h"

/**
 * 
 */
UCLASS()
class EL_API AProp_GameCompleteDoor : public ABaseprop
{
	GENERATED_BODY()
	
	public:
	virtual void BeginPlay() override;
	virtual void DoSomethinging(float speed) override;
	bool bComplete = false;
};
