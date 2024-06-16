// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "XuCheatManager.generated.h"

class UEventData;
/**
 * 
 */
UCLASS()
class XUKIT_API UXuCheatManager : public UCheatManager
{
	GENERATED_BODY()


	UFUNCTION(Exec)
	void GM_SaveAppconfig();
	UFUNCTION(Exec)
	void GM_registFreshRoom();
	int freshRoomID;
	void freshRoom(UEventData* EventData);
	UFUNCTION(Exec)
	void GM_callFreshRoom();
};
