// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SElMenuMainWidget.h"
#include "SlateOptMacros.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Style/ElMenuWidgetStyle.h"
#include "UI/Style/ElStyle.h"
#include "UI/Widget/SElMenuHUDWidget.h"
#include "Widgets/Images/SImage.h"
#include "Engine/World.h"
#include "UI/HUD/ElMenuHUD.h"
#include "Widgets/Layout/SUniformGridPanel.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SElMenuMainWidget::Construct(const FArguments& InArgs)
{
	MenuStyle=&ElStyle::Get().GetWidgetStyle<FElMenuStyle>("BPElMenuStyle");
	ChildSlot
	[
		// Populate the widget
		SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SAssignNew(MenuGridPanel,SUniformGridPanel)
			.SlotPadding(20.0f)
		]
	];
	if (MenuGridPanel)
	{
		MenuGridPanel->AddSlot(0,0)
		[
			SAssignNew(StartGameButton,SButtonWidget)
			.MenuButtonType(EMenuButtonType::StartGame)
			.ButtonText(NSLOCTEXT("ElMenu","StartGame","StartGame"))
			.ButtionImage(MenuStyle->TextBg)
			.OnClicked(this,&SElMenuMainWidget::MenuButtonOnClicked)
		];
		MenuGridPanel->AddSlot(1,0)
		[
			SAssignNew(SeletMapButton,SButtonWidget)
			.MenuButtonType(EMenuButtonType::GameSetting)
			.ButtonText(NSLOCTEXT("ElMenu","MenuGameOption","MenuGameOption"))
			.ButtionImage(MenuStyle->TextBg)
			.OnClicked(this,&SElMenuMainWidget::MenuButtonOnClicked)
		];
		MenuGridPanel->AddSlot(2,0)
		[
			SAssignNew(QuitGameMapButton,SButtonWidget)
			.MenuButtonType(EMenuButtonType::QuitGame)
			.ButtonText(NSLOCTEXT("ElMenu","QuitGame","QuitGame"))
			.ButtionImage(MenuStyle->TextBg)
			.OnClicked(this,&SElMenuMainWidget::MenuButtonOnClicked)
		];
	}
}

void SElMenuMainWidget::MenuButtonOnClicked(EMenuButtonType::Type ButtonType)
{
	if (GWorld&&UGameplayStatics::GetPlayerController(GWorld, 0))
	{
		AElMenuHUD* MenuHUD=Cast<AElMenuHUD>(UGameplayStatics::GetPlayerController(GWorld, 0)->GetHUD());

		if (MenuHUD)
		{
			MenuHUD->MenuHUDWidget->MenuButtonOnClicked(ButtonType);
		}	
	}
}

void SElMenuMainWidget::InitMenu()
{
	
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
