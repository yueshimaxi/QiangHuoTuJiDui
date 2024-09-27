// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "XuKit/QiangHuoTuJiDui.h"
#include "QHGameplayAbility.generated.h"
USTRUCT(BlueprintType)
struct  FSwapWeaponDirGameplayAbilityTargetData : public FGameplayAbilityTargetData
{
	GENERATED_BODY()

public:
	// 添加你需要的bool成员变量
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bSwapForward;

	// 构造函数
	FSwapWeaponDirGameplayAbilityTargetData()
	{
		bSwapForward = false;
	}

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FSwapWeaponDirGameplayAbilityTargetData::StaticStruct();
	}

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

};

template<>
struct TStructOpsTypeTraits<FSwapWeaponDirGameplayAbilityTargetData> : public TStructOpsTypeTraitsBase2<FSwapWeaponDirGameplayAbilityTargetData>
{
	enum
	{
		WithNetSerializer = true	// For now this is REQUIRED for FGameplayAbilityTargetDataHandle net serialization to work
	};
};
/**
 * 
 */
UCLASS()
class XUKIT_API UQHGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EQHAbilityInputID AbilityInputID = EQHAbilityInputID::None;
	UPROPERTY(EditDefaultsOnly,Category = "AInitInfo")
	FGameplayTag start_up_input_ability_tag;
	
	UPROPERTY(EditDefaultsOnly,Category = "AInitInfo")
	FGameplayTag cooldown_tag;

	
};
