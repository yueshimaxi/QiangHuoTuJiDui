// Fill out your copyright notice in the Description page of Project Settings.


#include "QHAbilityBPLibrary.h"

#include "GameplayEffectTypes.h"
#include "QHAbilitySystemComponent.h"
#include "QHAbilityTypes.h"
#include "QHAttributeSet.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "Ability/QHGameplayAbility.h"
#include "Kismet/GameplayStatics.h"
#include "XuKit/XuBPFuncLib.h"
#include "XuKit/Data/CharactorClassInfo.h"
#include "XuKit/GameMode/QHGameModeBase.h"
#include "XuKit/PlayerController/QHPlayerController.h"
#include "XuKit/PlayerState/QHPlayerState.h"

bool UQHAbilityBPLibrary::IsNotFriendly(AActor* ActorA, AActor* ActorB)
{
	bool isPlayer = ActorA->ActorHasTag("Player") && ActorB->ActorHasTag("Player");
	bool isEnemy = ActorA->ActorHasTag("Enemy") && ActorB->ActorHasTag("Enemy");
	return !(isPlayer || isEnemy);
}

bool UQHAbilityBPLibrary::IsCriticalHit(const FGameplayEffectContextHandle& effect_contextHandle)
{
	const FQHGameplayEffectContext* effect_context = static_cast<const FQHGameplayEffectContext*>(effect_contextHandle.Get());
	if (effect_context)
	{
		return effect_context->isCriticalHit();
	}
	return false;
}

bool UQHAbilityBPLibrary::IsBlockedHit(const FGameplayEffectContextHandle& effect_contextHandle)
{
	const FQHGameplayEffectContext* effect_context = static_cast<const FQHGameplayEffectContext*>(effect_contextHandle.Get());
	if (effect_context)
	{
		return effect_context->isBlockedHit();
	}
	return false;
}

UCharactorClassInfo* UQHAbilityBPLibrary::GetCharactorInfoDataAsset(UObject* WorldContextObject)
{
	AGameModeBase* game_mode_base = UGameplayStatics::GetGameMode(WorldContextObject);

	if (game_mode_base == nullptr)return nullptr;

	return Cast<AQHGameModeBase>(game_mode_base)->EnemyInitDataAsset;
}


int UQHAbilityBPLibrary::GetRewardXPFromCharactorTypeAndLevel(UObject* WorldContextObject, ECharactorClass CharactorClass, int level)
{
	UCharactorClassInfo* enemy_init_data_asset = GetCharactorInfoDataAsset(WorldContextObject);

	FCharactorInfo charactor_info = enemy_init_data_asset->GetCharactorInfo(CharactorClass);
	int Reward = charactor_info.RewardXP.GetValueAtLevel(level);
	return Reward;
}

FWidgetControllerParams UQHAbilityBPLibrary::GetFWidgetControllerParams(UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		AQHPlayerState* qh_PS = PC->GetPlayerState<AQHPlayerState>();
		if (qh_PS == nullptr)
		{
			return FWidgetControllerParams();
		}
		AQHPlayerController* qh_PC = Cast<AQHPlayerController>(PC);
		UQHAbilitySystemComponent* qh_ASC = Cast<UQHAbilitySystemComponent>(qh_PS->GetAbilitySystemComponent());
		UQHAttributeSet* qh_AS = Cast<UQHAttributeSet>(qh_PS->GetAttributeSet());
		return FWidgetControllerParams(qh_PC, qh_PS, qh_ASC, qh_AS);
	}
	return FWidgetControllerParams();
}

bool UQHAbilityBPLibrary::GetSwapWeaponDirFromTargetData(const FGameplayAbilityTargetDataHandle& TargetData, int32 Index)
{
	if (TargetData.Data.IsValidIndex(Index))
	{
		FGameplayAbilityTargetData* Data = TargetData.Data[Index].Get();
		//FGameplayAbilityTargetData转换成FSwapWeaponDirGameplayAbilityTargetData
		if (Data)
		{
			const FSwapWeaponDirGameplayAbilityTargetData* HitResultPtr = static_cast<const FSwapWeaponDirGameplayAbilityTargetData*>(Data);
			if (HitResultPtr)
			{
				XuPRINT(FString::Printf(TEXT("GetSwapWeaponDirFromTargetData: %d"), HitResultPtr->bSwapForward));
				return HitResultPtr->bSwapForward;
			}
		}
	}
	XuPRINT(FString::Printf(TEXT("GetSwapWeaponDirFromTargetData failed")));
	return false;
}
