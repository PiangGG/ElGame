// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widget/SElMenuHUDWidget.h"
#include "SlateOptMacros.h"
#include "Gameplay/ElMenuPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/ElMenuHUD.h"
#include "UI/Style/ElMenuWidgetStyle.h"
#include "UI/Style/ElStyle.h"
#include "UI/Widget/SElMenuMainWidget.h"
#include "UI/Widget/SElMenuSelectMapWidget.h"
#include "UI/Widget/SElMenuSettingWidget.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SDPIScaler.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SElMenuHUDWidget::Construct(const FArguments& InArgs)
{
	//获取编译器的MenuStyle|调用单例类ElStyle|在content目录下的蓝图类
	MenuStyle=&ElStyle::Get().GetWidgetStyle<FElMenuStyle>("BPElMenuStyle");
	UIScaler.Bind(this,&SElMenuHUDWidget::GetUIScaler);
	CurreGameMainState=EGameMainState::MainMenu;
	
	ChildSlot
	[
		// Populate the widget
		SNew(SDPIScaler)
		.DPIScale(UIScaler)
		[
			//包裹的大小盒子
			SNew(SOverlay)
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)//横竖填充
			[
				SNew(SImage)//指定背景图片
				.Image(&MenuStyle->MenuBackgroundBrush)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SAssignNew(MenuWidget,SElMenuMainWidget)
				.Visibility(EVisibility::Visible)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(SettingWidget,SElMenuSettingWidget)
				.Visibility(EVisibility::Hidden)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(SelectMapWidget,SElMenuSelectMapWidget)
				.Visibility(EVisibility::Hidden)
			]
			
		]
		
	];
	//初始化为主界面
	if (GWorld)
	{
		AElMenuHUD* MenuHUD=Cast<AElMenuHUD>(UGameplayStatics::GetPlayerController(GWorld, 0)->GetHUD());

		if (MenuHUD)
		{
			MenuHUD->MenuHUDWidget->ChangeGameMenuState(EGameMainState::MainMenu);
		}	
	}
}

void SElMenuHUDWidget::ChangeGameMenuState(EGameMainState::Type newState)
{
	if (CurreGameMainState==newState)return;
	CurreGameMainState = newState;
	switch (newState)
	{
	case EGameMainState::None:

		break;
	case EGameMainState::MainMenu:
		MenuWidget->SetVisibility(EVisibility::Visible);
		SettingWidget->SetVisibility(EVisibility::Hidden);
		SelectMapWidget->SetVisibility(EVisibility::Hidden);
		break;
	case EGameMainState::SelectMap:
		MenuWidget->SetVisibility(EVisibility::Hidden);
		SettingWidget->SetVisibility(EVisibility::Hidden);
		SelectMapWidget->SetVisibility(EVisibility::Visible);
		break;
	case EGameMainState::GameSetting:
		MenuWidget->SetVisibility(EVisibility::Hidden);
		SettingWidget->SetVisibility(EVisibility::Visible);
		SelectMapWidget->SetVisibility(EVisibility::Hidden);
		break;
	}
}

void SElMenuHUDWidget::MenuButtonOnClicked(EMenuButtonType::Type Button)
{
	switch (Button)
	{
	case EMenuButtonType::None: break;
	case EMenuButtonType::StartGame:
		MenuButtonOnClicked_StartGame();
		break;
	case EMenuButtonType::GameSetting:
		MenuButtonOnClicked_GameSetting();
		break;
	case EMenuButtonType::QuitGame:
		MenuButtonOnClicked_QuitGame();
		break;
	case EMenuButtonType::BackMainMenu:
		MenuButtonOnClicked_BackMainMenu();
		break;
	case EMenuButtonType::GameOption:
		break;
	default: break;
	}
}

void SElMenuHUDWidget::MenuButtonOnClicked_StartGame()
{
	if (GWorld)
	{
		AElMenuHUD* MenuHUD=Cast<AElMenuHUD>(UGameplayStatics::GetPlayerController(GWorld, 0)->GetHUD());

		if (MenuHUD)
		{
			MenuHUD->MenuHUDWidget->ChangeGameMenuState(EGameMainState::SelectMap);
		}	
	}
}

void SElMenuHUDWidget::MenuButtonOnClicked_GameSetting()
{
	if (GWorld&&UGameplayStatics::GetPlayerController(GWorld, 0))
	{
		AElMenuHUD* MenuHUD=Cast<AElMenuHUD>(UGameplayStatics::GetPlayerController(GWorld, 0)->GetHUD());

		if (MenuHUD)
		{
			MenuHUD->MenuHUDWidget->ChangeGameMenuState(EGameMainState::GameSetting);
		}	
	}
}

void SElMenuHUDWidget::MenuButtonOnClicked_QuitGame()
{
	if (UGameplayStatics::GetPlayerController(GWorld,0))
	{
		Cast<AElMenuPlayerController>(UGameplayStatics::GetPlayerController(GWorld,0))->ConsoleCommand("quit");
	}
}

void SElMenuHUDWidget::MenuButtonOnClicked_BackMainMenu()
{
	if (GWorld)
	{
		AElMenuHUD* MenuHUD=Cast<AElMenuHUD>(UGameplayStatics::GetPlayerController(GWorld, 0)->GetHUD());

		if (MenuHUD)
		{
			MenuHUD->MenuHUDWidget->ChangeGameMenuState(EGameMainState::MainMenu);
		}	
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

float SElMenuHUDWidget::GetUIScaler() const
{
	return GetViewportSize().Y/1080.f;
}

FVector2D SElMenuHUDWidget::GetViewportSize() const
{
	FVector2D Result(1920,1080);

	if (GEngine&&GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(Result);
	}
	return Result;
}