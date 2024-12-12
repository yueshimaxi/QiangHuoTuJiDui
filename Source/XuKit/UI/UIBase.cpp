// Fill out your copyright notice in the Description page of Project Settings.


#include "UIBase.h"

#include "Animation/WidgetAnimation.h"


EUILayer UUIBase::GetUILayer() const
{
	EUILayer Layer = EUILayer::Low;
	return Layer;
}

EUIType UUIBase::GetUIType() const
{
	EUIType Type = EUIType::Normal;
	return Type;
}


void UUIBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Event_OnActiveAnimationFinished.BindDynamic(this, &UUIBase::OnActiveAnimationFinished);
	if (OnActiveAnimation)
	{
		BindToAnimationFinished(OnActiveAnimation, Event_OnActiveAnimationFinished);
	}
	
}

void UUIBase::NativeConstruct()
{
	Super::NativeConstruct();
	if (OnActiveAnimation)
	{
		PlayAnimation(OnActiveAnimation);
	}else
	{
		Event_OnActiveAnimationFinished.ExecuteIfBound();
	}
}
void UUIBase::OnActiveAnimationFinished()
{
	OnShowed();
}

void UUIBase::OnShowed()
{
}

void UUIBase::OnHide()
{
}


