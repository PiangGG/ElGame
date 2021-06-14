// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
//语言枚举
UENUM()
enum class ELanguage:uint8
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

namespace EGameMainState
{
	enum Type
	{
		None,
		MainMenu,
		SelectMap,
		GameSetting
	};
}
namespace EInGameMenuState
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
		QuitGame,
		BackMainMenu,
		GameOption,
		BackGame,
		ReStartGame,
		NextMap
	};
}

namespace EControllerState
{
	enum Type
	{
		GameOnly,
		UIOnly,
		GameAndUI
	};
}

namespace EGameState
{
	enum Type
	{
		None,
		Playing,
		Complate
	};
}
namespace EGameHUDState
{
	enum Type
	{
		None,
		Option,
		Complete,
		Over
	};
}
