// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ElTypes.h"

/**
 * 
 */
class EL_API ElDataHandle
{
public:
	ElDataHandle();
	static void Initialize();
	static TSharedPtr<ElDataHandle> Get();
	//修改中英文
	void ChangeLocalizationCulture(ELanguage Language);
	//游戏基础设置初始化
	void InitializeGameSetting();
	//游戏基础设置更新
	void UpdateGameSetting();
	//字符串語言枚舉
	ELanguage FStirngToELanguage(FString &string);
public:
	//语言
	ELanguage CurrentLanguage;

	TArray<FString> Languages;
	
	
private:
	static TSharedPtr<ElDataHandle> Create();
private:
	//获取MenuStyle
	//const struct FElMenuStyle *MenuStyle;
	//获取GameStyle
	//const struct FElGameStyle *GameStyle;
	//定義單例
	static TSharedPtr<ElDataHandle> DataInstance;

	FString GameSetConfigfile;
};
