// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/ElController.h"

#include "Common/ElHelper.h"

AElController::AElController()
{
	CurrControllerState=EControllerState::UIOnly;
}

void AElController::ChangeControllerState(EControllerState::Type newtype)
{
	/*if (CurrControllerState==newtype)return;
	CurrControllerState=newtype;*/
	switch (newtype)
	{
	case EControllerState::GameOnly:
		GameOnlyState();
		break;
	case EControllerState::UIOnly:
		UIOnlyState();
		break;
	case EControllerState::GameAndUI:
		GameAndUIState();
		break;
	default: break;
	}
}
void AElController::GameOnlyState()
{
	if (GWorld&&GWorld->GetFirstPlayerController())
	{
		GWorld->GetFirstPlayerController()->SetShowMouseCursor(false);
		GWorld->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	}
	return;
}

void AElController::UIOnlyState()
{
	GWorld->GetFirstPlayerController()->SetShowMouseCursor(true);
	GWorld->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	return;
}

void AElController::GameAndUIState()
{
	GWorld->GetFirstPlayerController()->SetShowMouseCursor(true);
	SetInputMode(FInputModeGameAndUI());
	return;
}