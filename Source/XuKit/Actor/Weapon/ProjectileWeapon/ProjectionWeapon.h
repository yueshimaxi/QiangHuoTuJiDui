// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XuKit/AbilitySystem/Data/WeaponInfoDataAsset.h"
#include "XuKit/Actor/Weapon/Weapon.h"
#include "ProjectionWeapon.generated.h"

enum class EProjectileWeaponType:uint8;
enum class EAmmoType:uint8;
class ACasing;
class AProjectile;
/**
 * 
 */
UCLASS()
class XUKIT_API AProjectionWeapon : public AWeapon
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void OnWeaponStateSet() override;

public:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "AInitInfo")
	TSubclassOf<AProjectile> projectionClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "AInitInfo")
	TObjectPtr<UParticleSystem> MuzzleFlashEffect;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "AInitInfo")
	TObjectPtr<USoundBase> FireSound;

	UPROPERTY(EditAnywhere, Category = "AInitInfo")
	TSubclassOf<ACasing> casingClass;

	//子弹生成位置
	UFUNCTION(BlueprintCallable,BlueprintPure)
	FVector GetProjectileSpawnLocation();

	//弹壳生成位置
	FVector GetCasingSpawnLocation();

	UPROPERTY(EditAnywhere, Category="AInitInfo", ReplicatedUsing=OnRep_Ammo)
	int Ammo = 30;



	void Fire();


	void SpendAmmo();

	UFUNCTION()
	void OnRep_Ammo();

	void SetHUDAmmo();

	bool isEmptyAmmo();


	//换弹夹
	void ReloadAmmo();

	int GetCurAmmo();

	UPROPERTY(EditAnywhere, Category="AInitInfo")
	EProjectileWeaponType weaponType;

	UPROPERTY()
	FWeaponInfo weapon_info;

	bool bInitData=false;
	void InitData();
	
};
