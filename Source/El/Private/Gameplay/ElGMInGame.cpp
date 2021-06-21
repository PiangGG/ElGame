// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/ElGMInGame.h"

#include "Gameplay/ElCharacter.h"
#include "Gameplay/ElGI.h"
#include "Gameplay/ElPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/ElGameHUD.h"
#include "UI/Widget/SElGameHUDWidget.h"

AElGMInGame::AElGMInGame()
{
	//HUDClass=AElGameHUD::StaticClass();
	PlayerControllerClass=AElPlayerController::StaticClass();
	//PlayerStateClass
	DefaultPawnClass=AElCharacter::StaticClass();
}

void AElGMInGame::BeginPlay()
{
	Super::BeginPlay();

	CurrentGameState=EGameState::Playing;
	
	if ( GetWorld()->GetFirstPlayerController())
	{
		Cast<AElPlayerController>( GetWorld()->GetFirstPlayerController())->ChangeControllerState(EControllerState::GameOnly);
	}
}

void AElGMInGame::SetGameComplate()
{
	AElGameHUD *GameHUD= Cast<AElGameHUD>(UGameplayStatics::GetPlayerController(GWorld,0)->GetHUD());
	this->SetPause(UGameplayStatics::GetPlayerController(GWorld,0));
	if (GameHUD)
	{
		GameHUD->GameHUDWidget->ChangeGameHUDState(EGameHUDState::Complete);
	}
}

void AElGMInGame::ReStartGame()
{
	int CurrentMapID=Cast<UElGI>(UGameplayStatics::GetGameInstance(GWorld))->GetCurrentMapID();
	
	UGameplayStatics::OpenLevel(GWorld,FName("Map"+FString::FromInt(CurrentMapID)));
}
