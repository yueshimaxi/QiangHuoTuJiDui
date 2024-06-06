// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectionWeapon.h"

FVector AProjectionWeapon::GetProjectileSpawnLocation()
{
	FVector AmmoSocketLocation= weapon_mesh_component->GetSocketLocation(FName("AmmoSocket"));
	return AmmoSocketLocation;
}

FVector AProjectionWeapon::GetCasingSpawnLocation()
{
	FVector AmmoEjectLocation = weapon_mesh_component->GetSocketLocation(FName("AmmoEjectSocket"));
	return AmmoEjectLocation;
}
