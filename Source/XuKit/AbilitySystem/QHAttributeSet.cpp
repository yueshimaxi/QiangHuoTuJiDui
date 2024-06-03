// Fill out your copyright notice in the Description page of Project Settings.


#include "QHAttributeSet.h"

#include "Net/UnrealNetwork.h"

UQHAttributeSet::UQHAttributeSet()
{
}

void UQHAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UQHAttributeSet, Health, ELifetimeCondition::COND_None, ELifetimeRepNotifyCondition::REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UQHAttributeSet, MaxHealth, ELifetimeCondition::COND_None, ELifetimeRepNotifyCondition::REPNOTIFY_Always);
}

void UQHAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UQHAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UQHAttributeSet::OnRep_Health(const FGameplayAttributeData& oldData) const
{
	
}

void UQHAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& oldData) const
{
	
}
