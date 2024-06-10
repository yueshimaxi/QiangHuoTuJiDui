// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponInfoDataAsset.h"

FWeaponInfo UWeaponInfoDataAsset::GetWeaponInfo(EProjectileWeaponType weapon_type)
{
	for (FWeaponInfo weapon_info : weapon_info_array)
	{
		if (weapon_info.weapon_type == weapon_type)
		{
			return weapon_info;
		}
	}
	return FWeaponInfo();
}
