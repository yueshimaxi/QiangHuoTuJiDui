// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XuKit/Actor/Weapon/Weapon.h"
#include "ProjectionWeapon.generated.h"

enum class EAmmoType;
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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual  void OnWeaponStateSet() override;
	
public:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"),Category = "AInitInfo")
	TSubclassOf<AProjectile> projectionClass;

	UPROPERTY(EditDefaultsOnly, Category = "AInitInfo")
	TObjectPtr<UParticleSystem> MuzzleFlashEffect;

	UPROPERTY(EditDefaultsOnly, Category = "AInitInfo")
	TObjectPtr<USoundBase> FireSound;
	
	UPROPERTY(EditAnywhere, Category = "AInitInfo")
	TSubclassOf<ACasing> casingClass;

	//子弹生成位置
	FVector GetProjectileSpawnLocation();

	//弹壳生成位置
	FVector	GetCasingSpawnLocation();

	UPROPERTY(EditAnywhere, Category="AInitInfo", ReplicatedUsing=OnRep_Ammo)
	int Ammo=30;

	UPROPERTY(EditAnywhere, Category="AInitInfo")
	int MaxAmmo=30;

	void Fire();


	void SpendAmmo();
	
	UFUNCTION()
	void OnRep_Ammo();

	void SetHUDAmmo();

	bool isEmptyAmmo();


	//换弹夹
	void ReloadAmmo();

	int GetCurAmmo();

	UPROPERTY()
	EAmmoType ammoType;

};
