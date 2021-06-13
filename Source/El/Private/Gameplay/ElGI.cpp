// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/ElGI.h"

UElGI::UElGI()
{
	
}

int UElGI::GetCurrentMapID()
{
	return CurrentMapID;
}

void UElGI::SetCurrentMapID(int ID)
{
	CurrentMapID=ID;
}
