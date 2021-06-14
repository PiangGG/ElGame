// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/GameOver/BaseGameOverActor.h"

#include "Components/BoxComponent.h"
#include "GameFramework/GameModeBase.h"
#include "Gameplay/ElCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseGameOverActor::ABaseGameOverActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp=CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent=RootComp;
	
	BoxComp=CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this,&ABaseGameOverActor::OnOverlayBegin);
	BoxComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseGameOverActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseGameOverActor::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AElCharacter *Character=Cast<AElCharacter>(OtherActor);
	if (Character)
	{
		UGameplayStatics::GetGameMode(GWorld)->SetPause(UGameplayStatics::GetPlayerController(GWorld,0));
		Character->GameOver();
	}
}

// Called every frame
void ABaseGameOverActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

