// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDragMoveButtonWidget.h"
#include "SlateOptMacros.h"
#include "Blueprint/DragDropOperation.h"
#include "Common/ElHelper.h"
#include "UI/Style/ElGameWidgetStyle.h"
#include "UI/Style/ElStyle.h"
#include "Widgets/Images/SImage.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SDragMoveButtonWidget::Construct(const FArguments& InArgs)
{
	GameStyle=&ElStyle::Get().GetWidgetStyle<FElGameStyle>("BPElGameStyle");
	
	ChildSlot
	[
		// Populate the widget
		SNew(SImage)
		.Image(&GameStyle->MoveBG)
		
	];
	//Drag
}

FReply SDragMoveButtonWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	ElHelper::Debug(FString("OnMouseButtonDown"));
	
	//this->OnDragDetected(MyGeometry,MouseEvent,UDragDropOperation::Drop(FPointerEvent::GetCursorDelta()));
	return FReply::Handled();
}

FReply SDragMoveButtonWidget::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	ElHelper::Debug(FString("OnMouseButtonUp"));
	
	return FReply::Handled();
}

FReply SDragMoveButtonWidget::OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	ElHelper::Debug(FString("OnDragDetected"));
	return FReply::Handled();
}

FReply SDragMoveButtonWidget::OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{
	ElHelper::Debug(FString("OnDrop"));
	return FReply::Handled();
}
int32 SDragMoveButtonWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	SCompoundWidget::OnPaint(Args,AllottedGeometry,MyCullingRect,OutDrawElements,LayerId,InWidgetStyle,bParentEnabled);

	return 0;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
