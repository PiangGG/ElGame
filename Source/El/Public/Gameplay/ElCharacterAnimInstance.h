// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ElCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class EL_API UElCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	
	UElCharacterAnimInstance();

	virtual void NativeBeginPlay() override;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void UpdateParameter();

	//播放蒙太奇
	//PlayMotage
public:

	UPROPERTY(BlueprintReadWrite,Category=AnimaCharactre)
	float Speed;
	UPROPERTY(BlueprintReadWrite,Category=AnimaCharactre)
	bool IsFail;
	UPROPERTY(BlueprintReadWrite,Category=AnimaCharactre)
	bool IsCrouch;
	UPROPERTY(BlueprintReadWrite,Category=AnimaCharactre)
	class AElCharacter *ElCharacter;
	
};
