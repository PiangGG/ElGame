// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Style/ElMenuWidgetStyle.h"

FElMenuStyle::FElMenuStyle()
{
}

FElMenuStyle::~FElMenuStyle()
{
}

const FName FElMenuStyle::TypeName(TEXT("FElMenuStyle"));

const FElMenuStyle& FElMenuStyle::GetDefault()
{
	static FElMenuStyle Default;
	return Default;
}

void FElMenuStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

