// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "XuKit/Actor/Weapon/Weapon.h"
#include "WeaponInfoDataAsset.generated.h"

UENUM()
enum class EProjectileWeaponType
{
	pistol,
	AssaultRifle,
	shotGun,
	SMG,
	Rocket,
};

UENUM(Blueprintable,BlueprintType)
enum class EAmmoType
{
	EAmmoType_Pistol,
	EAmmoType_AssaultRifle,
	EAmmoType_ShotGun,
	EAmmoType_Rocket,
	EAmmoType_Max,
};


USTRUCT()
struct FWeaponInfo
{	
	GENERATED_BODY()

	UPROPERTY()
	EProjectileWeaponType weapon_type;

	UPROPERTY()
	TSubclassOf<AWeapon> weapon_class;

	UPROPERTY()
	FString weapon_name;

	UPROPERTY()
	FString weapon_description;

	UPROPERTY()
	int weapon_damage;

	UPROPERTY()
	int weapon_fire_rate;

	UPROPERTY()
	int weapon_clip_size;

	UPROPERTY()
	EAmmoType Ammo_type;
	
};

/**
 * 
 */
UCLASS()
class XUKIT_API UWeaponInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FWeaponInfo> weapon_info_array;

	UFUNCTION()
	FWeaponInfo GetWeaponInfo(EProjectileWeaponType weapon_type);
	
};
