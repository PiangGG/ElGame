// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SElMenuSettingWidget.h"

#include "SEditorViewportToolBarMenu.h"
#include "SlateOptMacros.h"
#include "Common/ElHelper.h"
#include "Data/ElDataHandle.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/ElMenuHUD.h"
#include "UI/Widget/SButtonWidget.h"
#include "UI/Widget/SElMenuHUDWidget.h"
#include "UI/Widget/SElMenuMainWidget.h"
#include "Widgets/Input/STextComboBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SElMenuSettingWidget::Construct(const FArguments& InArgs)
{
	
	//初始化下拉菜单
	for(TArray<FString>::TIterator It(ElDataHandle::Get()->Languages);It;++It)
	{
		LanguageSetString.Add(MakeShareable(new FString(*It)));
	}
	//MenuStyle=&ElStyle::Get().GetWidgetStyle<FElMenuStyle>("BPElMenuStyle");
	ChildSlot
	[
		// Populate the widget
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
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
				.Padding(FMargin(20))
				[
					SNew(STextBlock)
					.Text(NSLOCTEXT("ElMenu","Language","Language"))
					.Margin(20)
				]
				+SHorizontalBox::Slot()
				.HAlign(HAlign_Right)
				.VAlign(VAlign_Center)
				.Padding(FMargin(20))
				[
					SAssignNew(LanguageComboBox,STextComboBox)
					//.Font(MenuStyle->Font_30)
					.OptionsSource(&LanguageSetString)
					.OnSelectionChanged(this,&SElMenuSettingWidget::LanguageSetStringOnSelectionChanged)
				]
			]
			+SVerticalBox::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			[
				SAssignNew(BackMenuButton,SButtonWidget)
				.MenuButtonType(EMenuButtonType::BackMainMenu)
				.ButtonText(NSLOCTEXT("ElMenu","Back","Back"))
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
