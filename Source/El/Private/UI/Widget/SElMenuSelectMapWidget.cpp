// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SElMenuSelectMapWidget.h"
#include "SlateOptMacros.h"
#include "Common/ElHelper.h"
#include "Gameplay/ElGI.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/ElMenuHUD.h"
#include "UI/Style/ElMenuWidgetStyle.h"
#include "UI/Style/ElStyle.h"
#include "UI/Widget/SButtonWidget.h"
#include "UI/Widget/SElMenuHUDWidget.h"
#include "UI/Widget/SElSelectMapItemWidget.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SUniformGridPanel.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SElMenuSelectMapWidget::Construct(const FArguments& InArgs)
{
	MenuStyle=&ElStyle::Get().GetWidgetStyle<FElMenuStyle>("BPElMenuStyle");
	
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
			[
				SNew(SImage)
				.Image(&MenuStyle->TextBg)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(FMargin(200.0f,300.f,200.0f,300.0f))
			[
				SAssignNew(MapGridPanel,SUniformGridPanel)
				.SlotPadding(20.0f)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			.Padding(FMargin(0.0f,100.0f,0.0f,0.0f))
			[
				SNew(STextBlock)
				.Text(NSLOCTEXT("ElMenu","SelecMap","SelecMap"))
				.Font(MenuStyle->MenuFontInfo)
			]
			+SOverlay::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Center)
			.Padding(FMargin(0.0f,0.0f,0.0f,100.0f))
			[
				SNew(SBox)
				.HeightOverride(80.0f)
				.WidthOverride(200.0f)
				[
					SAssignNew(BackMenuButton,SButtonWidget)
					.MenuButtonType(EMenuButtonType::BackMainMenu)
					.ButtonText(NSLOCTEXT("ElMenu","Back","Back"))
					.ButtionImage(MenuStyle->TextBg)
					.OnClicked(this,&SElMenuSelectMapWidget::MenuButtonOnClicked)
				]
				
			]
		]
	];
	if (MapGridPanel)
	{
		ElHelper::Debug(FString("MapGridPanel"));
		for (int i=0;i<18;i++)
		{	
			TSharedPtr<SElSelectMapItemWidget> MapItemWidget;
			SAssignNew(MapItemWidget,SElSelectMapItemWidget)
			.MapText(FText::FromString("Map:"+FString::FromInt(i)))
			.MapId(i)
			.MapImage(MenuStyle->MapBg)
			.MapWidgetClicked(this,&SElMenuSelectMapWidget::MenuSelectMapOnClicked);
			MapGridPanel->AddSlot(i%6,i/6)
			[MapItemWidget->AsShared()];
		}
		
	}
	
}

void SElMenuSelectMapWidget::MenuButtonOnClicked(EMenuButtonType::Type type)
{
	if (GWorld)
	{
		AElMenuHUD* MenuHUD=Cast<AElMenuHUD>(UGameplayStatics::GetPlayerController(GWorld, 0)->GetHUD());

		if (MenuHUD)
		{
			MenuHUD->MenuHUDWidget->MenuButtonOnClicked(type);
		}	
	}
}
void SElMenuSelectMapWidget::MenuSelectMapOnClicked(int id)
{
	ElHelper::Debug(FString::FromInt(id));
	
	UElGI *GI=Cast<UElGI>(UGameplayStatics::GetGameInstance(GWorld));
	GI->SetCurrentMapID(id);

	UGameplayStatics::OpenLevel(GWorld,FName("Map"+FString::FromInt(GI->GetCurrentMapID())));
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
