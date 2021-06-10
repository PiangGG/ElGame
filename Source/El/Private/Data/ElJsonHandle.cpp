// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ElJsonHandle.h"

#include "Common/ElHelper.h"

ElJsonHandle::ElJsonHandle()
{
	RelativePath = FString("Res/Config/");
	GameSettingFileName =FString("GameSet.json");
}

void ElJsonHandle::GameSettingJsonRead(FString &Language,TArray<FString>& Languages)
{
	FString JsonValue;
	LoadStringFromFile(GameSettingFileName,RelativePath,JsonValue);
	TArray<TSharedPtr<FJsonValue>> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);
	//解析
	if (FJsonSerializer::Deserialize(JsonReader,JsonParsed))
	{
		//獲取默認語言設置
		Language=JsonParsed[0]->AsObject()->GetStringField(FString("Language"));
		//獲取語言設置Option
		TArray<TSharedPtr<FJsonValue>> LanguageArray = JsonParsed[1]->AsObject()->GetArrayField(FString("Languages"));
		for (int i=0;i<LanguageArray.Num();++i)
		{
			FString thisLanguage= LanguageArray[i]->AsObject()->GetStringField(FString::FromInt(i));
			Languages.Add(thisLanguage);
		}
	}else
	{
		ElHelper::Debug(FString("GameSettingFileName not can read!"));
	}
}

bool ElJsonHandle::LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString)
{
	if (!FileName.IsEmpty())
	{
		//获取绝对路径
		FString AbsoPath=FPaths::ProjectContentDir()+RelaPath+FileName;
		if (FPaths::FileExists(AbsoPath))
		{
			if (FFileHelper::LoadFileToString(ResultString,*AbsoPath))
			{
				return true;
			}else
			{
				//加载不成功
				ElHelper::Debug(AbsoPath+FString("文件加载错误!"));
			}
		}else
		{
			ElHelper::Debug(AbsoPath+FString("文件不存在!"));
		}
	}
	return false;
}

bool ElJsonHandle::GetFStringInJsonData(const TSharedPtr<FJsonObject>& JsonObj, FString& JsonStr)
{
	if (JsonObj.IsValid()&&JsonObj->Values.Num()>0)
	{
		TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonStr);
		//序列化
		FJsonSerializer::Serialize(JsonObj.ToSharedRef(),JsonWriter);
		return true;
	}
	return  false;
}

bool ElJsonHandle::WriteFileWithJsonData(const FString& JsonStr, const FString& RelaPath, const FString& FileName)
{
	if (!JsonStr.IsEmpty())
	{
		if (!FileName.IsEmpty())
		{
			//获取一下绝对路径
			FString AbsoPath = FPaths::ProjectContentDir()+RelativePath+FileName;
			//保存
			if(FFileHelper::SaveStringToFile(JsonStr,*AbsoPath))
			{
				return true;
			}else
			{
				ElHelper::Debug(AbsoPath+FileName+FString("保存失败"));
			}
		}	
	}
	return  false;
}
