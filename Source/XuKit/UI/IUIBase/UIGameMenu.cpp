// Fill out your copyright notice in the Description page of Project Settings.


#include "UIGameMenu.h"

EUILayer UUIGameMenu::GetUILayer() const
{
	return EUILayer::Low;
}

EUIType UUIGameMenu::GetUIType() const
{
	return EUIType::Stack;
}

void UUIGameMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UUIGameMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUIGameMenu::NativeDestruct()
{
	Super::NativeDestruct();
}
