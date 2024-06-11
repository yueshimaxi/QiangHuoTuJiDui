// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "WaitCoolDownChange.generated.h"
class UAbilitySystemComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCoolDownSignature, float, TimeRemaining);

/**
 * 
 */
UCLASS()
class XUKIT_API UWaitCoolDownChange : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintAssignable)
	FCoolDownSignature StartCoolDown;
	UPROPERTY(BlueprintAssignable)
	FCoolDownSignature EndCoolDown;	
	
	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly="true"))
	static UWaitCoolDownChange* WaitForCoolDownChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag InCoolDownTag);

	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent>	ASC;
	UPROPERTY()
	FGameplayTag CoolDownTag;

	UFUNCTION()
	void OnGameplayTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	bool GetCooldownRemainingForTag(FGameplayTag CooldownTag, float & TimeRemaining, float & CooldownDuration);
};
