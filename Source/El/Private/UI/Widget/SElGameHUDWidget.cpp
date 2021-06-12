// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SElGameHUDWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/ElGameWidgetStyle.h"
#include "UI/Style/ElStyle.h"
#include "UI/Widget/SElUserInfoWidget.h"
#include "Widgets/Images/SImage.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SElGameHUDWidget::Construct(const FArguments& InArgs)
{
	GameStyle=&ElStyle::Get().GetWidgetStyle<FElGameStyle>("BPElGameStyle");
	
	ChildSlot
	[
		// Populate the widget
		SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Bottom)
			.Padding(FMargin(0.0f,0.0f,0.0f,200.0f))
			[
				SAssignNew(ElUserInfoWidget,SElUserInfoWidget)
			]
		]
		
	];
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
