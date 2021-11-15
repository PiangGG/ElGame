// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/ElCharacterAnimInstance.h"

#include "Common/ElHelper.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gameplay/ElCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

UElCharacterAnimInstance::UElCharacterAnimInstance()
{
	IsFail = false;
	IsCrouch= false;
	IsUsePower=false;
	Speed = 0.0f;
	
	ConstructorHelpers::FObjectFinder<USoundCue>HitSound(TEXT("SoundCue'/Game/introduce/FootstepSound/Sounds/WaveFiles/Footsteps_Mono/Female/Plastic/PlasticHeels_1_Cue.PlasticHeels_1_Cue'"));
	Sound1=HitSound.Object;
	
	
}

void UElCharacterAnimInstance::NativeBeginPlay()
{
	if (!ElCharacter)ElCharacter=Cast<AElCharacter>(TryGetPawnOwner());
}

void UElCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	UpdateParameter();
}

void UElCharacterAnimInstance::UpdateParameter()
{
	if (ElCharacter)
	{
		Speed = ElCharacter->GetVelocity().Size();
		IsFail= ElCharacter->GetCharacterMovement()->IsFalling();
		IsCrouch=ElCharacter->GetCharacterMovement()->IsCrouching();
		IsUsePower=ElCharacter->bUsePower;
	}
}

void UElCharacterAnimInstance::PlayerSoundFoot()
{
	//USoundCue* HitSound = LoadObject<USoundCue>(this, TEXT("SoundCue'/Game/introduce/FootstepSound/Sounds/WaveFiles/Footsteps_Mono/Female/Plastic/PlasticHeels_1_Cue.PlasticHeels_1_Cue'"));
	if (Sound1)
		UGameplayStatics::SpawnSoundAttached(Sound1,ElCharacter->GetMesh(),FName("foot_root"));
}
