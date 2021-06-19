// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/Baseprop.h"
#include "Prop_LunchCharacter.generated.h"

/**
 * 
 */
UCLASS()
class EL_API AProp_LunchCharacter : public ABaseprop
{
	GENERATED_BODY()

public:
	AProp_LunchCharacter();
protected:	
	virtual void BeginPlay() override;
	
	virtual void DoSomethinging(float speed) override;
	
	virtual void Tick(float DeltaSeconds) override;

	//virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;	
private:
	FVector StartLocation;
	FVector CurrentLocation;
	
};