// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/ElGMInGame.h"

#include "Gameplay/ElCharacter.h"
#include "Gameplay/ElPlayerController.h"
#include "UI/HUD/ElGameHUD.h"

AElGMInGame::AElGMInGame()
{
	HUDClass=AElGameHUD::StaticClass();
	PlayerControllerClass=AElPlayerController::StaticClass();
	//PlayerStateClass
	DefaultPawnClass=AElCharacter::StaticClass();
	
}

void AElGMInGame::BeginPlay()
{
	Super::BeginPlay();

	if ( GetWorld()->GetFirstPlayerController())
	{
		Cast<AElPlayerController>( GetWorld()->GetFirstPlayerController())->ChangeControllerState(EControllerState::GameOnly);
	}
}
