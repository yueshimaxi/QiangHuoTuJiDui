// Fill out your copyright notice in the Description page of Project Settings.


#include "QHGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "XuKit/Actor/Weapon/ProjectileWeapon/ProjectionWeapon.h"
#include "XuKit/Character/PlayerCharacter.h"

bool FSwapWeaponDirGameplayAbilityTargetData::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << bSwapForward;

	bOutSuccess = true;
	return true;
}




bool UQHGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	// if (bCannotActivateWhileInteracting)
	// {
	// 	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	// 	if (ASC->GetTagCount(InteractingTag) > ASC->GetTagCount(InteractingRemovalTag))
	// 	{
	// 		return false;
	// 	}
	// }
	//
	// if (bSourceObjectMustEqualCurrentWeaponToActivate)
	// {
	// 	APlayerCharacter* Hero = Cast<APlayerCharacter>(ActorInfo->AvatarActor);
	// 	UObject* weapon = ICombatInterface::Execute_get_cur_projection_weapon(Hero);
	// 	if (Hero && weapon && weapon == GetSourceObject(Handle, ActorInfo))
	// 	{
	// 		return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
	// 	}
	// 	else
	// 	{
	// 		return false;
	// 	}
	// }

	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

bool UQHGameplayAbility::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CheckCost(Handle, ActorInfo, OptionalRelevantTags) && GSCheckCost(Handle, *ActorInfo);
}

bool UQHGameplayAbility::GSCheckCost_Implementation(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo& ActorInfo) const
{
	return true;

}

void UQHGameplayAbility::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	GSApplyCost(Handle, *ActorInfo, ActivationInfo);
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}

void UQHGameplayAbility::GSApplyCost_Implementation(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo& ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
}
