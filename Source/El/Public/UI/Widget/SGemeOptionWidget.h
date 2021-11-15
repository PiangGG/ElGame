// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Data/ElTypes.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class EL_API SGemeOptionWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGemeOptionWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void MenuButtonOnClicked(EMenuButtonType::Type ButtonType);
	private:
	//引入Sytle|获取GameStyle
	const struct FElGameStyle* GameStyle;
	TSharedPtr<class SUniformGridPanel> GameOptionGridPanel;
	TSharedPtr<class SButtonWidget> BackGameButton;
	TSharedPtr<class SButtonWidget> ReStartGameButton;
	TSharedPtr<class SButtonWidget> BackMainMenuButton;
	TSharedPtr<class SButtonWidget> QuiGameButton;
};
