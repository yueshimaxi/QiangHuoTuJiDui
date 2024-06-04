// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "XuKit/AbilitySystem/QHGameplayTags.h"

void UDamageGameplayAbility::CauseDamage(AActor* targetActor)
{
	check(targetActor);
	UAbilitySystemComponent* abs = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningActorFromActorInfo());
	FGameplayEffectContextHandle effect_context_handle = abs->MakeEffectContext();
	FGameplayEffectSpecHandle effect_spec_handle = abs->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), effect_context_handle);

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(effect_spec_handle, QHGameplayTags::Get().DamageTag, damageValue);
	abs->ApplyGameplayEffectSpecToTarget(*effect_spec_handle.Data.Get(), UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(targetActor));
}
