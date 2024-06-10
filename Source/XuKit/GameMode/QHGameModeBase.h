// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "QHGameModeBase.generated.h"

class UCharactorClassInfo;
/**
 * 
 */
UCLASS()
class XUKIT_API AQHGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCharactorClassInfo> EnemyInitDataAsset;
};
