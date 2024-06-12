// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XuKit/Actor/Weapon/Weapon.h"
#include "CombatInterface.generated.h"

class AProjectionWeapon;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XUKIT_API ICombatInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int GetPlayerLevel();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FVector GetCombatSocketLocation(const FGameplayTag& socketTag);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UpdateFacingTarget(FVector targetLocation);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UAnimMontage* GetHitReactMontage();

	virtual void Die(){};

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsDead();

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	AProjectionWeapon* get_cur_projection_weapon();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	ECharactorClass GetCharactorClass();
	
};
