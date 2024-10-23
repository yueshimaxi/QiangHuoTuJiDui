// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetDataTask.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "ShotgunTargetDataTask.generated.h"


/**
 * 
 */
UCLASS()
class XUKIT_API UShotgunTargetDataTask : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UShotgunTargetDataTask* CreateShotgunTargetDataTask(UGameplayAbility* OwningAbility, int num = 1);


	UPROPERTY(BlueprintAssignable)
	FTargetDataSignature ValidData;

	int num;

	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

	void SendCurorData();


	void OnCurorDataReplicatedCallBack(const FGameplayAbilityTargetDataHandle& Data, FGameplayTag ActivationTag);
};
