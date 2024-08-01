// Fill out your copyright notice in the Description page of Project Settings.


#include "XuKit/PlayerController/XuCheatManager.h"

#include "XuKit/XuBPFuncLib.h"
#include "XuKit/Data/DataMgr.h"
#include "XuKit/Event/EventMgr.h"


void UXuCheatManager::GM_SaveAppconfig()
{
	 UXuBPFuncLib::GetDataManager(GetWorld())->GetAppConfigDataBase()->OnSave();
}


