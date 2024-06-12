#include "SwapweaponDirTargetDataTask.h"

#include "AbilitySystemComponent.h"
#include "XuKit/XuBPFuncLib.h"
#include "XuKit/AbilitySystem/Ability/QHGameplayAbility.h"
#include "XuKit/Character/PlayerCharacter.h"


USwapweaponDirTargetDataTask* USwapweaponDirTargetDataTask::CreateSwapweaponDirTargetDataTask(UGameplayAbility* OwningAbility)
{
	USwapweaponDirTargetDataTask* MyObj = NewAbilityTask<USwapweaponDirTargetDataTask>(OwningAbility);
	return MyObj;

}

void USwapweaponDirTargetDataTask::Activate()
{
	if (IsLocallyControlled())
	{
		SendSwapWeaponDirData();
	}
	else
	{
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(), GetActivationPredictionKey()).AddUObject(this, &USwapweaponDirTargetDataTask::OnSwapWeaponDirDataReplicatedCallBack);
		bool CalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(), GetActivationPredictionKey());
		if (!CalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}


void USwapweaponDirTargetDataTask::SendSwapWeaponDirData()
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());

	APlayerController* player_controller = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult curorHitResult;
	player_controller->GetHitResultUnderCursor(ECC_Visibility, false, curorHitResult);

	bool bSwapWeaponDir = false;
	if (APlayerCharacter* player_character= Cast<APlayerCharacter>(player_controller->GetPawn()))
	{
		bSwapWeaponDir=player_character->SwapWeapon_forward;
	}
	
	FGameplayAbilityTargetDataHandle AbilityTargetDataHandle;
	FSwapWeaponDirGameplayAbilityTargetData* hitData = new FSwapWeaponDirGameplayAbilityTargetData();
	hitData->bSwapForward = bSwapWeaponDir;
	AbilityTargetDataHandle.Add(hitData);

	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(),
		AbilityTargetDataHandle, FGameplayTag(), AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(AbilityTargetDataHandle);
	}
}

void USwapweaponDirTargetDataTask::OnSwapWeaponDirDataReplicatedCallBack(const FGameplayAbilityTargetDataHandle& Data, FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());
	XuPRINT(TEXT("OnSwapWeaponDirDataReplicatedCallBack"));
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(Data);
	}
}
