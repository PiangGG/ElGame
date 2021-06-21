// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/BatteryComponent.h"

// Sets default values for this component's properties
UBatteryComponent::UBatteryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	MaxSize = 100.0f;
	CurrentSize = MaxSize;
	bCanUpdate=false;
	Speed=1.0f;
}


float UBatteryComponent::GetRatio()
{
	return CurrentSize/MaxSize;
}

// Called when the game starts
void UBatteryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UBatteryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (bCanUpdate)
	{
		UpdateSize(DeltaTime,Speed);
	}
}

void UBatteryComponent::SetSize(float size)
{
	CurrentSize=FMath::Clamp(size,0.0f,MaxSize);
	//CurrentSize=size;
}

float UBatteryComponent::GetSize()
{
	return CurrentSize;
}

void UBatteryComponent::UpdateSize(float DeltaTime,float speed)
{
	if (CurrentSize<=MaxSize)
	{
		//CurrentSize+=speed;
		CurrentSize+=DeltaTime*speed;
		//CurrentSize+=DeltaTime;
	}
}
inline void UBatteryComponent::SetCanUpdate(bool bcan,float speed)
{
	bCanUpdate=bcan;
	Speed=speed;
}