// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LevelMgr.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API ULevelMgr : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	void Init();
	
};
