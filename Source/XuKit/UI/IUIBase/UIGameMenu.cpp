// Fill out your copyright notice in the Description page of Project Settings.


#include "UIGameMenu.h"

#include "UIGameSettingScreen.h"
#include "XuKit/XuBPFuncLib.h"
#include "XuKit/UI/UIMgr.h"

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
	btn_exit->OnClicked().AddUObject(this,&UUIGameMenu::OnClickBtnExit);
	btn_setting->OnClicked().AddUObject(this,&UUIGameMenu::OnClickBtnSetting);
	btn_cancel->OnClicked().AddUObject(this,&UUIGameMenu::OnClickBtnCancel);
}

void UUIGameMenu::OnShowed()
{
	Super::OnShowed();
	
}

void UUIGameMenu::OnClickBtnExit()
{
}

void UUIGameMenu::OnClickBtnSetting()
{
	UXuBPFuncLib::GetUIManager(this)->ShowUI<UUIGameSettingScreen>();
}

void UUIGameMenu::OnClickBtnCancel()
{
	UXuBPFuncLib::GetUIManager(this)->HideUI<UUIGameMenu>();
}

