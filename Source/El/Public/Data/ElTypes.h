// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
//语言枚举
UENUM()
enum class ECultureTeam:uint8
{
	EN=0,
	ZH
};

namespace EMenuItem
{
	enum Type
	{
		None,
	};
}

namespace GameMainState
{
	enum Type
	{
		None,
		MainMenu,
		SelectMap,
		GameSetting
	};
}
namespace InGameMenuState
{
	enum Type
	{
		None,
	};
}
//鼠标点击按钮类型
namespace EMenuButtonType
{
	enum Type
	{
		None,
		StartGame,
		GameSetting,
		QuitGame
	};
}
