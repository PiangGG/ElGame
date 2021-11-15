// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ElMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class EL_API AElMenuHUD : public AHUD
{
	GENERATED_BODY()
	public:
	
	AElMenuHUD();
	
	TSharedPtr<class SElMenuHUDWidget> MenuHUDWidget;
};
