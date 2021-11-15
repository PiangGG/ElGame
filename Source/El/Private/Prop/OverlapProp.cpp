// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/OverlapProp.h"

#include "Common/ElHelper.h"
#include "Components/BoxComponent.h"
#include "Gameplay/ElCharacter.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AOverlapProp::AOverlapProp()
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
	//BoxComp->SetupAttachment(RootComp);
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
	
	StartRotator=BaseMesh->GetComponentRotation();
	TargetRotator=StartRotator;

	StartScale3D=GetActorScale3D();
	TargetScale3D=StartScale3D;

	ParticleSystem=ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Game/introduce/FXVarietyPack/Particles/P_ky_healAura.P_ky_healAura'")).Object;
	ParticleComp=CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));
	ParticleComp->SetupAttachment(BoxComp);
	ParticleComp->SetTemplate(ParticleSystem);
}

// Called when the game starts or when spawned
void AOverlapProp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOverlapProp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Update(bDoingProp,UpdateSpeed_Go,UpdateSpeed_Back,DeltaTime);
}

void AOverlapProp::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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

void AOverlapProp::OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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
void AOverlapProp::Update(bool bProp,float Speed_Go,float Speed_Back,float DeltaSeconds)
{
	if (bProp)
	{
		if (RotatorSpeed!=FRotator(0.0f))
		{
			TargetRotator+=RotatorSpeed*Speed_Go;
			BaseMesh->SetRelativeRotation(TargetRotator);
		}

		if (MoveSpeed!=FVector(0.0f))
		{
			TargetLocation+=MoveSpeed*Speed_Go;
			BaseMesh->SetRelativeLocation(TargetLocation);
		}
		if (MoveScale3D!=FVector(0.0f))
		{
			TargetScale3D+=MoveScale3D*Speed_Go;
			SetActorScale3D(TargetScale3D);
		}	
	}else
	{
		if (TargetRotator!=StartRotator)
		{
			TargetRotator=FMath::RInterpTo(TargetRotator,StartRotator,DeltaSeconds,Speed_Back);
			BaseMesh->SetRelativeRotation(TargetRotator);
		}

		if (TargetLocation!=StartLocation)
		{
			TargetLocation=FMath::VInterpTo(TargetLocation,StartLocation,DeltaSeconds,Speed_Back);
			BaseMesh->SetRelativeLocation(TargetLocation);
		}
		if (TargetScale3D!=StartScale3D)
		{
			TargetScale3D=FMath::VInterpTo(TargetScale3D,StartScale3D,DeltaSeconds,Speed_Back);
			SetActorScale3D(TargetScale3D);
		}
	}	
}

void AOverlapProp::SetPropDoing(bool bDoSomething)
{
	bDoingProp=bDoSomething;
}