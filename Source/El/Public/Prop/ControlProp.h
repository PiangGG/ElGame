// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AutomaticProp.h"

#include "ControlProp.generated.h"

UCLASS()
class AControlProp : public AAutomaticProp
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AControlProp();

protected:
	virtual void BeginPlay() override;

	virtual void Init();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChangeControlPropState(EControlPropState::State newState);

	void ChangeControlPropState_Red();
	void ChangeControlPropState_Greend();
	void ChangeControlPropState_Blue();

	void ChangeNextState();
public:
	EControlPropState::State ControlPropState = EControlPropState::Red;
	class UMaterial* RedMaterial;
	class UMaterial* GreenMaterial;
	class UMaterial* BlueMaterial;

	//不同State
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=RedState)
	FRotator EndRotator_Red;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=RedState)
	FVector EndLocation_Red;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=RedState)
	FVector EndScale3D_Red;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=GreenState)
	FRotator EndRotator_Green;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=GreenState)
	FVector EndLocation_Green;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=GreenState)
	FVector EndScale3D_Green;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=BlueState)
	FRotator EndRotator_Blue;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=BlueState)
	FVector EndLocation_Blue;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=BlueState)
	FVector EndScale3D_Blue;
};
