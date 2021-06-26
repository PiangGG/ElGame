// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/GameOver/GameCompleteProp.h"

#include "Components/BoxComponent.h"
#include "GameFramework/GameModeBase.h"
#include "Gameplay/ElCharacter.h"
#include "Gameplay/ElGMInGame.h"
#include "Kismet/GameplayStatics.h"


AGameCompleteProp::AGameCompleteProp()
{

	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("StaticMesh'/Game/introduce/beffio/Medieval_Kingdom/Content/Models/MagicStone/SM_Magic_Stone.SM_Magic_Stone'"));
	BaseMesh2=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh2"));
	BaseMesh2->SetStaticMesh(StaticMesh.Object);
	BaseMesh2->SetupAttachment(RootComp);
}
void AGameCompleteProp::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AElCharacter *Character=Cast<AElCharacter>(OtherActor);
	if (Character)
	{
		//UGameplayStatics::GetGameMode(GWorld)->SetPause(UGameplayStatics::GetPlayerController(GWorld,0));
		Cast<AElGMInGame>(UGameplayStatics::GetGameMode(GWorld))->SetGameComplate();
	}
}

