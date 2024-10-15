// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "XuKit/QiangHuoTuJiDui.h"
#include "QHGameplayAbility.generated.h"

USTRUCT(BlueprintType)
struct FSwapWeaponDirGameplayAbilityTargetData : public FGameplayAbilityTargetData
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

template <>
struct TStructOpsTypeTraits<FSwapWeaponDirGameplayAbilityTargetData> : public TStructOpsTypeTraitsBase2<FSwapWeaponDirGameplayAbilityTargetData>
{
	enum
	{
		WithNetSerializer = true // For now this is REQUIRED for FGameplayAbilityTargetDataHandle net serialization to work
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
	UPROPERTY(EditDefaultsOnly, Category = "AInitInfo")
	FGameplayTag start_up_input_ability_tag;

	UPROPERTY(EditDefaultsOnly, Category = "AInitInfo")
	FGameplayTag cooldown_tag;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	bool bCannotActivateWhileInteracting;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	FGameplayTag InteractingTag;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	FGameplayTag InteractingRemovalTag;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	bool bSourceObjectMustEqualCurrentWeaponToActivate;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
	bool GSCheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo& ActorInfo) const;
	virtual bool GSCheckCost_Implementation(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo& ActorInfo) const;


	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
	void GSApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo& ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const;
	virtual void GSApplyCost_Implementation(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo& ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const;;

	virtual bool CheckCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const override;
};
