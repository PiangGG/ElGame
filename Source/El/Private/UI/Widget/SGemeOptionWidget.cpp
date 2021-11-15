// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SGemeOptionWidget.h"
#include "SlateOptMacros.h"
#include "Gameplay/ElPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/ElGameHUD.h"
#include "UI/Style/ElGameWidgetStyle.h"
#include "UI/Style/ElStyle.h"
#include "UI/Widget/SButtonWidget.h"
#include "UI/Widget/SElGameHUDWidget.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SUniformGridPanel.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SGemeOptionWidget::Construct(const FArguments& InArgs)
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
			.Padding(FMargin(200.0f,350.0f,200.0f,350.0f))
			[
				SAssignNew(GameOptionGridPanel,SUniformGridPanel)
				//.SlotPadding()
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
				SAssignNew(BackGameButton,SButtonWidget)
				.MenuButtonType(EMenuButtonType::BackGame)
				.ButtonText(NSLOCTEXT("ElMenu","BackGame","BackGame"))
				.ButtionImage(GameStyle->GameBackgroundBrush)
				.OnClicked(this,&SGemeOptionWidget::MenuButtonOnClicked)
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
				.OnClicked(this,&SGemeOptionWidget::MenuButtonOnClicked)
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
				.OnClicked(this,&SGemeOptionWidget::MenuButtonOnClicked)
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
				.OnClicked(this,&SGemeOptionWidget::MenuButtonOnClicked)
			]
		];
	}
}

void SGemeOptionWidget::MenuButtonOnClicked(EMenuButtonType::Type ButtonType)
{
	if (GWorld&&UGameplayStatics::GetPlayerController(GWorld, 0))
	{
		/*AElGameHUD* GameHUD=Cast<AElGameHUD>(UGameplayStatics::GetPlayerController(GWorld, 0)->GetHUD());

		if (GameHUD)
		{
			GameHUD->GameHUDWidget->GameButtonOnClicked(ButtonType);
		}*/
		AElPlayerController* PlayerController=Cast<AElPlayerController>(UGameplayStatics::GetPlayerController(GWorld, 0));

		if (PlayerController)
		{
			PlayerController->GameHUDWidget->GameButtonOnClicked(ButtonType);
		}
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
