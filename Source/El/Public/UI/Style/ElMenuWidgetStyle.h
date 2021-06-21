// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"
#include "ElMenuWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct EL_API FElMenuStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FElMenuStyle();
	virtual ~FElMenuStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FElMenuStyle& GetDefault();

	UPROPERTY(EditAnywhere,Category=MenuHUD)
	FSlateBrush MenuBackgroundBrush;
	UPROPERTY(EditAnywhere,Category=MenuHUD)
	FSlateBrush TextBg;
	UPROPERTY(EditAnywhere,Category=MenuHUD)
	FSlateBrush MapBg;
	UPROPERTY(EditAnywhere,Category=MenuHUD)
	FSlateColor TextComboBoxColor;
	UPROPERTY(EditAnywhere,Category=MenuHUDSetting)
	FSlateFontInfo SlateFontInfo;
	
	UPROPERTY(EditAnywhere,Category=MenuHUDSetting)
	FButtonStyle ButtonStyle;
	UPROPERTY(EditAnywhere,Category=MenuHUDSetting)
	FComboBoxStyle ComboBoxStyle;

	
	UPROPERTY(EditAnywhere,Category=Font)
	FSlateFontInfo MenuFontInfo;

	
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UElMenuWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FElMenuStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
