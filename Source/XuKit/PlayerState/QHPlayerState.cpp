// Fill out your copyright notice in the Description page of Project Settings.


#include "QHPlayerState.h"

#include "XuKit/Ability/QHAbilitySystemComponent.h"
#include "XuKit/Ability/QHAttributeSet.h"

AQHPlayerState::AQHPlayerState()
{
	NetUpdateFrequency = 100;

	qh_ability_system_component = CreateDefaultSubobject<UQHAbilitySystemComponent>(TEXT("qh_ability_system_component"));
	qh_ability_system_component->SetIsReplicated(true);
	qh_ability_system_component->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	qh_attribute_set = CreateDefaultSubobject<UQHAttributeSet>(TEXT("qh_attributeSet"));
}

void AQHPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

UAbilitySystemComponent* AQHPlayerState::GetAbilitySystemComponent() const
{
	return qh_ability_system_component;

}

UAttributeSet* AQHPlayerState::GetAttributeSet()
{
	return qh_attribute_set;

}
