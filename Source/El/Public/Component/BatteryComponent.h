// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BatteryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EL_API UBatteryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBatteryComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetSize(float size);

	float GetSize();

	void UpdateSize(float DeltaTime,float Speed);

	virtual void SetCanUpdate(bool bcan,float speed);

	float GetRatio();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float MaxSize;
	float CurrentSize;
	bool bCanUpdate;
	float Speed;
};


