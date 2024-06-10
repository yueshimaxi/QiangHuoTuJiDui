// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "QHGameModeBase.generated.h"

class UWeaponInfoDataAsset;
class UCharactorClassInfo;
/**
 * 
 */
UCLASS()
class XUKIT_API AQHGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,Category="AInitInfo")
	TObjectPtr<UCharactorClassInfo> EnemyInitDataAsset;
	UPROPERTY(EditAnywhere,Category="AInitInfo")
	TObjectPtr<UWeaponInfoDataAsset> weapon_info_data_asset;
};
