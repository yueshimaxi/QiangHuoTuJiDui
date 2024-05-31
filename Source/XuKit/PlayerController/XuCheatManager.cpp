// Fill out your copyright notice in the Description page of Project Settings.


#include "XuKit/PlayerController/XuCheatManager.h"

#include "XuKit/Data/DataMgr.h"



void UXuCheatManager::GM_SaveAppconfig()
{
	GetWorld()->GetSubsystem<UDataMgr>()->GetAppConfigDataBase()->OnSave();
}
