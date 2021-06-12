// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

public:
	TSharedPtr<class SElUserInfoWidget> ElUserInfoWidget;
private:
	//引入Sytle|获取GameStyle
	const struct FElGameStyle* GameStyle;
};
