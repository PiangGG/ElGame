// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Prop_LunchCharacter.h"

#include "Common/ElHelper.h"
#include "Component/BatteryComponent.h"
#include "Gameplay/ElCharacter.h"
#include "Kismet/GameplayStatics.h"

AProp_LunchCharacter::AProp_LunchCharacter()
{
	this->BaseMesh->SetRelativeScale3D(FVector(2.0,2.f,0.3f));
	bBaseState=true;
}

void AProp_LunchCharacter::BeginPlay()
{
	Super::BeginPlay();
	StartLocation=GetActorLocation();
	CurrentLocation=StartLocation;
}

void AProp_LunchCharacter::DoSomethinging(float speed)
{
	if (BatteryComp->GetSize()>0)
	{
		if (OverlapCharacter)
		{
			FVector Dirction = OverlapCharacter->GetActorForwardVector()+OverlapCharacter->GetActorUpVector();
			OverlapCharacter->LaunchCharacter(Dirction*BatteryComp->GetSize()*10,false,false);
		
		}
		this->AddActorLocalOffset(GetActorUpVector()*(BatteryComp->GetSize()*2));
		BatteryComp->SetSize(0.0f);
		
		CurrentLocation=GetActorLocation();
		bBaseState=false;
	}
}

inline void AProp_LunchCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	ElHelper::Debug(FString("StartLocation:"+StartLocation.ToString()),0);
	ElHelper::Debug(FString("CurretLoction:"+CurrentLocation.ToString()),0);
	if (bBaseState==false)
	{
		CurrentLocation=FMath::VInterpTo(CurrentLocation,StartLocation,DeltaSeconds,1.0f);
		this->SetActorRelativeLocation(CurrentLocation);
		if (StartLocation==CurrentLocation)
		{
			bBaseState=true;
		}
	
	}
}

void AProp_LunchCharacter::OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlayEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	
}

