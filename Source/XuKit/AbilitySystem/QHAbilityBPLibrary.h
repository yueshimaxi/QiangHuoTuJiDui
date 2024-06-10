// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QHAbilityBPLibrary.generated.h"

struct FGameplayEffectContextHandle;
/**
 * 
 */
UCLASS()
class XUKIT_API UQHAbilityBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="AuraAbilityLibrary", meta=(WorldContext="WorldContextObject"))
	static bool IsNotFriendly(AActor* ActorA, AActor* ActorB);

	UFUNCTION(BlueprintPure, Category="AuraAbilityLibrary", meta=(WorldContext="WorldContextObject"))
	static bool IsCriticalHit(const FGameplayEffectContextHandle& effect_contextHandle);

	UFUNCTION(BlueprintPure, Category="AuraAbilityLibrary", meta=(WorldContext="WorldContextObject"))
	static bool IsBlockedHit(const FGameplayEffectContextHandle& effect_contextHandle);

	UFUNCTION(BlueprintCallable, Category="AuraAbilityLibrary", meta=(WorldContext="WorldContextObject"))
	static UCharactorClassInfo* GetCharactorInfoDataAsset(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="AuraAbilityLibrary", meta=(WorldContext="WorldContextObject"))
	static int GetRewardXPFromCharactorTypeAndLevel(UObject* WorldContextObject, ECharactorClass CharactorClass, int level);

};
