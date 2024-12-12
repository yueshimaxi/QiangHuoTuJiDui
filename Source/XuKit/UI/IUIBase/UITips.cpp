// Fill out your copyright notice in the Description page of Project Settings.


#include "UITips.h"

#include "XuKit/XuBPFuncLib.h"
#include "XuKit/UI/UIMgr.h"

EUILayer UUITips::GetUILayer() const
{
	return EUILayer::Tips;
}

EUIType UUITips::GetUIType() const
{
	return EUIType::Normal;
}

void UUITips::OnShowed()
{
	Super::OnShowed();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UUITips::WaitForDestroy, 3.0f, false);
	
}

void UUITips::SetTipsText(FString tips)
{
	Text_Tips->SetText(FText::FromString(tips));
}

void UUITips::WaitForDestroy()
{
	UXuBPFuncLib::GetUIManager(this)->HideUI<UUITips>();
}
