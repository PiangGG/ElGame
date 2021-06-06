// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FElModule:public FDefaultGameModuleImpl
{
public:
	//开始模块
	virtual void StartupModule() override;
	//结束模块
	virtual void ShutdownModule() override;
};