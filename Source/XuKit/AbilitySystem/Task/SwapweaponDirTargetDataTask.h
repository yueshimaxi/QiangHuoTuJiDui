
#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataTask.h"
#include "SwapweaponDirTargetDataTask.generated.h"
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
class XUKIT_API USwapweaponDirTargetDataTask : public UAbilityTask
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static USwapweaponDirTargetDataTask* CreateSwapweaponDirTargetDataTask(UGameplayAbility* OwningAbility);


	virtual void Activate() override;
	UPROPERTY(BlueprintAssignable)
	FTargetDataSignature ValidData;

	void SendSwapWeaponDirData();

	void OnSwapWeaponDirDataReplicatedCallBack(const FGameplayAbilityTargetDataHandle& Data, FGameplayTag ActivationTag);
};
