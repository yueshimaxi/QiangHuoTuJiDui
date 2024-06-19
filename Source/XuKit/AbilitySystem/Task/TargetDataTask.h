// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetDataSignature,const FGameplayAbilityTargetDataHandle&,data);

/**
 * 
 */
UCLASS()
class XUKIT_API UTargetDataTask : public UAbilityTask
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UTargetDataTask* CreateTargetDataTask(UGameplayAbility* OwningAbility);


	virtual void Activate() override;
	UPROPERTY(BlueprintAssignable)
	FTargetDataSignature ValidData;

	void SendCurorData();


	void OnCurorDataReplicatedCallBack(const FGameplayAbilityTargetDataHandle& Data, FGameplayTag ActivationTag);
};
