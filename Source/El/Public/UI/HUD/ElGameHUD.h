// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ElGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class EL_API AElGameHUD : public AHUD
{
	GENERATED_BODY()

	public:
	
	AElGameHUD();
	TSharedPtr<class SElGameHUDWidget> GameHUDWidget;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	class AElCharacter *Character;

	public:
	void ShowGameHUDWidget();
	void HindGameHUDWidget();
};
