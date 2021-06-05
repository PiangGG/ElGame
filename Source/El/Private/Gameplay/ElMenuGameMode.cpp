// Fill out your copyright notice in the Description page of Project Settings.


#include "ElMenuGameMode.h"

#include "ElMenuPlayerController.h"
#include "El/HUD/ElMenuHUD.h"

AElMenuGameMode::AElMenuGameMode()
{
	//设置游戏模式玩家控制器 
	PlayerControllerClass = AElMenuPlayerController::StaticClass();
	//HUD
	HUDClass=AElMenuHUD::StaticClass();
}
