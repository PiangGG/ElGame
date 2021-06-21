// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ElDataHandle.h"

#include "Data/ElJsonHandle.h"
#include "Data/ElSingleton.h"

class ElJsonHandle;
TSharedPtr<ElDataHandle> ElDataHandle::DataInstance=NULL;

ElDataHandle::ElDataHandle()
{
	//GameSetConfigfile=FString("");
	InitializeGameSetting();
}

void ElDataHandle::Initialize()
{
	if (!DataInstance.IsValid())
	{
		DataInstance=ElDataHandle::Create();
	}
}

TSharedPtr<ElDataHandle> ElDataHandle::Get()
{
	Initialize();
	return DataInstance;
}

void ElDataHandle::ChangeLocalizationCulture(ELanguage Language)
{
	switch (Language)
	{
	case ELanguage::ZH:
		{
			FInternationalization::Get().SetCurrentCulture(TEXT("zh"));
			UE_LOG(LogTemp,Warning,TEXT("zh"));
			break;
		}
	case ELanguage::EN:
		{
			FInternationalization::Get().SetCurrentCulture(TEXT("en"));
			UE_LOG(LogTemp,Warning,TEXT("en"));
			break;
		}
	}
	CurrentLanguage=Language;
	/*SlAiSingleton<SlAiJsonHandle>::Get()->UpdataRecordData(
		GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"),CurrentCultrueTeam),
		MusicVolume,
		SoundVolume,
		&RecordDataList);*/
}

void ElDataHandle::InitializeGameSetting()
{
	//初始化存档名
	GameSetConfigfile=FString("");
	//获取语言
	FString Language;
	//读取存档数据
	ElSingleton<ElJsonHandle>::Get()->GameSettingJsonRead(Language,Languages);
	//初始化语言
	ChangeLocalizationCulture(FStirngToELanguage(Language));
}

void ElDataHandle::UpdateGameSetting()
{
	//更新語言
	FString Language;
	ElSingleton<ElJsonHandle>::Get()->GameSettingJsonRead(Language,Languages);
	ChangeLocalizationCulture(FStirngToELanguage(Language));
}

TSharedPtr<ElDataHandle> ElDataHandle::Create()
{
	//MakeShareable 可以用来创建共享指针和共享引用
	TSharedPtr<ElDataHandle> DataRef = MakeShareable(new ElDataHandle());
	return DataRef;
}

ELanguage ElDataHandle::FStirngToELanguage(FString& string)
{
	if (string.Equals("简体中文"))
	{
		return ELanguage::ZH;
	}else if (string.Equals("English"))
	{
		return ELanguage::EN;
	}else
	{
		return ELanguage::ZH;
	}
}
