// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Rotateprop/Baseprop.h"

#include "Common/ElHelper.h"
#include "Component/BatteryComponent.h"
#include "Components/BoxComponent.h"
#include "Gameplay/ElCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Prop/Rotateprop/PropWidgetComponent.h"
#include "UI/Widget/SElUserInfoWidget.h"

// Sets default values
ABaseprop::ABaseprop()
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

	BatteryComp=CreateDefaultSubobject<UBatteryComponent>(TEXT("BatteryComp"));
	BatteryComp->SetSize(0.0f);
	BatteryComp->SetCanUpdate(false,-1.0f);
	bUsePower=false;
	bDosomething = false;
	
	WidgetComp=CreateDefaultSubobject<UPropWidgetComponent>(TEXT("WidgetComp"));
	WidgetComp->SetupAttachment(RootComponent);
	WidgetComp->SetVisibility(false);

	//粒子
	ParticleSystem=ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Game/Res/Particle/PS_Arcs_Omni_Area_Loop.PS_Arcs_Omni_Area_Loop'")).Object;
	ParticleComp=CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));
	ParticleComp->SetupAttachment(RootComp);
	//ParticleComp->SetTemplate(ParticleSystem);
	ParticleComp->Deactivate();
}

// Called when the game starts or when spawned
void ABaseprop::BeginPlay()
{
	Super::BeginPlay();
	BoxComp->SetGenerateOverlapEvents(true);


	//设置血条widget
	SAssignNew(InfoWidget, SElUserInfoWidget).size(BatteryComp->GetRatio());
	WidgetComp->SetSlateWidget(InfoWidget);
	WidgetComp->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	WidgetComp->SetDrawSize(FVector2D(100.f, 10.f));

	ParticleComp->Deactivate();
}

void ABaseprop::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//ElHelper::Debug(FString("OnOverlayBegin"));
	AElCharacter *Character=Cast<AElCharacter>(OtherActor);
	if (Character)
	{
		OverlapCharacter=Character;
		bOverlap = true;
		WidgetComp->SetVisibility(true);
		Character->OverlapBaseprop(this);
	}
}

void ABaseprop::OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//ElHelper::Debug(FString("OnOverlayEnd"));
	AElCharacter *Character=Cast<AElCharacter>(OtherActor);
	if (Character)
	{
		OverlapCharacter=nullptr;
		bOverlap = false;
		WidgetComp->SetVisibility(false);
		Character->OverlapBaseprop(this);	
	}
	bInPower=false;
	BatteryComp->SetCanUpdate(false,1.0f);
	bDosomething=true;
}

void ABaseprop::UpdateInfoWidget(FVector Loaction)
{
	//旋转
	FVector StartPos(GetActorLocation().X, GetActorLocation().Y, 0);
	FVector TargetPos(Loaction.X, Loaction.Y, 0.f);
	WidgetComp->SetWorldRotation(FRotationMatrix::MakeFromX(TargetPos - StartPos).Rotator());
	WidgetComp->SetWorldLocation(OverlapCharacter->GetActorLocation()+FVector(0.0f,0.0f,100.0f));
	WidgetComp->SetRelativeScale3D(FVector(1.f));
	if (InfoWidget&&BatteryComp)
	{
		InfoWidget->UpdateProgressBar(BatteryComp->GetRatio());
	}
}

void ABaseprop::DoSomethingStart()
{
	if (bDosomething==false)
	{
		bDosomething=true;
	}
	if (bDosomething)
	{
		BatteryComp->SetCanUpdate(bDosomething,-5.0);
		ParticleComp->Activate();
	}

}

void ABaseprop::DoSomethingEnd()
{
	if (bDosomething==true)
	{
		bDosomething=false;
	}
	if (bDosomething==false)
	{
		BatteryComp->SetCanUpdate(bDosomething,-5.0);
		ParticleComp->Deactivate();
	}
}

void ABaseprop::DoSomethinging(float speed)
{
	//this->SetActorScale3D(ActorScale3D+=FVector(speed*0.001));
}

void ABaseprop::InPower(float Speed)
{
	if (BatteryComp->GetRatio()<1.0f)
	{
		bInPower=true;
		BatteryComp->SetCanUpdate(true,Speed*5.0f);
	}
}

void ABaseprop::OutPower(float Speed)
{
	if (BatteryComp->GetRatio()>0.0f)
	{
		bInPower=false;
		BatteryComp->SetCanUpdate(false,Speed);
	}
}

// Called every frame
void ABaseprop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bOverlap&&OverlapCharacter)
	{
		UpdateInfoWidget(OverlapCharacter->GetCameraLocation());
	}
	if (bInPower==false)
	{
		if (BatteryComp->GetSize()>0.0f)
		{
			DoSomethingStart();
			ParticleSystemActive=true;
			
		}else
		{
			DoSomethingEnd();
			ParticleSystemActive=false;
		}
	}
	if (bDosomething)
	{
		DoSomethinging(1.0f);	
	}
}

