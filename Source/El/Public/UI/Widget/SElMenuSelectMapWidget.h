// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Data/ElTypes.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class EL_API SElMenuSelectMapWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SElMenuSelectMapWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	void MenuButtonOnClicked(EMenuButtonType::Type type);
	void MenuSelectMapOnClicked(int id);
private:
	//引入Sytle|获取MenuStyle
	const struct FElMenuStyle* MenuStyle;
	
	TSharedPtr<class SUniformGridPanel> MapGridPanel;
	//返回主界面按鈕
	TSharedPtr<class SButtonWidget> BackMenuButton;
	
	TArray<TSharedPtr<class SElSelectMapItemWidget>>  WidgetArr;
	TSharedPtr<class SElSelectMapItemWidget>  Widget0;
};