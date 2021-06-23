// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SElUserInfoWidget.h"
#include "SlateOptMacros.h"
#include "Common/ElHelper.h"
#include "Gameplay/ElCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Style/ElGameWidgetStyle.h"
#include "UI/Style/ElStyle.h"
#include "UI/Widget/SButtonWidget.h"
#include "UI/Widget/SDragMoveButtonWidget.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Notifications/SProgressBar.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SElUserInfoWidget::Construct(const FArguments& InArgs)
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
			.Padding(FMargin(0.0f,0.0f,0.0f,0.0f))
			[
				SNew(SBox)
				.WidthOverride(400.0f)
				.HeightOverride(40.0f)
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
					+SOverlay::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					[
						SNew(SImage)
						.Image(&GameStyle->GameBackgroundBrush)
					]
				]	
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Bottom)
			.Padding(FMargin(0.0f,0.0f,100.0f,100.0f))
			[
				SAssignNew(PowerButton,SButton)
				.ButtonStyle(&GameStyle->PowerButtonStyle)
				.OnPressed(this,&SElUserInfoWidget::PowerButtonOnOnPressed)
				.OnReleased(this,&SElUserInfoWidget::PowerButtonOnOnOnReleased)
				
			]
			/*+SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Bottom)
			.Padding(FMargin(160.0f,0.0f,100.0f,90.0f))
			[
				SNew(SOverlay)
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SAssignNew(DragMoveButton,SDragMoveButtonWidget)
				]
				
			]*/
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

void SElUserInfoWidget::PowerButtonOnOnPressed()
{
	Cast<AElCharacter>(UGameplayStatics::GetPlayerCharacter(GWorld,0))->OutPower();
}
void SElUserInfoWidget::PowerButtonOnOnOnReleased()
{
	Cast<AElCharacter>(UGameplayStatics::GetPlayerCharacter(GWorld,0))->InPower();
}

FReply SElUserInfoWidget::OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{
	OnDragDetected(MyGeometry,DragDropEvent);
	ElHelper::Debug(FString("OnDragDetected(MyGeometry,DragDropEvent);"));
	
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
