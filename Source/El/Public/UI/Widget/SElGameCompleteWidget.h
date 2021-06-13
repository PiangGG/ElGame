// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class EL_API SElGameCompleteWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SElGameCompleteWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	//引入Sytle|获取GameStyle
	const struct FElGameStyle* GameStyle;
};
