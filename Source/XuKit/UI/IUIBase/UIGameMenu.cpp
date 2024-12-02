// Fill out your copyright notice in the Description page of Project Settings.


#include "UIGameMenu.h"

EUILayer UUIGameMenu::GetUILayer_Implementation() const
{
	return EUILayer::Low;
}

EUIType UUIGameMenu::GetUIType_Implementation() const
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
