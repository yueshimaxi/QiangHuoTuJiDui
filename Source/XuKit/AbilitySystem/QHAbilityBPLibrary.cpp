// Fill out your copyright notice in the Description page of Project Settings.


#include "QHAbilityBPLibrary.h"

#include "GameplayEffectTypes.h"
#include "QHAbilityTypes.h"
#include "Kismet/GameplayStatics.h"
#include "XuKit/Data/CharactorClassInfo.h"
#include "XuKit/GameMode/QHGameModeBase.h"

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
	int Reward= charactor_info.RewardXP.GetValueAtLevel(level);
	return Reward;
}
