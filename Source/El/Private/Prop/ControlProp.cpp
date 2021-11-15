// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/ControlProp.h"

// Sets default values
AControlProp::AControlProp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterial> State_Red(TEXT("Material'/Game/Res/Mat/PropMat/Red.Red'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> State_Green(TEXT("Material'/Game/Res/Mat/PropMat/Green.Green'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> State_Bule(TEXT("Material'/Game/Res/Mat/PropMat/blue.blue'"));

	RedMaterial=State_Red.Object;
	GreenMaterial=State_Green.Object;
	BlueMaterial=State_Bule.Object;
}

void AControlProp::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void AControlProp::Init()
{
	int state = FMath::RandRange(0,2);
	switch (state)
	{
	case  0:
		ChangeControlPropState_Red();
		break;
	case  1:
		ChangeControlPropState_Greend();
		break;
	case  2:
		ChangeControlPropState_Blue();
		break;
	default: break;
	}
}

// Called every frame
void AControlProp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AControlProp::ChangeControlPropState(EControlPropState::State newState)
{
	ControlPropState=newState;
	switch (ControlPropState)
	{
	case EControlPropState::Red:
		ChangeControlPropState_Red();
		break;
	case EControlPropState::Green:
		ChangeControlPropState_Greend();
		break;
	case EControlPropState::Blue:
		ChangeControlPropState_Blue();
		break;
	default: ;
	}
}

void AControlProp::ChangeControlPropState_Red()
{
	EndRotator=EndRotator_Red;
	EndLocation=EndLocation_Red;
	EndScale3D = EndScale3D_Red;
	BaseMesh->SetMaterial(0,RedMaterial);
}

void AControlProp::ChangeControlPropState_Greend()
{
	EndRotator=EndRotator_Green;
	EndLocation=EndLocation_Green;
	EndScale3D = EndScale3D_Green;
	BaseMesh->SetMaterial(0,GreenMaterial);
}

void AControlProp::ChangeControlPropState_Blue()
{
	EndRotator=EndRotator_Blue;
	EndLocation=EndLocation_Blue;
	EndScale3D = EndScale3D_Blue;
	BaseMesh->SetMaterial(0,BlueMaterial);
}

void AControlProp::ChangeNextState()
{
	switch (ControlPropState)
	{
	case EControlPropState::Red:
		ChangeControlPropState(EControlPropState::Green);
		break;
	case EControlPropState::Green:
		ChangeControlPropState(EControlPropState::Blue);
		break;
	case EControlPropState::Blue:
		ChangeControlPropState(EControlPropState::Red);
		break;
	default: break;
	}
}

