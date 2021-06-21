// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Data/ElTypes.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class EL_API SElGameHUDWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SElGameHUDWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	
	void GameButtonOnClicked(EMenuButtonType::Type ButtonType);

	void ChangeGameHUDState(EGameHUDState::Type GameHUDState);

	void GameState_None();
	
	void GameState_Option();

	void GameState_Complete();

	void GameState_Over();
	
	void GameOption_OnClick();
	
	void BackGame_OnClick();
	
	void ReStartGame_OnClick();
	
	void BackMainMenu_OnClick();

	void QuiGame_OnClick();
	
	void NextMap_OnClick();

public:
	TSharedPtr<class SElUserInfoWidget> ElUserInfoWidget;
	
	TSharedPtr<class SBox> RootBox;

	TSharedPtr<class SButtonWidget> OptionButton;
	
	TSharedPtr<class SGemeOptionWidget> GemeOptionWidget;
	
	TSharedPtr<class SElGameCompleteWidget> GemeCompleteWidget;
	
	TSharedPtr<class SElGameOverWidget> GemeOverWidget;
private:
	//引入Sytle|获取GameStyle
	const struct FElGameStyle* GameStyle;

	EGameHUDState::Type CurrenGameHUDState=EGameHUDState::None;

	EVisibility bOptionVisibility=EVisibility::Visible;
};

