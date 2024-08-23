// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "XuKit/Interface/CombatInterface.h"
#include "AuraAbilityLibrary.generated.h"

enum class ECharactorClass : uint8;
class UQHAbilitySystemComponent;
class AQHPlayerController;
class AQHPlayerState;
class UQHAttributeSet;
struct FGameplayAbilityTargetDataHandle;
class UCharactorClassInfo;
class UAbilitySystemComponent;
class UAttributeSet;
struct FGameplayEffectContextHandle;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()
	FWidgetControllerParams(){}
	FWidgetControllerParams(AQHPlayerController* PC,AQHPlayerState* PS,UQHAbilitySystemComponent* ASC,UQHAttributeSet* AS)
	:qh_PlayerController(PC),qh_PlayerState(PS),qh_AbilitySystemComponent(ASC),qh_AttributeSet(AS){}
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<AQHPlayerController> qh_PlayerController;
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<AQHPlayerState> qh_PlayerState;
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<UQHAbilitySystemComponent> qh_AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<UQHAttributeSet> qh_AttributeSet;	
};
/**
 * 
 */
UCLASS()
class XUKIT_API UAuraAbilityLibrary : public UBlueprintFunctionLibrary
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


	UFUNCTION(BlueprintPure, Category="AuraAbilityLibrary", meta=(WorldContext="WorldContextObject"))
	static bool  GetSwapWeaponDirFromTargetData(const FGameplayAbilityTargetDataHandle& TargetData, int32 Index);

	UFUNCTION(BlueprintCallable, Category="AuraAbilityLibrary", meta=(WorldContext="WorldContextObject"))
	static  void GetLiveActorOnSphere(UObject* WorldContextObject, const FVector& Origin, float Radius, TArray<AActor*>& OutActors,TArray<AActor*> IgnoreActors);
	
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilityLibrary", meta=(WorldContext="WorldContextObject"))
	static void InitDefaultAttributeActorInfo(UObject* WorldContextObject, int level, ECharactorClass charactor_class, UAbilitySystemComponent* ABS);

	UFUNCTION(BlueprintCallable, Category="AuraAbilityLibrary", meta=(WorldContext="WorldContextObject"))
	static void GiveStartAbilities(UObject* WorldContextObject, int level, ECharactorClass charactor_class, UAbilitySystemComponent* ABS);

	UFUNCTION(BlueprintCallable, Category="AuraAbilityLibrary", meta=(WorldContext="WorldContextObject"))
	static FTaggedMontage GetRandomTagMotageFromArray(UObject* WorldContextObject, const TArray<FTaggedMontage>& Montages);

};
