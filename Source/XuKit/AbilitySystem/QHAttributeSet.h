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

public:
	UPROPERTY(ReplicatedUsing=OnRep_Health, BlueprintReadOnly, Category="Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UQHAttributeSet, Health);
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& oldData) const;
	
	UPROPERTY(ReplicatedUsing=OnRep_MaxHealth, BlueprintReadOnly, Category="Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UQHAttributeSet, MaxHealth);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& oldData) const;
};
