// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Rotateprop/Rotateprop.h"

#include "Component/BatteryComponent.h"
#include "Gameplay/ElCharacter.h"

ARotateprop::ARotateprop()
{
	//BaseMesh->GetComponentTransform();
	StartRotator=BaseMesh->GetComponentRotation();
	TargetRotator=StartRotator;

	StartLocation=BaseMesh->GetComponentLocation();
	TargetLocation=StartLocation;

	StartScale3D=GetActorScale3D();
	TargetScale3D=StartScale3D;
	
	bBaseState=true;
}

void ARotateprop::BeginPlay()
{
	Super::BeginPlay();
	
}
void ARotateprop::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (!bDosomething)
	{
		if (TargetRotator!=StartRotator)
		{
			TargetRotator=FMath::RInterpTo(TargetRotator,StartRotator,DeltaSeconds,1.0f);
			BaseMesh->SetRelativeRotation(TargetRotator);
		}

		if (TargetLocation!=StartLocation)
		{
			TargetLocation=FMath::VInterpTo(TargetLocation,StartLocation,DeltaSeconds,1.0f);
			BaseMesh->SetRelativeLocation(TargetLocation);
		}
		if (TargetScale3D!=StartScale3D)
		{
			TargetScale3D=FMath::VInterpTo(TargetScale3D,StartScale3D,DeltaSeconds,1.0f);
			SetActorScale3D(TargetScale3D);
		}
	}
}
void ARotateprop::DoSomethinging(float speed)
{
	if (BatteryComp->GetSize()>0)
	{
		if (RotatorSpeed!=FRotator(0.0f))
		{
			TargetRotator+=RotatorSpeed*speed;
			BaseMesh->SetRelativeRotation(TargetRotator);
		}

		if (MoveSpeed!=FVector(0.0f))
		{
			TargetLocation+=MoveSpeed*speed;
			//TargetLocation+=OverlapCharacter->GetActorForwardVector();
			BaseMesh->SetRelativeLocation(TargetLocation);
		}
		if (MoveScale3D!=FVector(0.0f))
		{
			TargetScale3D+=MoveScale3D*speed;
			SetActorScale3D(TargetScale3D);
		}	
		
		bBaseState=false;
	}
}
