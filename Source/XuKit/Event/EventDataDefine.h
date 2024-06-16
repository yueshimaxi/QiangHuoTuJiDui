// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventMgr.h"
#include "UObject/NoExportTypes.h"
#include "XuKit/GameInstance/XuGI.h"
#include "EventDataDefine.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UEventDataDefine : public UObject
{
	GENERATED_BODY()
};






UCLASS()
class UFirstEventData : public UEventData
{
	GENERATED_BODY()

public:
	virtual EXuEventType GetEventType() override
	{
		return EXuEventType::FirstEvent;
	}

	UPROPERTY()
	FString id;

};


UCLASS()
class UFreshRoomListEventData : public UEventData
{
	GENERATED_BODY()

public:
	virtual EXuEventType GetEventType() override
	{
		return EXuEventType::FreshRoomList;
	}

	UPROPERTY()
	TArray<UCustomBlueprintSessionResultData*> roomListData;

};




UCLASS()
class UFreshHUDEventData : public UEventData
{
	GENERATED_BODY()

public:
	virtual EXuEventType GetEventType() override
	{
		return EXuEventType::FreshHUD;
	}



};


