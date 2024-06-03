// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "QHAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UQHAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AddCharactorAbilities(TArray<TSubclassOf<UGameplayAbility>>& startUpAbilities);

	
	void AbilityInputTagPressed(FGameplayTag ActionTag);
	void AbilityInputTagHeld(FGameplayTag ActionTag);
	void AbilityInputTagReleased(FGameplayTag ActionTag);
};
