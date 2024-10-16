// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetDataTask.h"

#include "AbilitySystemComponent.h"
#include "XuKit/XuBPFuncLib.h"

UTargetDataTask* UTargetDataTask::CreateTargetDataTask(UGameplayAbility* OwningAbility)
{
	UTargetDataTask* MyObj = NewAbilityTask<UTargetDataTask>(OwningAbility);
	return MyObj;

}

void UTargetDataTask::Activate()
{
	if (IsLocallyControlled())
	{
		SendCurorData();
	}
	else
	{
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(), GetActivationPredictionKey()).AddUObject(this, &UTargetDataTask::OnCurorDataReplicatedCallBack);
		bool CalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(), GetActivationPredictionKey());
		if (!CalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UTargetDataTask::OnDestroy(bool bInOwnerFinished)
{
	
	Super::OnDestroy(bInOwnerFinished);
	
}

void UTargetDataTask::SendCurorData()
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());

	APlayerController* player_controller = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult curorHitResult;
	player_controller->GetHitResultUnderCursor(ECC_Visibility, false, curorHitResult);

	FGameplayAbilityTargetDataHandle AbilityTargetDataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* hitData = new FGameplayAbilityTargetData_SingleTargetHit();
	hitData->HitResult = curorHitResult;
	AbilityTargetDataHandle.Add(hitData);

	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(),
		AbilityTargetDataHandle, FGameplayTag(), AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(AbilityTargetDataHandle);
	}
	EndTask();
}



void UTargetDataTask::OnCurorDataReplicatedCallBack(const FGameplayAbilityTargetDataHandle& Data, FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());
	XuPRINT(TEXT("OnCurorDataReplicatedCallBack"));
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(Data);
	}
	EndTask();
}
