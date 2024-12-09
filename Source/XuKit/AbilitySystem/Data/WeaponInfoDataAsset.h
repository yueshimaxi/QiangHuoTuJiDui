// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "XuKit/Actor/Weapon/Weapon.h"
#include "WeaponInfoDataAsset.generated.h"


USTRUCT(Blueprintable, BlueprintType)
struct FWeaponInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag WeaponTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag WeaponAmmoTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeapon> weapon_class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString weapon_name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString weapon_description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float weapon_damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float weapon_fire_delay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int weapon_clip_size;


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
	FWeaponInfo GetWeaponInfo(FGameplayTag weapontag);
};
