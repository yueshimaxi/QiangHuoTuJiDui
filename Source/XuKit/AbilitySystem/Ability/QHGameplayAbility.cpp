// Fill out your copyright notice in the Description page of Project Settings.


#include "QHGameplayAbility.h"

bool FSwapWeaponDirGameplayAbilityTargetData::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << bSwapForward;

	bOutSuccess = true;
	return true;
}
