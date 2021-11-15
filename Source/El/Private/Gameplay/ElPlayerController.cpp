// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/ElPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Common/ElHelper.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/TouchInterface.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/ElGameHUD.h"
#include "UI/Widget/SElGameHUDWidget.h"

void AElPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	//SAssignNew(GameHUDWidget, SElGameHUDWidget);
	
	//CurrentTouchInterface->set
	//ActivateTouchInterface(CurrentTouchInterface);
	GameHUDWidget=Cast<AElGameHUD>(GetHUD())->GameHUDWidget;
	GEngine->GameViewport->AddViewportWidgetForPlayer(GetLocalPlayer(),GameHUDWidget.ToSharedRef(),0);

	
}

AElPlayerController::AElPlayerController()
{
	bOpenOptionWidget=false;
	
	
}

void AElPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction("OpenOption", EInputEvent::IE_Pressed, this, &AElPlayerController::OpenOptionWidget);

}

void AElPlayerController::OpenOptionWidget()
{
	if (bOpenOptionWidget==false)
	{
		if (GameHUDWidget)
		{
			GameHUDWidget->GameState_Option();
		}
	}else
	{
		if (GameHUDWidget)
		{
			GameHUDWidget->GameState_None();
		}
	}
	bOpenOptionWidget=!bOpenOptionWidget;
	if (bOpenOptionWidget)
	{
		Cast<AElGameHUD>(GetHUD())->ShowGameHUDWidget();
		
	}else
	{
		Cast<AElGameHUD>(GetHUD())->HindGameHUDWidget();
	}
}
