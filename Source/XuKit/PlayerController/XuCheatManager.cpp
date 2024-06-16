// Fill out your copyright notice in the Description page of Project Settings.


#include "XuKit/PlayerController/XuCheatManager.h"

#include "XuKit/XuBPFuncLib.h"
#include "XuKit/Data/DataMgr.h"
#include "XuKit/Event/EventMgr.h"


void UXuCheatManager::GM_SaveAppconfig()
{
	GetWorld()->GetSubsystem<UDataMgr>()->GetAppConfigDataBase()->OnSave();
}

void UXuCheatManager::GM_registFreshRoom()
{
	FXuEventDelegate fresh_room_list_eventDelegate;
	fresh_room_list_eventDelegate.BindDynamic(this, &UXuCheatManager::freshRoom);
	GetWorld()->GetSubsystem<UEventMgr>()->RegistEvent(EXuEventType::FreshRoomList, freshRoomID,fresh_room_list_eventDelegate);

}

void UXuCheatManager::freshRoom(UEventData* EventData)
{
	XuPRINT(TEXT("freshRoom"));
}

void UXuCheatManager::GM_callFreshRoom()
{
	GetWorld()->GetSubsystem<UEventMgr>()->BroadcastEvent(EXuEventType::FreshRoomList, nullptr);
}
