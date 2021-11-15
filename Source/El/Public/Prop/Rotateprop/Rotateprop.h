// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/Rotateprop/Baseprop.h"
#include "Rotateprop.generated.h"

/**
 * 
 */
UCLASS()
class EL_API ARotateprop : public ABaseprop
{
	GENERATED_BODY()

public:
	
	ARotateprop();
protected:
	virtual void BeginPlay() override;

	virtual void DoSomethinging(float speed) override;
	
	virtual void Tick(float DeltaSeconds) override;
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FRotator StartRotator;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FRotator TargetRotator;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FRotator RotatorSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector StartLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector TargetLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector MoveSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector StartScale3D;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector TargetScale3D;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector MoveScale3D;
};
