// Fill out your copyright notice in the Description page of Project Settings.


#include "APPMgr.h"

#include "XuKit/XuBPFuncLib.h"
#include "XuKit/UI/UIMgr.h"
#include "XuKit/UI/IUIBase/UIMessageBox.h"

void UAPPMgr::Init()
{
	UXuBPFuncLib::GetUIManager(GetWorld())->Init();
}
