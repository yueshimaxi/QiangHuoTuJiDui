// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageGameplayAbility.h"
#include "QHGameplayAbility.h"
#include "ProjectileGameplayAbility.generated.h"

class AProjectile;
/**
 * 
 */
UCLASS()
class XUKIT_API UProjectileGameplayAbility : public UDamageGameplayAbility
{
	GENERATED_BODY()


public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile> ProjectileClass;

	

	UFUNCTION(BlueprintCallable, Category="InitInfo")
	void SpawnProjectile(FGameplayTag socketTag,bool overridePitch=false,float pitch=0.0f);
};
