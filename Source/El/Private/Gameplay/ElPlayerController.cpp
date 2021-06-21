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
	
	SAssignNew(GameHUDWidget, SElGameHUDWidget);
	GetWorld()->GetGameViewport()->AddViewportWidgetContent(GameHUDWidget.ToSharedRef());
	GameHUDWidget->SetVisibility(EVisibility::Hidden);
	CurrentTouchInterface->Activate(VirtualJoystick);
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
	/*if (bOpenOptionWidget==false)
	{
		AElGameHUD *GameHUD = Cast<AElGameHUD>(GetHUD());
		if (GameHUD)
		{
			GameHUD->GameHUDWidget->GameState_Option();
		}
	}else
	{
		AElGameHUD *GameHUD = Cast<AElGameHUD>(GetHUD());
		if (GameHUD)
		{
			GameHUD->GameHUDWidget->GameState_None();
		}
	}*/
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
		GameHUDWidget->SetVisibility(EVisibility::Visible);
	}else
	{
		GameHUDWidget->SetVisibility(EVisibility::Hidden);	
	}
}
