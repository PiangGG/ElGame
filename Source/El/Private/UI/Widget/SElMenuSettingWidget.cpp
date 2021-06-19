// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SElMenuSettingWidget.h"
#include "SlateOptMacros.h"
#include "Common/ElHelper.h"
#include "Data/ElDataHandle.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/ElMenuHUD.h"
#include "UI/Style/ElMenuWidgetStyle.h"
#include "UI/Style/ElStyle.h"
#include "UI/Widget/SButtonWidget.h"
#include "UI/Widget/SElMenuHUDWidget.h"
#include "UI/Widget/SElMenuMainWidget.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/STextComboBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SElMenuSettingWidget::Construct(const FArguments& InArgs)
{
	
	//初始化下拉菜单
	for(TArray<FString>::TIterator It(ElDataHandle::Get()->Languages);It;++It)
	{
		LanguageSetString.Add(MakeShareable(new FString(*It)));
	}
	MenuStyle=&ElStyle::Get().GetWidgetStyle<FElMenuStyle>("BPElMenuStyle");
	ChildSlot
	[
		// Populate the widget
		SNew(SOverlay)
		+SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SAssignNew(VerticalBox,SVerticalBox)
				+SVerticalBox::Slot()
				.VAlign(VAlign_Fill)
				.HAlign(HAlign_Fill)
				[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(1.0f)
					[
						SNew(SBox)
						.HeightOverride(80.0f)
						.WidthOverride(200.0f)
						[
							SNew(SOverlay)
							+SOverlay::Slot()
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Center)
							[
								SNew(STextBlock)
								.Text(NSLOCTEXT("ElMenu","Language","Language"))
								.Font(MenuStyle->MenuFontInfo)
							]
							+SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							[
								SNew(SImage)
								.Image(&MenuStyle->TextBg)
							]
						]
						
					]
					+SHorizontalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Center)
					.Padding(1.0f)
					[
						SNew(SBox)
						.HeightOverride(80.0f)
						.WidthOverride(200.0f)
						[
							SAssignNew(LanguageComboBox,STextComboBox)
							.OptionsSource(&LanguageSetString)
							.ButtonStyle(&MenuStyle->ButtonStyle)
							.Font(MenuStyle->MenuFontInfo)
							.ColorAndOpacity(MenuStyle->TextComboBoxColor)
							.OnSelectionChanged(this,&SElMenuSettingWidget::LanguageSetStringOnSelectionChanged)
					
						]
					]
				]
			]
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
				.OnClicked(this,&SElMenuSettingWidget::MenuButtonOnClicked)
			]
			
		]
	];
	
	if (LanguageSetString[0])
	{
		LanguageComboBox->SetSelectedItem(LanguageSetString[0]);
	}
}

void SElMenuSettingWidget::MenuButtonOnClicked(EMenuButtonType::Type type)
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

void SElMenuSettingWidget::LanguageSetStringOnSelectionChanged(TSharedPtr < FString > NewSelection , ESelectInfo :: Type SelectInfo)
{
	ElDataHandle::Get()->ChangeLocalizationCulture(ElDataHandle::Get()->FStirngToELanguage(LanguageComboBox->GetSelectedItem().ToSharedRef().Get()));
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
