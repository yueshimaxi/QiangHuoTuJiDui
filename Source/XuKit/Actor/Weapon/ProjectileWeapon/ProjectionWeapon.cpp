// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectionWeapon.h"

#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "XuKit/AbilitySystem/Data/WeaponInfoDataAsset.h"
#include "XuKit/Data/DataMgr.h"
#include "XuKit/Data/IDatabase/WeaponConfigDatabase.h"
#include "XuKit/GameMode/QHGameModeBase.h"
#include "XuKit/PlayerState/QHPlayerState.h"
#include "XuKit/UI/UIMgr.h"
#include "XuKit/UI/IUIBase/UIPlayerHUD.h"

void AProjectionWeapon::BeginPlay()
{
	Super::BeginPlay();

	weapon_info = GetWorld()->GetSubsystem<UDataMgr>()->GetWeaponConfigDataBase()->GetWeaponInfo(weaponType);
	Ammo = weapon_info.weapon_clip_size;
}

void AProjectionWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AProjectionWeapon, Ammo);
}

void AProjectionWeapon::OnWeaponStateSet()
{
	Super::OnWeaponStateSet();
	if (GetOwner() && Cast<ACharacter>(GetOwner())->IsLocallyControlled())
	{
		SetHUDAmmo();
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


void AProjectionWeapon::Fire()
{
	SpendAmmo();
}


void AProjectionWeapon::SpendAmmo()
{
	if (Ammo > 0)
	{
		Ammo -= 1;
	}
	else
	{
		ReloadAmmo();
	}
	if (Cast<ACharacter>(GetOwner())->IsLocallyControlled())
	{
		SetHUDAmmo();
	}
}

void AProjectionWeapon::OnRep_Ammo()
{
	if (GetOwner() && Cast<ACharacter>(GetOwner())->IsLocallyControlled())
	{
		SetHUDAmmo();
	}
}

void AProjectionWeapon::SetHUDAmmo()
{
	if (UUIPlayerHUD* playerHUD = GetWorld()->GetGameInstance()->GetSubsystem<UUIMgr>()->GetUI<UUIPlayerHUD>())
	{
		if (AQHPlayerState* playerState = Cast<ACharacter>(GetOwner())->GetPlayerState<AQHPlayerState>())
		{
			int allBackpackAmmo = playerState->GetAmmoNum(weapon_info.Ammo_type);
			playerHUD->SetHUDAmmo(Ammo, allBackpackAmmo);
		}
	}
}

bool AProjectionWeapon::isEmptyAmmo()
{
	return Ammo <= 0;
}

void AProjectionWeapon::ReloadAmmo()
{
	if (AQHPlayerState* playerState = Cast<ACharacter>(GetOwner())->GetPlayerState<AQHPlayerState>())
	{
		int allBackpackAmmo = playerState->GetAmmoNum(weapon_info.Ammo_type);
		if (allBackpackAmmo > 0)
		{
			int needAmmo = weapon_info.weapon_clip_size - Ammo;
			if (allBackpackAmmo >= needAmmo)
			{
				Ammo = weapon_info.weapon_clip_size;
				playerState->AddAmmoNum(weapon_info.Ammo_type, -needAmmo);
			}
			else
			{
				Ammo += allBackpackAmmo;
				playerState->AddAmmoNum(weapon_info.Ammo_type, -allBackpackAmmo);
			}
		}
		if (Cast<ACharacter>(GetOwner())->IsLocallyControlled())
		{
			SetHUDAmmo();
		}
	}
}

int AProjectionWeapon::GetCurAmmo()
{
	return Ammo;
}
