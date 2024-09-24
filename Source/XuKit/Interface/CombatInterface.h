// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "XuKit/AbilitySystem/Data/CharactorClassInfo.h"
#include "XuKit/Actor/Weapon/Weapon.h"
#include "CombatInterface.generated.h"

class AProjectionWeapon;

USTRUCT(BlueprintType, Blueprintable)
struct FTaggedMontage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Montage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag MontageTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag SocketTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* ImpactSound;
	
};

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

	virtual void Die();

	virtual bool IsDead();

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	AProjectionWeapon* get_cur_projection_weapon();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	ECharactorClass GetCharactorClass();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TArray<FTaggedMontage> GetTaggedMontages();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FTaggedMontage GetTaggedMontageByTag(FGameplayTag tag);
	
};
