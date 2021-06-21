// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ElTypes.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(FSButtonWidgetClicked,const EMenuButtonType::Type)

class EL_API SButtonWidget : public SCompoundWidget
{
	
public:
	SLATE_BEGIN_ARGS(SButtonWidget)
	{}
		SLATE_ATTRIBUTE(FText,ButtonText)//attribute
		SLATE_ATTRIBUTE(EMenuButtonType::Type,MenuButtonType)
		SLATE_ATTRIBUTE(FSlateBrush,ButtionImage)
		SLATE_EVENT(FSButtonWidgetClicked,OnClicked)
		
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	//virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;
	virtual  void OnMouseLeave(const FPointerEvent& MouseEvent) override;
private:
	//引入Sytle|获取MenuStyle
	const struct FElMenuStyle* MenuStyle;

	FSlateBrush ButtionImage;
	//按下事件委托
	FSButtonWidgetClicked OnClicked;
	//保存按钮类型
	EMenuButtonType::Type MenuButtonType;
	//按钮是否已经按下
	bool IsMouseButtonDow=false;
	
};
