// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SElUserInfoWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/ElGameWidgetStyle.h"
#include "UI/Style/ElStyle.h"
#include "Widgets/Notifications/SProgressBar.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SElUserInfoWidget::Construct(const FArguments& InArgs)
{
	GameStyle=&ElStyle::Get().GetWidgetStyle<FElGameStyle>("BPElGameStyle");
	
	ChildSlot
	[
		// Populate the widget
		SNew(SBox)
		.HeightOverride(40.0f)
		.WidthOverride(200.0f)
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(ProgressBar,SProgressBar)
				.Percent((float)InArgs._size.Get())
				.BackgroundImage(&GameStyle->ProbarBGBrush)
				.FillImage(&GameStyle->ProbarFillImageBrush)
				
			]
		]
	];
	
}

void SElUserInfoWidget::UpdateProgressBar(float num)
{
	if (ProgressBar&&num)
	{
		ProgressBar->SetPercent(num);
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
