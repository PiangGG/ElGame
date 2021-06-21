// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/ElCharacter.h"

#include "Camera/CameraComponent.h"
#include "Common/ElHelper.h"
#include "Component/BatteryComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Prop/Baseprop.h"
#include "UI/HUD/ElGameHUD.h"
#include "UI/Widget/SElGameHUDWidget.h"
#include "UI/Widget/SElUserInfoWidget.h"

// Sets default values
AElCharacter::AElCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> theMesh(TEXT("SkeletalMesh'/Game/Import/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstance(TEXT("AnimBlueprint'/Game/Blueprints/Animation/ElCharacterAnimInstanceBP.ElCharacterAnimInstanceBP_C'"));
	
	GetMesh()->SetSkeletalMesh(theMesh.Object);
	GetMesh()->SetRelativeLocation(FVector(0.0f,0.0f,-90.0f));
	GetMesh()->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.0f,0.0f,-90.0f)));
	GetMesh()->SetAnimClass(AnimInstance.Class);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("Camera Boom"));
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->TargetArmLength = 700.f;
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bEnableCameraLag =true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->FieldOfView = 110.f;
	
	Camera->SetupAttachment(SpringArm);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.8f;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch=true;
	GetCharacterMovement()->MaxWalkSpeedCrouched =GetCharacterMovement()->MaxWalkSpeed*0.2;

	//ElComponent
	BatteryComp=CreateDefaultSubobject<UBatteryComponent>(TEXT("BatteryComp"));
	BatteryComp->SetSize(100.0f);
	BatteryComp->SetCanUpdate(false,1.0f);

	bUsePower = false;

	ParticleSystem=ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Game/Res/Particle/PS_LightningStrike_Constant.PS_LightningStrike_Constant'")).Object;
	ParticleComp=CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));
	ParticleComp->SetupAttachment(GetMesh(),FName("Hand_r"));
	
	ParticleComp->SetTemplate(ParticleSystem);
	ParticleComp->Deactivate();
}

// Called when the game starts or when spawned
void AElCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

void AElCharacter::OverlapBaseprop(ABaseprop* prop)
{
	if (bOverlapBaseprop==false)
	{
		CurrenOverlapBaseprop=prop;
		bOverlapBaseprop=true;
	}else
	{
		CurrenOverlapBaseprop=nullptr;
		bOverlapBaseprop=false;
	}
}

void AElCharacter::GameOver()
{
	GameHUDWidget=Cast<AElGameHUD>(UGameplayStatics::GetPlayerController(GWorld,0)->GetHUD())->GameHUDWidget;
	if (GameHUDWidget)
	{
		GameHUDWidget->ChangeGameHUDState(EGameHUDState::Over);
	}
}

// Called every frame
void AElCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (CurrenOverlapBaseprop&&bUsePower==true)
	{
		
		BatteryComp->SetCanUpdate(true,-5.0f);
		ParticleComp->Activate();
		ParticleComp->SetVectorParameter(FName("Target"),CurrenOverlapBaseprop->GetActorLocation());
	}else
	{
		BatteryComp->SetCanUpdate(false,-5.0f);
		ParticleComp->Deactivate();
	}
}

// Called to bind functionality to input
void AElCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Crouch", EInputEvent::IE_Pressed, this, &AElCharacter::CrouchEl);
	InputComponent->BindAction("Crouch", EInputEvent::IE_Released, this, &AElCharacter::UnCrouchEl);

	InputComponent->BindAction("Power", EInputEvent::IE_Pressed, this, &AElCharacter::OutPower);
	InputComponent->BindAction("Power", EInputEvent::IE_Released, this, &AElCharacter::InPower);

	InputComponent->BindAxis("ChangeCameraHeight", this, &AElCharacter::ChangeCameraHeight);
	InputComponent->BindAxis("RotateCamera", this, &AElCharacter::RotateCamera);
	InputComponent->BindAxis("MoveForward", this, &AElCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AElCharacter::MoveRight);
}

void AElCharacter::MoveForward(float amount)
{
	if (Controller && amount) {
		AddMovementInput(SpringArm->GetForwardVector(), amount);
	}
}

void AElCharacter::MoveRight(float amount)
{
	if (Controller && amount) {
		AddMovementInput(SpringArm->GetRightVector(), amount);
	}
}

void AElCharacter::RotateCamera(float amount)
{
	if (Controller && amount) {
		FVector rot = SpringArm->GetComponentRotation().Euler();
		rot += FVector(0, 0, amount);
		SpringArm->SetWorldRotation(FQuat::MakeFromEuler(rot));
	}
}

void AElCharacter::ChangeCameraHeight(float amount)
{
	if (Controller && amount) {
		FVector rot = SpringArm->GetComponentRotation().Euler();

		float originalHeight = rot.Y;
		originalHeight += amount;
		originalHeight = FMath::Clamp(originalHeight, -45.f, -5.f);

		rot = FVector(0, originalHeight, rot.Z);
		SpringArm->SetWorldRotation(FQuat::MakeFromEuler(rot));
	}
}
void AElCharacter::CrouchEl()
{
	ElHelper::Debug(FString("CrouchEl"));
	Crouch();
}

void AElCharacter::UnCrouchEl()
{
	ElHelper::Debug(FString("UnCrouchEl"));
	UnCrouch();
}

void AElCharacter::InPower()
{
	//角色充电
	if (CurrenOverlapBaseprop&&bUsePower==true)
	{
		//ElHelper::Debug(FString("AElCharacter::InPower()"));
		CurrenOverlapBaseprop->OutPower(-10.0);
		bUsePower = false;
		
	}

}

void AElCharacter::OutPower()
{
	//角色消电
	if (CurrenOverlapBaseprop&&bUsePower==false)
	{
		//ElHelper::Debug(FString("AElCharacter::OutPower()"));
		CurrenOverlapBaseprop->InPower(10.0);
		bUsePower = true;
		
	}
}

FVector AElCharacter::GetCameraLocation()
{
	return Camera->GetComponentLocation();
}
