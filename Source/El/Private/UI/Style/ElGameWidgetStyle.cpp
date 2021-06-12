// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Style/ElGameWidgetStyle.h"

FElGameStyle::FElGameStyle()
{
}

FElGameStyle::~FElGameStyle()
{
}

const FName FElGameStyle::TypeName(TEXT("FElGameStyle"));

const FElGameStyle& FElGameStyle::GetDefault()
{
	static FElGameStyle Default;
	return Default;
}

void FElGameStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

