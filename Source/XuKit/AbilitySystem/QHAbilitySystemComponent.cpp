// Fill out your copyright notice in the Description page of Project Settings.


#include "QHAbilitySystemComponent.h"

#include "Ability/QHGameplayAbility.h"

void UQHAbilitySystemComponent::AddCharactorAbilities(TArray<TSubclassOf<UGameplayAbility>>& startUpAbilities)
{
	for (TSubclassOf<UGameplayAbility> ability : startUpAbilities)
	{
		if (ability)
		{
			FGameplayAbilitySpec spec(ability, 1, INDEX_NONE, this);
			if (UQHGameplayAbility* qhAbility = Cast<UQHGameplayAbility>(spec.Ability))
			{
				spec.DynamicAbilityTags.AddTag(qhAbility->start_up_input_ability_tag);
				GiveAbility(spec);
			}
		}
	}
}

void UQHAbilitySystemComponent::AbilityInputTagPressed(FGameplayTag ActionTag)
{
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
