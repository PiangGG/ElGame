// Fill out your copyright notice in the Description page of Project Settings.


#include "ElMenuHUD.h"

#include "Widget/SElMenuWidget.h"
#include "Widgets/SWeakWidget.h"
AElMenuHUD::AElMenuHUD()
{
	if (GEngine&&GEngine->GameViewport)
	{
		SAssignNew(MenuHUDWidget, SElMenuWidget);
		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MenuHUDWidget.ToSharedRef()));
	}
}
