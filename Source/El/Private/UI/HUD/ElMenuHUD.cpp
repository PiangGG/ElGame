// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/ElMenuHUD.h"

#include "UI/Widget/SElMenuHUDWidget.h"
#include "Widgets/SWeakWidget.h"
AElMenuHUD::AElMenuHUD()
{
	if (GEngine&&GEngine->GameViewport)
	{
		SAssignNew(MenuHUDWidget, SElMenuHUDWidget);
		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MenuHUDWidget));
		//UE_LOG(LogTemp,Warning,TEXT("InitAElMenuHUD"));
	}
}
