// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"

#include "ElGameWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct EL_API FElGameStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FElGameStyle();
	virtual ~FElGameStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FElGameStyle& GetDefault();

	UPROPERTY(EditAnywhere,Category=MenuHUD)
	FSlateBrush GameBackgroundBrush;
	UPROPERTY(EditAnywhere,Category=MenuHUD)
	FSlateBrush ProbarBGBrush;
	UPROPERTY(EditAnywhere,Category=MenuHUD)
	FSlateBrush ProbarFillImageBrush;
	
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UElGameWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FElGameStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
