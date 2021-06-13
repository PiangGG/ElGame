// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SElGameCompleteWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/ElGameWidgetStyle.h"
#include "UI/Style/ElStyle.h"
#include "Widgets/Images/SImage.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SElGameCompleteWidget::Construct(const FArguments& InArgs)
{
	GameStyle=&ElStyle::Get().GetWidgetStyle<FElGameStyle>("BPElGameStyle");
	ChildSlot
	[
		// Populate the widget
		SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SImage)
			.Image(&GameStyle->GameBackgroundBrush)
		]
	];
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
