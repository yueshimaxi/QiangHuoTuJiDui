// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QHAbilityBPLibrary.generated.h"

class UCharactorClassInfo;
class UAbilitySystemComponent;
class UAttributeSet;
struct FGameplayEffectContextHandle;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()
	FWidgetControllerParams(){}
	FWidgetControllerParams(APlayerController* PC,APlayerState* PS,UAbilitySystemComponent* ASC,UAttributeSet* AS)
	:PlayerController(PC),PlayerState(PS),AbilitySystemComponent(ASC),AttributeSet(AS){}
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;	
};
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

	UFUNCTION(BlueprintPure, Category="AuraAbilityLibrary", meta=(WorldContext="WorldContextObject"))
	static FWidgetControllerParams GetFWidgetControllerParams(UObject* WorldContextObject);

};
