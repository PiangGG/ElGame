// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/ElController.h"

#include "Common/ElHelper.h"

AElController::AElController()
{
	CurrControllerState=EControllerState::UIOnly;
}

void AElController::ChangeControllerState(EControllerState::Type type)
{
	//if (CurrControllerState==type)return;
	switch (type)
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
	CurrControllerState=type;
}
void AElController::GameOnlyState()
{
	this->SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly());
	return;
}

void AElController::UIOnlyState()
{
	this->SetShowMouseCursor(true);
	SetInputMode(FInputModeUIOnly());
	return;
}

void AElController::GameAndUIState()
{
	this->SetShowMouseCursor(true);
	SetInputMode(FInputModeGameAndUI());
	return;
}