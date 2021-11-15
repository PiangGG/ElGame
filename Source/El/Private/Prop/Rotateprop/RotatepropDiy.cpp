// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Rotateprop/RotatepropDiy.h"

#include "Component/BatteryComponent.h"
#include "Gameplay/ElCharacter.h"

ARotatepropDiy::ARotatepropDiy()
{	
	StartLocation=BaseMesh->GetComponentLocation();
	TargetLocation=StartLocation;

	bBaseState=true;
}

void ARotatepropDiy::BeginPlay()
{
	Super::BeginPlay();
}

void ARotatepropDiy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ARotatepropDiy::DoSomethinging(float speed)
{
	
	if (BatteryComp->GetSize()>0)
	{
		if (MoveSpeed!=FVector(0.0f))
		{
			if(OverlapCharacter)
			{
				TargetLocation+=OverlapCharacter->GetActorForwardVector();
				BaseMesh->SetRelativeLocation(TargetLocation);
			}
			else
			{
				TargetLocation+=GetActorForwardVector();
				BaseMesh->SetRelativeLocation(TargetLocation);
			}
		}
		bBaseState=false;
	}
}
