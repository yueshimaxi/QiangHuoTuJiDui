// Fill out your copyright notice in the Description page of Project Settings.


#include "QHAbilitySystemComponent.h"

#include "Ability/QHGameplayAbility.h"

void UQHAbilitySystemComponent::AbilitySystemComponentInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UQHAbilitySystemComponent::ClientEffectApplied);

}

void UQHAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* abs, const FGameplayEffectSpec& effect_spec, FActiveGameplayEffectHandle active_effect_handle)
{
	FGameplayTagContainer effect_tags;
	effect_spec.GetAllAssetTags(effect_tags);
	bAbilityGiven=true;
	OnEffectTags.Broadcast(effect_tags);
}

void UQHAbilitySystemComponent::AddCharactorAbilities(TArray<TSubclassOf<UQHGameplayAbility>>& startUpAbilities)
{
	for (TSubclassOf<UQHGameplayAbility> ability : startUpAbilities)
	{
		if (ability)
		{
			FGameplayAbilitySpec spec(ability, 1, static_cast<int>(ability.GetDefaultObject()->AbilityInputID), this);
			if (UQHGameplayAbility* qhAbility = Cast<UQHGameplayAbility>(spec.Ability))
			{
				spec.DynamicAbilityTags.AddTag(qhAbility->start_up_input_ability_tag);
				GiveAbility(spec);
			}
		}
	}
}

void UQHAbilitySystemComponent::AddCharactorPassiveAbilities(TArray<TSubclassOf<UGameplayAbility>>& startUpPassiveAbilities)
{
	for (TSubclassOf<UGameplayAbility> ability : startUpPassiveAbilities)
	{
		if (ability)
		{
			FGameplayAbilitySpec spec(ability, 1, INDEX_NONE, this);
			GiveAbilityAndActivateOnce(spec);

		}
	}
}

void UQHAbilitySystemComponent::AbilityInputTagPressed(FGameplayTag ActionTag)
{
	for (FGameplayAbilitySpec& abilitySpc : ActivatableAbilities.Items)
	{
		if (abilitySpc.DynamicAbilityTags.HasTagExact(ActionTag))
		{
			AbilitySpecInputPressed(abilitySpc);
			if (!abilitySpc.IsActive())
			{
				TryActivateAbility(abilitySpc.Handle);
			}
		}
	}
}

void UQHAbilitySystemComponent::AbilityInputTagHeld(FGameplayTag ActionTag)
{
	for (FGameplayAbilitySpec& abilitySpc : ActivatableAbilities.Items)
	{
		if (abilitySpc.DynamicAbilityTags.HasTagExact(ActionTag))
		{
			AbilitySpecInputPressed(abilitySpc);
			if (!abilitySpc.IsActive())
			{
				TryActivateAbility(abilitySpc.Handle);
			}
		}
	}
}

void UQHAbilitySystemComponent::AbilityInputTagReleased(FGameplayTag ActionTag)
{
	for (FGameplayAbilitySpec abilitySpc : ActivatableAbilities.Items)
	{
		if (abilitySpc.DynamicAbilityTags.HasTagExact(ActionTag))
		{
			AbilitySpecInputReleased(abilitySpc);
		}
	}
}

