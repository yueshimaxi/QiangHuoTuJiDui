// Fill out your copyright notice in the Description page of Project Settings.


#include "UIInteraction.h"

EUILayer UUIInteraction::GetUILayer_Implementation() const
{
	return EUILayer::Low;

}

EUIType UUIInteraction::GetUIType_Implementation() const
{
	return EUIType::Normal;
}

void UUIInteraction::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UUIInteraction::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUIInteraction::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUIInteraction::UpdateMousePosition(FVector2D MousePosition)
{
	//移动控件到鼠标位置
	SetPositionInViewport(MousePosition);
}

void UUIInteraction::Interact()
{
}
