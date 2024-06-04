// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XuKit/Actor/Weapon/Weapon.h"
#include "ProjectionWeapon.generated.h"

class AProjectile;
/**
 * 
 */
UCLASS()
class XUKIT_API AProjectionWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectile> projectionClass;


	
};
