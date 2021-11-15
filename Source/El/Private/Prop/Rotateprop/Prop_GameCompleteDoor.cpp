// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Rotateprop/Prop_GameCompleteDoor.h"

#include "Components/BoxComponent.h"
#include "Gameplay/ElGMInGame.h"
#include "Kismet/GameplayStatics.h"

AProp_GameCompleteDoor::AProp_GameCompleteDoor()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("StaticMesh'/Game/Res/Meshs/Sphere.Sphere'"));
	BaseMesh->SetStaticMesh(StaticMesh.Object);
	BoxComp->SetBoxExtent(FVector(128));
}

void AProp_GameCompleteDoor::BeginPlay()
{
	Super::BeginPlay();
}

void AProp_GameCompleteDoor::DoSomethinging(float speed)
{
	if (bComplete==false)
	{
		bComplete=true;
		Cast<AElGMInGame>(UGameplayStatics::GetGameMode(GWorld))->SetGameComplate();
	}
}
