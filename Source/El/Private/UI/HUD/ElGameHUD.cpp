// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/ElGameHUD.h"

#include "Component/BatteryComponent.h"
#include "Gameplay/ElCharacter.h"
#include "UI/Widget/SElGameHUDWidget.h"
#include "UI/Widget/SElUserInfoWidget.h"

AElGameHUD::AElGameHUD()
{
	if (GWorld&&GWorld->GetFirstPlayerController())
	{
		SAssignNew(GameHUDWidget, SElGameHUDWidget);
		
		GWorld->GetGameViewport()->AddViewportWidgetContent(GameHUDWidget.ToSharedRef());
		//UE_LOG(LogTemp,Warning,TEXT("InitAElMenuHUD"));
	}
}

void AElGameHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (Character)
	{
		GameHUDWidget->ElUserInfoWidget->UpdateProgressBar(Character->BatteryComp->GetRatio());
	}
}

void AElGameHUD::BeginPlay()
{
	Super::BeginPlay();
	Character=Cast<AElCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}
