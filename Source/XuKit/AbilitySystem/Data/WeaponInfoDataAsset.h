// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "XuKit/Actor/Weapon/Weapon.h"
#include "WeaponInfoDataAsset.generated.h"

UENUM()
enum class EProjectileWeaponType:uint8
{
	pistol,
	AssaultRifle,
	shotGun,
	SMG,
	Rocket,
};

UENUM(Blueprintable, BlueprintType)
enum class EAmmoType:uint8
{
	EAmmoType_Pistol,        // 手枪弹药
	EAmmoType_AssaultRifle,  // 突击步枪弹药
	EAmmoType_ShotGun,       // 霰弹枪弹药
	EAmmoType_Rocket,        // 火箭弹药
	EAmmoType_LaserGun,      // 激光枪弹药
};


USTRUCT(Blueprintable, BlueprintType)
struct FWeaponInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EProjectileWeaponType weapon_type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeapon> weapon_class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString weapon_name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString weapon_description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float weapon_damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float weapon_fire_rate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int weapon_clip_size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAmmoType Ammo_type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* weapon_icon;
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
