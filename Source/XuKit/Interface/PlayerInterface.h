// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XUKIT_API IPlayerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Player")
	void AddXP(int xp);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Player")
	int GetXP();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Player")
	void LevelUp();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Player")
	void AddToLevel(int AddLevel);


	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Player")
	int FindLevelForXP(int XP);


	
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Player")
	void ReloadAmmo();
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Player")
	void SwapWeapon(bool swapWeaponForward);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Player")
	void Interact();

	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Player")
	void DropWeapon();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Player")
	void EquipWeapon(class AWeapon* weapon);
};
