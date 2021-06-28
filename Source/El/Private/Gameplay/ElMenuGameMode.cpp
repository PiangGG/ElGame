// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/ElMenuGameMode.h"

#include "Common/ElHelper.h"
#include "Gameplay/ElMenuPlayerController.h"
#include "UI/HUD/ElMenuHUD.h"

AElMenuGameMode::AElMenuGameMode()
{
	//设置游戏模式玩家控制器 
	PlayerControllerClass = AElMenuPlayerController::StaticClass();
	//HUD
	HUDClass=AElMenuHUD::StaticClass();
}

void AElMenuGameMode::BeginPlay()
{
	if (Cast<AElMenuPlayerController>( GetWorld()->GetFirstPlayerController()))
	{
		Cast<AElMenuPlayerController>( GetWorld()->GetFirstPlayerController())->ChangeControllerState(EControllerState::UIOnly);
	}
}
