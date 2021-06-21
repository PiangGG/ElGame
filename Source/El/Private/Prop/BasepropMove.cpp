// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/BasepropMove.h"

void ABasepropMove::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation=GetActorLocation();
	this->SetActorScale3D(FVector(5.0,10.f,1.0f));
}

void ABasepropMove::DoSomethinging(float speed)
{
	this->AddActorLocalOffset(GetActorForwardVector());
}
