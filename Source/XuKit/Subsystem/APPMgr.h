// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "APPMgr.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UAPPMgr : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable)
	void Init();
	
};
