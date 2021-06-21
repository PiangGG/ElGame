// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/ElCharacterAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Gameplay/ElCharacter.h"

UElCharacterAnimInstance::UElCharacterAnimInstance()
{
	IsFail = false;
	IsCrouch= false;
	IsUsePower=false;
	Speed = 0.0f;
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
