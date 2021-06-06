// Copyright Epic Games, Inc. All Rights Reserved.

#include "El.h"
#include "Modules/ModuleManager.h"
#include "Styling/SlateStyleRegistry.h"
#include "UI/Style/ElStyle.h"


void FElModule::StartupModule()
{
	//初始化样式ElStyle|先卸载再加载(防止没卸载就加载报错)
	FSlateStyleRegistry::UnRegisterSlateStyle(ElStyle::GetStyleSetName());
	//实例化
	ElStyle::Initialze();
}

void FElModule::ShutdownModule()
{
	ElStyle::ShutDown();
}
IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, El, "El");
