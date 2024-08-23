// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAbilityLibrary.h"

#include "GameplayEffectTypes.h"
#include "QHAbilitySystemComponent.h"
#include "QHAbilityTypes.h"
#include "QHAttributeSet.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "Ability/QHGameplayAbility.h"
#include "Data/CharactorClassInfo.h"
#include "Kismet/GameplayStatics.h"
#include "XuKit/XuBPFuncLib.h"
#include "XuKit/GameMode/QHGameModeBase.h"
#include "XuKit/PlayerController/QHPlayerController.h"
#include "XuKit/PlayerState/QHPlayerState.h"

bool UAuraAbilityLibrary::IsNotFriendly(AActor* ActorA, AActor* ActorB)
{
	bool isPlayer = ActorA->ActorHasTag("Player") && ActorB->ActorHasTag("Player");
	bool isEnemy = ActorA->ActorHasTag("Enemy") && ActorB->ActorHasTag("Enemy");
	return !(isPlayer || isEnemy);
}

bool UAuraAbilityLibrary::IsCriticalHit(const FGameplayEffectContextHandle& effect_contextHandle)
{
	const FQHGameplayEffectContext* effect_context = static_cast<const FQHGameplayEffectContext*>(effect_contextHandle.Get());
	if (effect_context)
	{
		return effect_context->isCriticalHit();
	}
	return false;
}

bool UAuraAbilityLibrary::IsBlockedHit(const FGameplayEffectContextHandle& effect_contextHandle)
{
	const FQHGameplayEffectContext* effect_context = static_cast<const FQHGameplayEffectContext*>(effect_contextHandle.Get());
	if (effect_context)
	{
		return effect_context->isBlockedHit();
	}
	return false;
}

UCharactorClassInfo* UAuraAbilityLibrary::GetCharactorInfoDataAsset(UObject* WorldContextObject)
{
	AGameModeBase* game_mode_base = UGameplayStatics::GetGameMode(WorldContextObject);

	if (game_mode_base == nullptr)return nullptr;

	return Cast<AQHGameModeBase>(game_mode_base)->EnemyInitDataAsset;
}


int UAuraAbilityLibrary::GetRewardXPFromCharactorTypeAndLevel(UObject* WorldContextObject, ECharactorClass CharactorClass, int level)
{
	UCharactorClassInfo* enemy_init_data_asset = GetCharactorInfoDataAsset(WorldContextObject);

	FCharactorInfo charactor_info = enemy_init_data_asset->GetCharactorInfo(CharactorClass);
	int Reward = charactor_info.RewardXP.GetValueAtLevel(level);
	return Reward;
}

FWidgetControllerParams UAuraAbilityLibrary::GetFWidgetControllerParams(UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		AQHPlayerState* qh_PS = PC->GetPawn()->GetPlayerState<AQHPlayerState>();
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

bool UAuraAbilityLibrary::GetSwapWeaponDirFromTargetData(const FGameplayAbilityTargetDataHandle& TargetData, int32 Index)
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

void UAuraAbilityLibrary::GetLiveActorOnSphere(UObject* WorldContextObject, const FVector& Origin, float Radius, TArray<AActor*>& OutActors, TArray<AActor*> IgnoreActors)
{

	FCollisionQueryParams SphereParams;


	SphereParams.AddIgnoredActors(IgnoreActors);

	// query scene to see what we hit
	TArray<FOverlapResult> Overlaps;
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		World->OverlapMultiByObjectType(Overlaps, Origin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);
		for (int32 Idx = 0; Idx < Overlaps.Num(); ++Idx)
		{
			AActor* Overlap = Overlaps[Idx].GetActor();
			bool implementCombatInterface = Overlap->GetClass()->ImplementsInterface(UCombatInterface::StaticClass());

			if (implementCombatInterface && !ICombatInterface::Execute_IsDead(Overlap))
			{
				OutActors.AddUnique(Overlap);
			}
		}
	}
}

void UAuraAbilityLibrary::InitDefaultAttributeActorInfo(UObject* WorldContextObject, int level, ECharactorClass charactor_class, UAbilitySystemComponent* ABS)
{
	UCharactorClassInfo* enemy_init_data_asset = GetCharactorInfoDataAsset(WorldContextObject);

	{
		FGameplayEffectContextHandle effect_context_handle = ABS->MakeEffectContext();
		effect_context_handle.AddSourceObject(WorldContextObject);
		FGameplayEffectSpecHandle effect_spec_handle = ABS->MakeOutgoingSpec(enemy_init_data_asset->GetCharactorInfo(charactor_class).GE_InitPrimaryAttributeClass, level, effect_context_handle);
		ABS->ApplyGameplayEffectSpecToSelf(*effect_spec_handle.Data.Get());
	}
	{
		FGameplayEffectContextHandle effect_context_handle = ABS->MakeEffectContext();
		effect_context_handle.AddSourceObject(WorldContextObject);
		FGameplayEffectSpecHandle effect_spec_handle = ABS->MakeOutgoingSpec(enemy_init_data_asset->GE_InitSecondAttributeClass, level, effect_context_handle);
		ABS->ApplyGameplayEffectSpecToSelf(*effect_spec_handle.Data.Get());
	}
	{
		FGameplayEffectContextHandle effect_context_handle = ABS->MakeEffectContext();
		effect_context_handle.AddSourceObject(WorldContextObject);
		FGameplayEffectSpecHandle effect_spec_handle = ABS->MakeOutgoingSpec(enemy_init_data_asset->GE_InitVitalAttributeClass, level, effect_context_handle);
		ABS->ApplyGameplayEffectSpecToSelf(*effect_spec_handle.Data.Get());
	}
}

void UAuraAbilityLibrary::GiveStartAbilities(UObject* WorldContextObject, int level, ECharactorClass charactor_class, UAbilitySystemComponent* ABS)
{
	UCharactorClassInfo* enemy_init_data_asset = GetCharactorInfoDataAsset(WorldContextObject);
	TArray<TSubclassOf<UGameplayAbility>> startUpAbilities = enemy_init_data_asset->CommonAbilities;
	for (TSubclassOf<UGameplayAbility> ability : startUpAbilities)
	{
		if (ability)
		{
			FGameplayAbilitySpec spec(ability, level, INDEX_NONE);
			ABS->GiveAbility(spec);
		}
	}
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities = enemy_init_data_asset->GetCharactorInfo(charactor_class).DefaultAbilities;
	for (TSubclassOf<UGameplayAbility> ability : DefaultAbilities)
	{
		if (ability)
		{
			FGameplayAbilitySpec spec(ability, level, INDEX_NONE);
			ABS->GiveAbility(spec);
		}
	}
}

FTaggedMontage UAuraAbilityLibrary::GetRandomTagMotageFromArray(UObject* WorldContextObject, const TArray<FTaggedMontage>& Montages)
{
	if (Montages.Num() == 0)return FTaggedMontage();
	int32 index = FMath::RandRange(0, Montages.Num() - 1);
	return Montages[index];
}
