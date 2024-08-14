// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "QHAbilitySystemComponent.generated.h"
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags,const FGameplayTagContainer&);
DECLARE_MULTICAST_DELEGATE_OneParam(AbilityGiven,UQHAbilitySystemComponent*);
DECLARE_DELEGATE_OneParam(FForEachAbility,FGameplayAbilitySpec&);
/**
 * 
 */
UCLASS()
class XUKIT_API UQHAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	FEffectAssetTags OnEffectTags;
	AbilityGiven AbilityGivenDelegate;
	bool bAbilityGiven = false;
	void AbilitySystemComponentInfoSet();
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* abs, const FGameplayEffectSpec& effect_spec, FActiveGameplayEffectHandle active_effect_handle);

	
	void AddCharactorAbilities(TArray<TSubclassOf<UGameplayAbility>>& startUpAbilities);

	
	void AbilityInputTagPressed(FGameplayTag ActionTag);
	void AbilityInputTagHeld(FGameplayTag ActionTag);
	void AbilityInputTagReleased(FGameplayTag ActionTag);

};
