// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponInfoDataAsset.h"

FWeaponInfo UWeaponInfoDataAsset::GetWeaponInfo(FGameplayTag weapontag)
{
	for (FWeaponInfo weapon_info : weapon_info_array)
	{
		if (weapon_info.WeaponTag .MatchesTagExact(weapontag))
		{
			return weapon_info;
		}
	}
	return FWeaponInfo();
}
