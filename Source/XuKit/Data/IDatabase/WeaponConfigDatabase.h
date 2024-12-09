// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "XuKit/Data/XuDataBase.h"
#include "WeaponConfigDatabase.generated.h"

struct FWeaponInfo;
class UWeaponInfoDataAsset;
/**
 * 
 */
UCLASS()
class XUKIT_API UWeaponConfigDatabase : public UXuDataBase
{
	GENERATED_BODY()
public:
	virtual ::DataBaseType DataBaseType() override;
	virtual FString DataPath() override;
	virtual void OnParse() override;
	virtual void OnSave() override;
	virtual void ClearData() override;


	UPROPERTY()
	UWeaponInfoDataAsset* weaponInfoDataAsset;

	UFUNCTION()
	FWeaponInfo GetWeaponInfo(FGameplayTag weaponTag);
};
