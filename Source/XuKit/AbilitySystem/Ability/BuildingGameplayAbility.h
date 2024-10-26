// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageGameplayAbility.h"
#include "QHGameplayAbility.h"
#include "XuKit/Actor/Building/Building.h"
#include "BuildingGameplayAbility.generated.h"

class AProjectile;
/**
 * 
 */
UCLASS()
class XUKIT_API UBuildingGameplayAbility : public UDamageGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AInitInfo")
	FDataTableRowHandle BuildingRow;
	UFUNCTION(BlueprintNativeEvent, Category = "AInitInfo")
	void StartBuilding();
};
