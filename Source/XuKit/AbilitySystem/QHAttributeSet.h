// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "QHAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	AActor* SourceAvaterActor;
	UPROPERTY()
	AController* SourceController;
	UPROPERTY()
	ACharacter* SourceCharacter;
	UPROPERTY()
	UAbilitySystemComponent* SourceASC;
	UPROPERTY()
	AActor* TargetAvaterActor;
	UPROPERTY()
	AController* TargetController;
	UPROPERTY()
	ACharacter* TargetCharacter;
	UPROPERTY()
	UAbilitySystemComponent* TargetASC;
};
/**
 * 
 */
UCLASS()
class XUKIT_API UQHAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:
	UQHAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& EffectProperties);
	
	void ShowDamageText(FEffectProperties props, float damage, bool isCriticalHit, bool isBlockedHit) const;

	void SendXPEvent(FEffectProperties props);

public:
	UPROPERTY(ReplicatedUsing=OnRep_Health, BlueprintReadOnly, Category="Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UQHAttributeSet, Health);

	
	UPROPERTY(ReplicatedUsing=OnRep_MaxHealth, BlueprintReadOnly, Category="Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UQHAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Ammo", ReplicatedUsing = OnRep_PisalReserveAmmo)
	FGameplayAttributeData PisalReserveAmmo;
	ATTRIBUTE_ACCESSORS(UQHAttributeSet, PisalReserveAmmo)

	UPROPERTY(BlueprintReadOnly, Category = "Ammo", ReplicatedUsing = OnRep_MaxPisalReserveAmmo)
	FGameplayAttributeData MaxPisalReserveAmmo;
	ATTRIBUTE_ACCESSORS(UQHAttributeSet, MaxPisalReserveAmmo)

	
	UPROPERTY(BlueprintReadOnly, Category = "Ammo", ReplicatedUsing = OnRep_RifleReserveAmmo)
	FGameplayAttributeData RifleReserveAmmo;
	ATTRIBUTE_ACCESSORS(UQHAttributeSet, RifleReserveAmmo)


	UPROPERTY(BlueprintReadOnly, Category = "Ammo", ReplicatedUsing = OnRep_MaxRifleReserveAmmo)
	FGameplayAttributeData MaxRifleReserveAmmo;
	ATTRIBUTE_ACCESSORS(UQHAttributeSet, MaxRifleReserveAmmo)
	
	// UPROPERTY(BlueprintReadOnly, Category = "Ammo", ReplicatedUsing = OnRep_RocketReserveAmmo)
	// FGameplayAttributeData RocketReserveAmmo;
	// ATTRIBUTE_ACCESSORS(UQHAttributeSet, RocketReserveAmmo)
	//
	//
	// UPROPERTY(BlueprintReadOnly, Category = "Ammo", ReplicatedUsing = OnRep_MaxRocketReserveAmmo)
	// FGameplayAttributeData MaxRocketReserveAmmo;
	// ATTRIBUTE_ACCESSORS(UQHAttributeSet, MaxRocketReserveAmmo)
	//
	//
	// UPROPERTY(BlueprintReadOnly, Category = "Ammo", ReplicatedUsing = OnRep_ShotgunReserveAmmo)
	// FGameplayAttributeData ShotgunReserveAmmo;
	// ATTRIBUTE_ACCESSORS(UQHAttributeSet, ShotgunReserveAmmo)
	//
	//
	//
	// UPROPERTY(BlueprintReadOnly, Category = "Ammo", ReplicatedUsing = OnRep_MaxShotgunReserveAmmo)
	// FGameplayAttributeData MaxShotgunReserveAmmo;
	// ATTRIBUTE_ACCESSORS(UQHAttributeSet, MaxShotgunReserveAmmo)
	


	//meta Attributes
	//Damage
	UPROPERTY(BlueprintReadOnly, Category="Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UQHAttributeSet, IncomingDamage);

	//XP
	UPROPERTY(BlueprintReadOnly, Category="Meta Attributes")
	FGameplayAttributeData InComingXP;
	ATTRIBUTE_ACCESSORS(UQHAttributeSet, InComingXP);

	UPROPERTY(BlueprintReadOnly, Category = "Gold", ReplicatedUsing = OnRep_Gold)
	FGameplayAttributeData Gold;
	ATTRIBUTE_ACCESSORS(UQHAttributeSet, Gold)

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& oldData) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& oldData) const;
	UFUNCTION()
	void OnRep_PisalReserveAmmo(const FGameplayAttributeData& oldData) const;
	UFUNCTION()
	void OnRep_MaxPisalReserveAmmo(const FGameplayAttributeData& oldData) const;
	UFUNCTION()
	void OnRep_RifleReserveAmmo(const FGameplayAttributeData& oldData) const;
	UFUNCTION()
	void OnRep_MaxRifleReserveAmmo(const FGameplayAttributeData& oldData) const;
	// UFUNCTION()
	// void OnRep_RocketReserveAmmo(const FGameplayAttributeData& oldData) const;
	// UFUNCTION()
	// void OnRep_MaxRocketReserveAmmo(const FGameplayAttributeData& oldData) const;
	// UFUNCTION()
	// void OnRep_ShotgunReserveAmmo(const FGameplayAttributeData& oldData) const;
	// UFUNCTION()
	// void OnRep_MaxShotgunReserveAmmo(const FGameplayAttributeData& oldData) const;
	UFUNCTION()
	void OnRep_Gold(const FGameplayAttributeData& oldData) const;
};
