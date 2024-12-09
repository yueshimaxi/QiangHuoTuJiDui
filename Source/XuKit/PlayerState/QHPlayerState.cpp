// Fill out your copyright notice in the Description page of Project Settings.


#include "QHPlayerState.h"

#include "Net/UnrealNetwork.h"
#include "XuKit/XuBPFuncLib.h"
#include "XuKit/AbilitySystem/QHAbilitySystemComponent.h"
#include "XuKit/AbilitySystem/QHAttributeSet.h"
#include "XuKit/AbilitySystem/QHGameplayTags.h"
#include "XuKit/AbilitySystem/Data/WeaponInfoDataAsset.h"
#include "XuKit/Event/EventDataDefine.h"

AQHPlayerState::AQHPlayerState()
{
	NetUpdateFrequency = 100;

	qh_ability_system_component = CreateDefaultSubobject<UQHAbilitySystemComponent>(TEXT("qh_ability_system_component"));
	qh_ability_system_component->SetIsReplicated(true);
	qh_ability_system_component->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	qh_attribute_set = CreateDefaultSubobject<UQHAttributeSet>(TEXT("qh_attributeSet"));

	bReplicates = true;
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





void AQHPlayerState::SetXP(int xp)
{
	XP=xp;
	on_xp_change_delegate.Broadcast(XP);

}

int AQHPlayerState::GetXP()
{
	return XP;
}

void AQHPlayerState::AddToXP(int xp)
{
	XP+=xp;
	on_xp_change_delegate.Broadcast(XP);
}

void AQHPlayerState::OnRep_XP(int oldValue)
{
	on_xp_change_delegate.Broadcast(XP);
	
}
 
void AQHPlayerState::SetPlayerLevel(int level)
{
	PlayerLevel=level;
	on_level_change_delegate.Broadcast(PlayerLevel);
}

int AQHPlayerState::GetPlayerLevel()
{
	return PlayerLevel;
}
void AQHPlayerState::AddPlayerLevel(int level)
{
	PlayerLevel+=level;
	on_level_change_delegate.Broadcast(PlayerLevel);
}



void AQHPlayerState::OnRep_PlayerLevel(int oldValue)
{
	on_level_change_delegate.Broadcast(PlayerLevel);
}
