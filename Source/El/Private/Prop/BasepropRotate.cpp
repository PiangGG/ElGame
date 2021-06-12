// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/BasepropRotate.h"

void ABasepropRotate::BeginPlay()
{
	Super::BeginPlay();
	this->SetActorScale3D(FVector(5.0,10.f,1.0f));
	StartRotaor=GetActorForwardVector().Rotation();
}

void ABasepropRotate::DoSomethinging(float speed)
{
	StartRotaor.Yaw+=speed;
	BaseMesh->SetWorldRotation(StartRotaor);
}
