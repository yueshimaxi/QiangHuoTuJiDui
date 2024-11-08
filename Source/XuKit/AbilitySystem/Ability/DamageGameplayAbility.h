// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QHGameplayAbility.h"
#include "DamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UDamageGameplayAbility : public UQHGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "AInitInfo")
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "AInitInfo")
	float damageValue;

	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* targetActor);
};
