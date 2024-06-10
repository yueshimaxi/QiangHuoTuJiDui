// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectionWeapon.h"

#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "XuKit/PlayerState/QHPlayerState.h"
#include "XuKit/UI/UIMgr.h"
#include "XuKit/UI/IUIBase/UIPlayerHUD.h"

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
	if (Cast<ACharacter>(GetOwner())->IsLocallyControlled())
	{
		SetHUDAmmo();
	}
}

void AProjectionWeapon::SetHUDAmmo()
{
	UUIPlayerHUD* playerHUD = GetWorld()->GetGameInstance()->GetSubsystem<UUIMgr>()->GetUI<UUIPlayerHUD>();
	if (playerHUD)
	{
		int allBackpackAmmo = Cast<ACharacter>(GetOwner())->GetPlayerState<AQHPlayerState>()->GetAmmoNum(ammoType);
		playerHUD->SetHUDAmmo(Ammo, allBackpackAmmo);
	}
}

bool AProjectionWeapon::isEmptyAmmo()
{
	return Ammo <= 0;
}

void AProjectionWeapon::ReloadAmmo()
{
	int allBackpackAmmo = Cast<ACharacter>(GetOwner())->GetPlayerState<AQHPlayerState>()->GetAmmoNum(ammoType);
	if (allBackpackAmmo > 0)
	{
		int needAmmo = MaxAmmo - Ammo;
		if (allBackpackAmmo >= needAmmo)
		{
			Ammo = MaxAmmo;
			Cast<ACharacter>(GetOwner())->GetPlayerState<AQHPlayerState>()->AddAmmoNum(ammoType, -needAmmo);
		}
		else
		{
			Ammo += allBackpackAmmo;
			Cast<ACharacter>(GetOwner())->GetPlayerState<AQHPlayerState>()->AddAmmoNum(ammoType, -allBackpackAmmo);
		}
	}
	if (Cast<ACharacter>(GetOwner())->IsLocallyControlled())
	{
		SetHUDAmmo();
	}
}

int AProjectionWeapon::GetCurAmmo()
{
	return Ammo;
}
