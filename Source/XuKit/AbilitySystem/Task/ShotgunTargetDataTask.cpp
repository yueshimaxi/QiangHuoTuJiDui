// Fill out your copyright notice in the Description page of Project Settings.


#include "ShotgunTargetDataTask.h"

#include "TargetDataTask.h"

#include "AbilitySystemComponent.h"
#include "XuKit/XuBPFuncLib.h"

UShotgunTargetDataTask* UShotgunTargetDataTask::CreateShotgunTargetDataTask(UGameplayAbility* OwningAbility, int num)
{
	UShotgunTargetDataTask* MyObj = NewAbilityTask<UShotgunTargetDataTask>(OwningAbility);
	MyObj->num = num;
	return MyObj;
}

void UShotgunTargetDataTask::Activate()
{
	if (IsLocallyControlled())
	{
		SendCurorData();
	}
	else
	{
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(), GetActivationPredictionKey()).AddUObject(this, &UShotgunTargetDataTask::OnCurorDataReplicatedCallBack);
		bool CalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(), GetActivationPredictionKey());
		if (!CalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UShotgunTargetDataTask::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}

void UShotgunTargetDataTask::SendCurorData()
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());

	APlayerController* player_controller = Ability->GetCurrentActorInfo()->PlayerController.Get();

	FGameplayAbilityTargetDataHandle AbilityTargetDataHandle;
	for (int i = 0; i < num; ++i)
	{
		FGameplayAbilityTargetData_SingleTargetHit* hitData = new FGameplayAbilityTargetData_SingleTargetHit();
		
		FHitResult curorHitResult;
		player_controller->GetHitResultUnderCursor(ECC_Visibility, false, curorHitResult);
		//做一些散弹的偏移
		curorHitResult.Location += FMath::VRand() * 100;
		hitData->HitResult = curorHitResult;
		AbilityTargetDataHandle.Add(hitData);
	}

	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(),
	                                                      AbilityTargetDataHandle, FGameplayTag(), AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(AbilityTargetDataHandle);
	}
	EndTask();
}


void UShotgunTargetDataTask::OnCurorDataReplicatedCallBack(const FGameplayAbilityTargetDataHandle& Data, FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	XuPRINT(TEXT("OnCurorDataReplicatedCallBack"));
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(Data);
	}
	EndTask();
}
