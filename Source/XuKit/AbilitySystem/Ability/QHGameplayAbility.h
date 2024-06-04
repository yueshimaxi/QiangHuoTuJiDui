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
	UPROPERTY(EditDefaultsOnly,Category="InitInfo")
	FGameplayTag start_up_input_ability_tag;
};
