// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectionWeapon.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "XuKit/XuBPFuncLib.h"
#include "XuKit/AbilitySystem/QHAttributeSet.h"
#include "XuKit/AbilitySystem/QHGameplayTags.h"
#include "XuKit/AbilitySystem/Data/WeaponInfoDataAsset.h"
#include "XuKit/Character/PlayerCharacter.h"
#include "XuKit/Data/DataMgr.h"
#include "XuKit/Data/IDatabase/WeaponConfigDatabase.h"
#include "XuKit/Event/EventDataDefine.h"
#include "XuKit/Event/EventMgr.h"
#include "XuKit/GameMode/QHGameModeBase.h"
#include "XuKit/PlayerState/QHPlayerState.h"
#include "XuKit/UI/UIMgr.h"
#include "XuKit/UI/IUIBase/UIPlayerHUD.h"


void AProjectionWeapon::BeginPlay()
{
	Super::BeginPlay();

	InitData();
}

void AProjectionWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AProjectionWeapon, PrimaryClipAmmo);
	DOREPLIFETIME(AProjectionWeapon, MaxPrimaryClipAmmo);
}

void AProjectionWeapon::OnWeaponStateSet()
{
	Super::OnWeaponStateSet();
	if (weapon_state == EWeaponState::EWS_Equiped)
	{
		if (GetOwner() && Cast<ACharacter>(GetOwner())->IsLocallyControlled())
		{
			SetHUDAmmo();
		};
	}
}

FVector AProjectionWeapon::GetProjectileSpawnLocation()
{
	FVector AmmoSocketLocation = weapon_mesh_component->GetSocketLocation(FName("AmmoSocket"));
	return AmmoSocketLocation;
}

FVector AProjectionWeapon::GetCasingSpawnLocation()
{
	FVector AmmoEjectLocation = weapon_mesh_component->GetSocketLocation(FName("AmmoEjectSocket"));
	return AmmoEjectLocation;
}

void AProjectionWeapon::OnRep_PrimaryClipAmmo(int32 OldPrimaryClipAmmo)
{
	OnPrimaryClipAmmoChanged.Broadcast(OldPrimaryClipAmmo, PrimaryClipAmmo);
	if (GetOwner() && Cast<ACharacter>(GetOwner())->IsLocallyControlled())
	{
		SetHUDAmmo();
	}
}

void AProjectionWeapon::OnRep_MaxPrimaryClipAmmo(int32 OldMaxPrimaryClipAmmo)
{
	OnMaxPrimaryClipAmmoChanged.Broadcast(OldMaxPrimaryClipAmmo, MaxPrimaryClipAmmo);
	if (GetOwner() && Cast<ACharacter>(GetOwner())->IsLocallyControlled())
	{
		SetHUDAmmo();
	}
}


int32 AProjectionWeapon::GetPrimaryClipAmmo() const
{
	return PrimaryClipAmmo;
}

int32 AProjectionWeapon::GetMaxPrimaryClipAmmo() const
{
	return MaxPrimaryClipAmmo;
}

void AProjectionWeapon::SetPrimaryClipAmmo(int32 NewPrimaryClipAmmo)
{
	int32 OldPrimaryClipAmmo = PrimaryClipAmmo;
	PrimaryClipAmmo = NewPrimaryClipAmmo;
	OnPrimaryClipAmmoChanged.Broadcast(OldPrimaryClipAmmo, PrimaryClipAmmo);
	if (GetOwner() && Cast<ACharacter>(GetOwner())->IsLocallyControlled())
	{
		SetHUDAmmo();
	}
}

void AProjectionWeapon::SetMaxPrimaryClipAmmo(int32 NewMaxPrimaryClipAmmo)
{
	int32 OldMaxPrimaryClipAmmo = MaxPrimaryClipAmmo;
	MaxPrimaryClipAmmo = NewMaxPrimaryClipAmmo;
	OnMaxPrimaryClipAmmoChanged.Broadcast(OldMaxPrimaryClipAmmo, MaxPrimaryClipAmmo);
	if (GetOwner() && Cast<ACharacter>(GetOwner())->IsLocallyControlled())
	{
		SetHUDAmmo();
	}
}


void AProjectionWeapon::SetHUDAmmo()
{
	UFreshHUDEventData* fresh_hud_event = NewObject<UFreshHUDEventData>();
	UXuBPFuncLib::GetEventManager(GetWorld())->BroadcastEvent(EXuEventType::FreshHUD, fresh_hud_event);
}


void AProjectionWeapon::ReloadAmmo()
{
	if (AQHPlayerState* playerState = Cast<ACharacter>(GetOwner())->GetPlayerState<AQHPlayerState>())
	{
		int allBackpackAmmo = GetCurReserveAmmo();
		if (allBackpackAmmo > 0)
		{
			int needAmmo = weapon_info.weapon_clip_size - GetPrimaryClipAmmo();
			int num = 0;
			if (allBackpackAmmo >= needAmmo)
			{
				num = -needAmmo;
				SetPrimaryClipAmmo(weapon_info.weapon_clip_size);
				
			}
			else
			{
				num = -allBackpackAmmo;
				SetPrimaryClipAmmo(GetPrimaryClipAmmo() + allBackpackAmmo);
			}
			//创建gameplayeffect 并且设置modfi，然后应用
			APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(GetOwner());
			if (playerCharacter)
			{
				UGameplayEffect* GEAmmo = NewObject<UGameplayEffect>(GetTransientPackage(), FName(TEXT("Ammo")));
				GEAmmo->DurationPolicy = EGameplayEffectDurationType::Instant;
				int32 Idx = GEAmmo->Modifiers.Num();
				GEAmmo->Modifiers.SetNum(Idx + 1);

				FGameplayModifierInfo& InfoPrimaryAmmo = GEAmmo->Modifiers[Idx];
				InfoPrimaryAmmo.ModifierMagnitude = FScalableFloat(num);
				InfoPrimaryAmmo.ModifierOp = EGameplayModOp::Additive;
				InfoPrimaryAmmo.Attribute = UQHAttributeSet::GetReserveAmmoAttributeFromTag(WeaponTag);
				
				
				playerCharacter->GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(GEAmmo,0, playerCharacter->GetAbilitySystemComponent()->MakeEffectContext());
			}
		}
		if (Cast<ACharacter>(GetOwner())->IsLocallyControlled())
		{
			SetHUDAmmo();
		}
	}
}


void AProjectionWeapon::InitData()
{
	if (bInitData)
	{
		return;
	}
	weapon_info = UXuBPFuncLib::GetDataManager(GetWorld())->GetWeaponConfigDataBase()->GetWeaponInfo(WeaponTag);
	SetPrimaryClipAmmo(weapon_info.weapon_clip_size);
}

int AProjectionWeapon::GetCurReserveAmmo()
{
	if (AQHPlayerState* playerState = Cast<ACharacter>(GetOwner())->GetPlayerState<AQHPlayerState>())
	{
		return playerState->qh_attribute_set->GetReserveAmmoAttributeFromTag(WeaponTag).GetGameplayAttributeData(playerState->qh_attribute_set)->GetCurrentValue();
	}
	return 0;
}
