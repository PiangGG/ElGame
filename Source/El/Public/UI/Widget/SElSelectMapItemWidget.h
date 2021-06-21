// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SImage;
DECLARE_DELEGATE_OneParam(FMapWidgetClicked,const int Mapnumber)
class EL_API SElSelectMapItemWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SElSelectMapItemWidget)
	{}
	SLATE_ATTRIBUTE(FText,MapText)
	SLATE_ATTRIBUTE(int,MapId)
	SLATE_ATTRIBUTE(FSlateBrush,MapImage)
	SLATE_EVENT(FMapWidgetClicked,MapWidgetClicked)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void Init(FText Text);
	virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply OnMouseButtonClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent);
	virtual FReply OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;
private:
	//引入Sytle|获取MenuStyle
	const struct FElMenuStyle* MenuStyle = nullptr;

	TSharedPtr<class SImage> MapImage;
	TSharedPtr<class STextBlock> MapText;
	FMapWidgetClicked MapWidgetClicked;

	int MapId = 0;
};
