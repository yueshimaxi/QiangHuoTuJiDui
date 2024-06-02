// Fill out your copyright notice in the Description page of Project Settings.


#include "QHAttributeSet.h"

UQHAttributeSet::UQHAttributeSet()
{
}

void UQHAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
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
