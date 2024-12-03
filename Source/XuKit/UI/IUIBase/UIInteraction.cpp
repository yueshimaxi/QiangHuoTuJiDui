// Fill out your copyright notice in the Description page of Project Settings.


#include "UIInteraction.h"

#include "Animation/WidgetAnimation.h"

EUILayer UUIInteraction::GetUILayer() const
{
	return EUILayer::Low;

}

EUIType UUIInteraction::GetUIType() const
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



void UUIInteraction::PlayShowAnim_Implementation(bool bShow)
{
	if (ShowAnimation)
	{
		if (bShow)
		{
			PlayAnimationForward(ShowAnimation);
		}
		else
		{
			PlayAnimationReverse(ShowAnimation);

		}
	}
}