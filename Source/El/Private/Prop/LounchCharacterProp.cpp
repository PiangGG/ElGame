// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/LounchCharacterProp.h"

#include "Common/ElHelper.h"
#include "Components/BoxComponent.h"
#include "Gameplay/ElCharacter.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ALounchCharacterProp::ALounchCharacterProp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp=CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));//根组件
	RootComponent=RootComp;
	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("StaticMesh'/Game/Res/Meshs/Cube.Cube'"));
	BaseMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));//网格
	BaseMesh->SetupAttachment(RootComp);
	BaseMesh->SetCollisionProfileName(FName("BaseMeshProfile"));
	BaseMesh->SetStaticMesh(StaticMesh.Object);
	BaseMesh->SetRelativeScale3D(FVector(0.3f));
	
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(BaseMesh);
	//BoxComp->SetCollisionProfileName(FName("BoxCompProfile"));
	BoxComp->SetGenerateOverlapEvents(true);
	
	//绑定检测方法到碰撞体
	FScriptDelegate OverlayBegin;
	OverlayBegin.BindUFunction(this,"OnOverlayBegin");
	BoxComp->OnComponentBeginOverlap.Add(OverlayBegin);
	
	FScriptDelegate OverlayEnd;
	OverlayEnd.BindUFunction(this,"OnOverlayEnd");
	BoxComp->OnComponentEndOverlap.Add(OverlayEnd);

	StartLocation=BaseMesh->GetComponentLocation();
	TargetLocation=StartLocation;

	ParticleSystem=ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Game/introduce/FXVarietyPack/Particles/P_ky_magicCircle1.P_ky_magicCircle1'")).Object;
	ParticleComp=CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));
	ParticleComp->SetupAttachment(BoxComp);
	ParticleComp->SetTemplate(ParticleSystem);
}

void ALounchCharacterProp::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AElCharacter *Character=Cast<AElCharacter>(OtherActor);
	if (Character&&bOverlap==false)
	{
		OverlapCharacter=Character;
		OverlapCharacter->BeginOverlapprop(this);
		bOverlap = true;
	}
}

void ALounchCharacterProp::OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AElCharacter *Character=Cast<AElCharacter>(OtherActor);
	if (Character)
	{
		OverlapCharacter->EndOverlapprop(this);
		OverlapCharacter=nullptr;
		bOverlap = false;
	}
	SetPropDoing(false);
}

void ALounchCharacterProp::Update(bool bProp, float Speed_Go, float Speed_Back, float DeltaTime)
{
	if (bProp)
	{
		if (MoveSpeed!=FVector(0.0f))
		{
			if (TargetLocation!=EndLocation)
			{
				TargetLocation+=MoveSpeed*Speed_Go;
				BaseMesh->SetRelativeLocation(TargetLocation);
			}
			
			LounchSize+=10;
			LounchSize=FMath::Clamp(LounchSize,100.0f,1000.0f);
		}	
	}else
	{
		TargetLocation=FMath::VInterpTo(TargetLocation,StartLocation,DeltaTime,Speed_Back);
		BaseMesh->SetRelativeLocation(TargetLocation);
	}
}

void ALounchCharacterProp::LounchCaracter()
{
	if (OverlapCharacter)
	{
		FVector Dirction = OverlapCharacter->GetActorForwardVector()+OverlapCharacter->GetActorUpVector();
		OverlapCharacter->LaunchCharacter(Dirction*LounchSize,false,false);
		LounchSize=1.0f;
	}
}

void ALounchCharacterProp::SetPropDoing(bool bDoSomething)
{
	bDoingProp=bDoSomething;
	if (bDoingProp==false)
	{
		LounchCaracter();
	}
}

// Called when the game starts or when spawned
void ALounchCharacterProp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALounchCharacterProp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Update(bDoingProp,UpdateSpeed_Go,UpdateSpeed_Back,DeltaTime);
}

