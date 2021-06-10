// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Data/ElTypes.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class EL_API SElMenuSettingWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SElMenuSettingWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	
	void MenuButtonOnClicked(EMenuButtonType::Type type);

	void LanguageSetStringOnSelectionChanged(TSharedPtr < FString > NewSelection , ESelectInfo :: Type SelectInfo);
private:
	//引入Sytle|获取MenuStyle
	const struct FElMenuStyle* MenuStyle;
	//中間垂直框
	TSharedPtr<class SVerticalBox> VerticalBox;

	//語言設置選項框
	//TSharedPtr<class STextBlock> LanguageTextBlock;
	//下拉菜单|語言設置
	TSharedPtr<STextComboBox> LanguageComboBox;
	//字符指针数组
	TArray<TSharedPtr<FString>> LanguageSetString;
	//返回主界面按鈕
	TSharedPtr<class SButtonWidget> BackMenuButton;
};
