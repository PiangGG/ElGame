// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ElController.h"
#include "ElPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class EL_API AElPlayerController : public AElController
{
	GENERATED_BODY()

	protected:
	virtual void BeginPlay() override;
public:
	AElPlayerController();

	virtual void SetupInputComponent() override;

	void OpenOptionWidget();

	bool bOpenOptionWidget;

	TSharedPtr<class SElGameHUDWidget> GameHUDWidget;

};
