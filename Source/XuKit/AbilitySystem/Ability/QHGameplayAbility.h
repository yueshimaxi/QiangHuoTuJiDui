// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "QHGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UQHGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly,Category = "AInitInfo")
	FGameplayTag start_up_input_ability_tag;
	
	UPROPERTY(EditDefaultsOnly,Category = "AInitInfo")
	FGameplayTag cooldown_tag;

	
};
