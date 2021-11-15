// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 注册样式的全局类
 */
class EL_API ElStyle
{
public:
	//项目开始调用|El.h中
	static void Initialze();

	static FName GetStyleSetName();

	static void ShutDown();
	//外部调用|实现单例
	static const ISlateStyle&Get();
private:
	static TSharedRef<class FSlateStyleSet>Create();
	
	static TSharedPtr<class FSlateStyleSet> ElStyleInstance;
};
