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


USTRUCT(Blueprintable,BlueprintType)
struct FWeaponInfo
{	
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EProjectileWeaponType weapon_type;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AWeapon> weapon_class;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString weapon_name;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString weapon_description;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float weapon_damage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float weapon_fire_rate;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int weapon_clip_size;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
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
