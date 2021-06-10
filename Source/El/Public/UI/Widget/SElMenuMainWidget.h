// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SButtonWidget.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class EL_API SElMenuMainWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SElMenuMainWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//引入Sytle|获取MenuStyle
	const struct FElMenuStyle* MenuStyle;

	TArray<SButtonWidget> SButtonArr;

	void MenuButtonOnClicked(EMenuButtonType::Type ButtonType);
private:
	void InitMenu();
private:
	TSharedPtr<SButtonWidget> StartGameButton;
	TSharedPtr<SButtonWidget> SeletMapButton;
	TSharedPtr<SButtonWidget> QuitGameMapButton;
	//垂直框|用来保存垂直列表
	TSharedPtr<SVerticalBox>ContentBox;
	
};
