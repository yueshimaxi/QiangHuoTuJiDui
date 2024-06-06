// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XuKit/Actor/Weapon/Weapon.h"
#include "ProjectionWeapon.generated.h"

class ACasing;
class AProjectile;
/**
 * 
 */
UCLASS()
class XUKIT_API AProjectionWeapon : public AWeapon
{
	GENERATED_BODY()

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
	
};
