// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 * 
 */
class EL_API ElInternation
{
	
public:
	static void Register(FText value)
	{
		return;
	}
};
#define LOCTEXT_NAMESPACE "ElMenu"
ElInternation::Register(LOCTEXT("Menu","Menu"));
ElInternation::Register(LOCTEXT("GoBack","GoBack");
ElInternation::Register(LOCTEXT("StartGame","StartGame");
ElInternation::Register(LOCTEXT("MenuGameOption","MenuGameOption");
ElInternation::Register(LOCTEXT("GameOption","GameOption");
ElInternation::Register(LOCTEXT("QuitGame","QuitGame");
ElInternation::Register(LOCTEXT("SelecMap","SelecMap");
ElInternation::Register(LOCTEXT("GameComplate!","GameComplate!");
ElInternation::Register(LOCTEXT("GameOver!","GameOver!");
#undef LOCTEXT_NAMESPACE