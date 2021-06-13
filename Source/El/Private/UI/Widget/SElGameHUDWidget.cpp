// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SElGameHUDWidget.h"

#include "SEditorViewportToolBarMenu.h"
#include "SlateOptMacros.h"
#include "Common/ElHelper.h"
#include "Gameplay/ElGI.h"
#include "Gameplay/ElPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Style/ElGameWidgetStyle.h"
#include "UI/Style/ElStyle.h"
#include "UI/Widget/SButtonWidget.h"
#include "UI/Widget/SElGameCompleteWidget.h"
#include "UI/Widget/SElUserInfoWidget.h"
#include "UI/Widget/SGemeOptionWidget.h"
#include "Widgets/Images/SImage.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SElGameHUDWidget::Construct(const FArguments& InArgs)
{
	GameStyle=&ElStyle::Get().GetWidgetStyle<FElGameStyle>("BPElGameStyle");
	
	ChildSlot
	[
		// Populate the widget
		SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(FMargin(0.0f,0.0f,0.0f,100.0f))
			[
				SAssignNew(ElUserInfoWidget,SElUserInfoWidget)
				.Visibility(EVisibility::Visible)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Top)
			.Padding(FMargin(0.0f,20.0f,20.0f,0.0f))
			[
				SNew(SBox)
				.HeightOverride(50.0f)
				.WidthOverride(50.0f)
				.Visibility(bOptionVisibility)
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
					[
						SAssignNew(OptionButton,SButtonWidget)
						.Visibility(EVisibility::Visible)
						.ButtonText(NSLOCTEXT("ElMenu","Option","Option"))
						.MenuButtonType(EMenuButtonType::GameOption)
						.OnClicked(this, &SElGameHUDWidget::GameButtonOnClicked)
						.ButtionImage(GameStyle->Icon_Option)
					]
				]	
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(GemeOptionWidget,SGemeOptionWidget)
				.Visibility(EVisibility::Hidden)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(GemeCompleteWidget,SElGameCompleteWidget)
				.Visibility(EVisibility::Hidden)
			]
		]
		
	];
	
}

void SElGameHUDWidget::GameButtonOnClicked(EMenuButtonType::Type ButtonType)
{
	switch (ButtonType)
	{
	case EMenuButtonType::None: break;
	case EMenuButtonType::StartGame: break;
	case EMenuButtonType::GameSetting: break;
	case EMenuButtonType::QuitGame:
		QuiGame_OnClick();
		break;
	case EMenuButtonType::BackMainMenu:
		BackMainMenu_OnClick();
		break;
	case EMenuButtonType::GameOption:
		GameOption_OnClick();
		break;
	case EMenuButtonType::BackGame:
		BackGame_OnClick();
		break;
	case EMenuButtonType::ReStartGame:
		ReStartGame_OnClick();
		break;
	case EMenuButtonType::NextMap:
		NextMap_OnClick();
	default: break;
	}
}

void SElGameHUDWidget::ChangeGameHUDState(EGameHUDState::Type GameHUDState)
{
	CurrenGameHUDState=GameHUDState;
	switch (CurrenGameHUDState)
	{
	case EGameHUDState::None: 
		GameState_None();
		break;
	case EGameHUDState::Option:
		GameState_Option();
		break;
	case EGameHUDState::Complete:
		GameState_Complete();
	default: break;
	}
}

void SElGameHUDWidget::GameState_None()
{
	if (ElUserInfoWidget)
	{
		ElUserInfoWidget->SetVisibility(EVisibility::Visible);
	}
	if (OptionButton)
	{
		OptionButton->SetVisibility(EVisibility::Visible);
		bOptionVisibility=EVisibility::Visible;
	}
	if (GemeOptionWidget)
	{
		GemeOptionWidget->SetVisibility(EVisibility::Hidden);
	}
	if (GemeCompleteWidget)
	{
		GemeCompleteWidget->SetVisibility(EVisibility::Hidden);
	}
}

void SElGameHUDWidget::GameState_Option()
{
	if (ElUserInfoWidget)
	{
		ElUserInfoWidget->SetVisibility(EVisibility::Hidden);
	}
	if (OptionButton)
	{
		OptionButton->SetVisibility(EVisibility::Hidden);
		bOptionVisibility=EVisibility::Hidden;
	}
	if (GemeOptionWidget)
	{
		GemeOptionWidget->SetVisibility(EVisibility::Visible);
	}
	if (GemeCompleteWidget)
	{
		GemeCompleteWidget->SetVisibility(EVisibility::Hidden);
	}
}

void SElGameHUDWidget::GameState_Complete()
{
	if (ElUserInfoWidget)
	{
		ElUserInfoWidget->SetVisibility(EVisibility::Hidden);
	}
	if (OptionButton)
	{
		OptionButton->SetVisibility(EVisibility::Hidden);
		bOptionVisibility=EVisibility::Hidden;
	}
	if (GemeOptionWidget)
	{
		GemeOptionWidget->SetVisibility(EVisibility::Hidden);
	}
	if (GemeCompleteWidget)
	{
		GemeCompleteWidget->SetVisibility(EVisibility::Visible);
	}
}

void SElGameHUDWidget::GameOption_OnClick()
{
	ElHelper::Debug(FString("GameOption_OnClick"));
	ChangeGameHUDState(EGameHUDState::Option);
}

void SElGameHUDWidget::BackGame_OnClick()
{
	ChangeGameHUDState(EGameHUDState::None);
}

void SElGameHUDWidget::ReStartGame_OnClick()
{
	ChangeGameHUDState(EGameHUDState::None);
	UElGI *GI=Cast<UElGI>(UGameplayStatics::GetGameInstance(GWorld));
	UGameplayStatics::OpenLevel(GWorld,FName("Map"+FString::FromInt(GI->GetCurrentMapID())));
}

void SElGameHUDWidget::QuiGame_OnClick()
{
	if (UGameplayStatics::GetPlayerController(GWorld,0))
	{
		Cast<AElPlayerController>(UGameplayStatics::GetPlayerController(GWorld,0))->ConsoleCommand("quit");
	}
}

void SElGameHUDWidget::NextMap_OnClick()
{

	UElGI *GI=Cast<UElGI>(UGameplayStatics::GetGameInstance(GWorld));
	if (GI->GetCurrentMapID()<17)
	{
		ChangeGameHUDState(EGameHUDState::None);
		UGameplayStatics::OpenLevel(GWorld,FName("Map"+FString::FromInt(GI->GetCurrentMapID()+1)));
	}
}

void SElGameHUDWidget::BackMainMenu_OnClick()
{
	ChangeGameHUDState(EGameHUDState::None);
	UElGI *GI=Cast<UElGI>(UGameplayStatics::GetGameInstance(GWorld));
	UGameplayStatics::OpenLevel(GWorld,FName("MainMenu"));
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
