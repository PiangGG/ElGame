// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/AutomaticProp.h"

#include "Components/BoxComponent.h"

// Sets default values
AAutomaticProp::AAutomaticProp()
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
	
	bDosomething=true;

	StartRotator=BaseMesh->GetComponentRotation();
	TargetRotator=StartRotator;

	StartLocation=BaseMesh->GetComponentLocation();
	TargetLocation=StartLocation;

	StartScale3D=GetActorScale3D();
	TargetScale3D=StartScale3D;

	CurrentState=EAutomaticPropState::To;
}

// Called when the game starts or when spawned
void AAutomaticProp::BeginPlay()
{
	Super::BeginPlay();

	//设置变换往返定时器
	GetWorldTimerManager().SetTimer(TransfomTimeTimerHandle, this, &AAutomaticProp::ChangeGoOrBack, TransfomTime, true);
}

void AAutomaticProp::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void AAutomaticProp::OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

// Called every frame
void AAutomaticProp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Update(bDosomething,DeltaTime);
}

void AAutomaticProp::Update(const bool &Dosomething,float DeltaSeconds)
{
	if (Dosomething)
	{
		switch (CurrentState)
		{
		case EAutomaticPropState::To:
			Update_Go(DeltaSeconds);
			break;
		case EAutomaticPropState::Back:
			Update_Back(DeltaSeconds);
			break;
		default: ;
		}
	}
}

void AAutomaticProp::Update_Go(float DeltaSeconds)
{
	TargetRotator=FMath::RInterpTo(TargetRotator,EndRotator,DeltaSeconds,RotatorSpeed);
	BaseMesh->SetRelativeRotation(TargetRotator);

	TargetLocation=FMath::VInterpTo(TargetLocation,EndLocation,DeltaSeconds,MoveSpeed);
	BaseMesh->SetRelativeLocation(TargetLocation);

	TargetScale3D=FMath::VInterpTo(TargetScale3D,EndScale3D,DeltaSeconds,ScaleSpeed);
	SetActorScale3D(TargetScale3D);
}

void AAutomaticProp::Update_Back(float DeltaSeconds)
{
	TargetRotator=FMath::RInterpTo(TargetRotator,StartRotator,DeltaSeconds,RotatorSpeed);
	BaseMesh->SetRelativeRotation(TargetRotator);

	TargetLocation=FMath::VInterpTo(TargetLocation,StartLocation,DeltaSeconds,MoveSpeed);
	BaseMesh->SetRelativeLocation(TargetLocation);

	TargetScale3D=FMath::VInterpTo(TargetScale3D,StartScale3D,DeltaSeconds,ScaleSpeed);
	SetActorScale3D(TargetScale3D);
}

void AAutomaticProp::ChangeGoOrBack()
{
	if (CurrentState==EAutomaticPropState::To)
	{
		CurrentState=EAutomaticPropState::Back;
		return;
	}else if (CurrentState==EAutomaticPropState::Back)
	{
		CurrentState=EAutomaticPropState::To;
		return;
	}
}