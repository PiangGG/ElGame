// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Style/ElStyle.h"
#include "Slate/SlateGameResources.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr<FSlateStyleSet> ElStyle::ElStyleInstance = NULL;

void ElStyle::Initialze()
{
	if (!ElStyleInstance.IsValid())
	{
		ElStyleInstance = Create();
		//注册进注册表
		FSlateStyleRegistry::RegisterSlateStyle(*ElStyleInstance);
	}
}

FName ElStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("ElStyle"));
	return StyleSetName;
	
}

void ElStyle::ShutDown()
{
	//游戏关闭时调用
	FSlateStyleRegistry::UnRegisterSlateStyle(*ElStyleInstance);
	//确保唯一
	ensure(ElStyleInstance.IsUnique());
	ElStyleInstance.Reset();
}

const ISlateStyle& ElStyle::Get()
{
	if (!ElStyleInstance)
	{
		Initialze();
	}
	return *ElStyleInstance;
}

TSharedRef<class FSlateStyleSet> ElStyle::Create()
{
	//"/Game/UI/Style"|在content路径下的Style文件
	TSharedRef<FSlateStyleSet> StyleRef  = FSlateGameResources::New(ElStyle::GetStyleSetName(),"/Game/UI/Style","/Game/UI/Style");

	return StyleRef;
}
