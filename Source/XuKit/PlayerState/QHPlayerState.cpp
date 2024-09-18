// Fill out your copyright notice in the Description page of Project Settings.


#include "QHPlayerState.h"

#include "Net/UnrealNetwork.h"
#include "XuKit/XuBPFuncLib.h"
#include "XuKit/AbilitySystem/QHAbilitySystemComponent.h"
#include "XuKit/AbilitySystem/QHAttributeSet.h"
#include "XuKit/AbilitySystem/Data/WeaponInfoDataAsset.h"

AQHPlayerState::AQHPlayerState()
{
	NetUpdateFrequency = 100;

	qh_ability_system_component = CreateDefaultSubobject<UQHAbilitySystemComponent>(TEXT("qh_ability_system_component"));
	qh_ability_system_component->SetIsReplicated(true);
	qh_ability_system_component->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	qh_attribute_set = CreateDefaultSubobject<UQHAttributeSet>(TEXT("qh_attributeSet"));
	AddAmmoNum(EAmmoType::EAmmoType_Pistol, 30);
	AddAmmoNum(EAmmoType::EAmmoType_AssaultRifle, 100);

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



void AQHPlayerState::SpendAmmo(EAmmoType ammo_type)
{
	if (ammo_map.Contains(ammo_type))
	{
		int ammoNum = ammo_map[ammo_type];
		if (ammoNum > 0)
		{
			ammoNum -= 1;
		}
		else
		{
			//todo: show no ammo
		}
	}
	else
	{
		ammo_map.Add(ammo_type, 0);
		//todo: show no ammo
	}
}

int AQHPlayerState::GetAmmoNum(EAmmoType ammo_type)
{
	if (ammo_map.Contains(ammo_type))
	{
		return ammo_map[ammo_type];
	}
	else
	{
		ammo_map.Add(ammo_type, 0);
		return 0;
	}
}

void AQHPlayerState::AddAmmoNum(EAmmoType ammo_type, int num)
{
	if (ammo_map.Contains(ammo_type))
	{
		//最小为0
		ammo_map[ammo_type] = FMath::Max(ammo_map[ammo_type] + num, 0);
	}
	else
	{
		ammo_map.Add(ammo_type, num);
	}
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