// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Data/ElTypes.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class EL_API SElMenuHUDWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SElMenuHUDWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	void ChangeGameMenuState(EGameMainState::Type newState);

	void MenuButtonOnClicked(EMenuButtonType::Type Button);

	/*
	 * 按鈕函數
	 */
	void MenuButtonOnClicked_StartGame();
	void MenuButtonOnClicked_GameSetting();
	void MenuButtonOnClicked_QuitGame();
	void MenuButtonOnClicked_BackMainMenu();
private:
	//绑定UIScaler的函数
	float GetUIScaler()const;
	//获取屏幕尺寸
	FVector2D GetViewportSize()const;
private:
	//引入Sytle|获取MenuStyle
	const struct FElMenuStyle* MenuStyle;

	//屏幕dpi适配
	TAttribute<float> UIScaler;
	//菜单指针
	TSharedPtr<class SElMenuMainWidget> MenuWidget;
	//設置指針
	TSharedPtr<class SElMenuSettingWidget> SettingWidget;
	//选择地图
	TSharedPtr<class SElMenuSelectMapWidget> SelectMapWidget;

	EGameMainState::Type CurreGameMainState;
};
