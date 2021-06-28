// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SButtonWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/ElMenuWidgetStyle.h"
#include "UI/Style/ElStyle.h"
#include "Widgets/Images/SImage.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SButtonWidget::Construct(const FArguments& InArgs)
{
	OnClicked=InArgs._OnClicked;
	MenuButtonType=InArgs._MenuButtonType.Get();
	ButtionImage=InArgs._ButtionImage.Get();
	MenuStyle=&ElStyle::Get().GetWidgetStyle<FElMenuStyle>("BPElMenuStyle");
	ChildSlot
	[
		// Populate the widget
		SNew(SBox)
		.WidthOverride(256.0f)
		.HeightOverride(256.0f)
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SNew(SImage)
				//.ColorAndOpacity(this,&SSlAiMenuItemWidget::GetTintColor)
				.Image(&ButtionImage)
			]
			+SOverlay::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			[
				SNew(STextBlock)
				.Text(InArgs._ButtonText)
				.Font(MenuStyle->MenuFontInfo)
				
			]
		]
	];

}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
FReply SButtonWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	IsMouseButtonDow=true;
	//ElHelper::Debug(FString("true"));
	OnClicked.ExecuteIfBound(MenuButtonType);
	return FReply::Handled();
}

FReply SButtonWidget::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (IsMouseButtonDow)
	{
		IsMouseButtonDow=false;
		//OnClicked.ExecuteIfBound(MenuButtonType);
		//ElHelper::Debug(FString("false"));
	}
	return FReply::Handled();
}

void SButtonWidget::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	IsMouseButtonDow=false;
}

FReply SButtonWidget::OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent)
{
	OnClicked.ExecuteIfBound(MenuButtonType);
	return FReply::Handled();
}
