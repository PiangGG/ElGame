// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SElGameCompleteWidget.h"
#include "SlateOptMacros.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/ElGameHUD.h"
#include "UI/Style/ElGameWidgetStyle.h"
#include "UI/Style/ElStyle.h"
#include "UI/Widget/SButtonWidget.h"
#include "UI/Widget/SElGameHUDWidget.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SUniformGridPanel.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SElGameCompleteWidget::Construct(const FArguments& InArgs)
{
	GameStyle=&ElStyle::Get().GetWidgetStyle<FElGameStyle>("BPElGameStyle");
	ChildSlot
	[
		// Populate the widget
		SNew(SBox)
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SNew(SImage)
				.Image(&GameStyle->GameBackgroundBrush)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			.Padding(FMargin(0.0f,100.0f,0.0f,0.0f))
			[
				SNew(STextBlock)
				.Text(NSLOCTEXT("ElMenu","GameComplate!","GameComplate!"))
				.Font(GameStyle->GameFont)
			]
			+SOverlay::Slot()
			.Padding(FMargin(200.0f,350.0f,200.0f,350.0f))
			[
				SAssignNew(GameOptionGridPanel,SUniformGridPanel)
				.SlotPadding(20.0f)
			]
		]
	];

	if (GameOptionGridPanel)
	{
		GameOptionGridPanel->AddSlot(0,0)
		[
			SNew(SBox)
			.HeightOverride(256.0)
			.WidthOverride(256.0)
			[
				SAssignNew(NextMapButton,SButtonWidget)
				.MenuButtonType(EMenuButtonType::NextMap)
				.ButtonText(NSLOCTEXT("ElMenu","Next","Next"))
				.ButtionImage(GameStyle->GameBackgroundBrush)
				.OnClicked(this,&SElGameCompleteWidget::MenuButtonOnClicked)
			]
			
		];
		GameOptionGridPanel->AddSlot(1,0)
		[
			SNew(SBox)
			.HeightOverride(256.0)
			.WidthOverride(256.0)
			[
				SAssignNew(ReStartGameButton,SButtonWidget)
				.MenuButtonType(EMenuButtonType::ReStartGame)
				.ButtonText(NSLOCTEXT("ElMenu","ReStartGame","ReStartGame"))
				.ButtionImage(GameStyle->Icon_ReStart)
				.OnClicked(this,&SElGameCompleteWidget::MenuButtonOnClicked)
			]
			
		];
		GameOptionGridPanel->AddSlot(2,0)
		[
			SNew(SBox)
			.HeightOverride(256.0)
			.WidthOverride(256.0)
			[
				SAssignNew(BackMainMenuButton,SButtonWidget)
				.MenuButtonType(EMenuButtonType::BackMainMenu)
				.ButtonText(NSLOCTEXT("ElMenu","BackMainMenu","BackMainMenu"))
				.ButtionImage(GameStyle->GameBackgroundBrush)
				.OnClicked(this,&SElGameCompleteWidget::MenuButtonOnClicked)
			]
		];
		GameOptionGridPanel->AddSlot(3,0)
		[	SNew(SBox)
			.HeightOverride(256.0)
			.WidthOverride(256.0)
			[
				SAssignNew(QuiGameButton,SButtonWidget)
				.MenuButtonType(EMenuButtonType::QuitGame)
				.ButtonText(NSLOCTEXT("ElMenu","QuitGame","QuitGame"))
				.ButtionImage(GameStyle->GameBackgroundBrush)
				.OnClicked(this,&SElGameCompleteWidget::MenuButtonOnClicked)
			]
		];
	}
	
}

void SElGameCompleteWidget::MenuButtonOnClicked(EMenuButtonType::Type ButtonType)
{
	if (GWorld&&UGameplayStatics::GetPlayerController(GWorld, 0))
	{
		AElGameHUD* GameHUD=Cast<AElGameHUD>(UGameplayStatics::GetPlayerController(GWorld, 0)->GetHUD());

		if (GameHUD)
		{
			GameHUD->GameHUDWidget->GameButtonOnClicked(ButtonType);
		}	
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
