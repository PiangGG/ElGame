// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
template<class T>
class EL_API ElSingleton
{
public:
	static  TSharedPtr<T> Get();
	private:
	static void Initialize();

	static TSharedRef<T> Create();

	private:
	static TSharedPtr<T> TInstance;	
};
template <class T>
TSharedPtr<T> ElSingleton<T>::TInstance=NULL;
template <class T>
TSharedPtr<T> ElSingleton<T>::Get()
{
	Initialize();
	return TInstance;
}

template <class T>
void ElSingleton<T>::Initialize()
{
	if (!TInstance.IsValid())
	{
		TInstance=Create();
	}
	
}

template <class T>
TSharedRef<T> ElSingleton<T>::Create()
{
	TSharedRef<T> TRef =MakeShareable(new T());
	return TRef;
}