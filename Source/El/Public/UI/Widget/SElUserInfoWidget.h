// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"


/**
 * 
 */
class EL_API SElUserInfoWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SElUserInfoWidget)
	{}
	SLATE_ATTRIBUTE(float,size)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	void UpdateProgressBar(float num);
private:
	//引入Sytle|获取GameStyle
	const struct FElGameStyle* GameStyle;
	TSharedPtr<class SProgressBar> ProgressBar;//电量
	float size;
};
