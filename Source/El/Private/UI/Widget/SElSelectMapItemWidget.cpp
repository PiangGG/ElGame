// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widget/SElSelectMapItemWidget.h"
#include "SlateOptMacros.h"
#include "Common/ElHelper.h"
#include "UI/Style/ElMenuWidgetStyle.h"
#include "UI/Style/ElStyle.h"
#include "Widgets/Images/SImage.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SElSelectMapItemWidget::Construct(const FArguments& InArgs)
{

	MapWidgetClicked=InArgs._MapWidgetClicked;
	MapId=InArgs._MapId.Get();
	//Init(InArgs._MapText.Get());

	MenuStyle = &ElStyle::Get().GetWidgetStyle<FElMenuStyle>("BPElMenuStyle");
	ChildSlot
	[
		// Populate the widget
		SNew(SBox)
		.WidthOverride(150)
		.HeightOverride(150)
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(MapImage,SImage)
				.Image(&MenuStyle->MapBg)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Bottom)
			[
				SAssignNew(MapText,STextBlock)
				//.Font()
				.Text(InArgs._MapText)
			]
		]
	];
	
}

void SElSelectMapItemWidget::Init(FText Text)
{
	if (MapText)
	{
		MapText->SetText(Text);
	}
}

FReply SElSelectMapItemWidget::OnMouseButtonDoubleClick(const FGeometry& InMyGeometry,
	const FPointerEvent& InMouseEvent)
{
	ElHelper::Debug(FString("OnMouseButtonDoubleClick"));
	MapWidgetClicked.ExecuteIfBound(MapId);
	return FReply::Handled();
}

FReply SElSelectMapItemWidget::OnMouseButtonClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent)
{
	ElHelper::Debug(FString("OnMouseButtonClick"));
	MapWidgetClicked.ExecuteIfBound(MapId);
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
