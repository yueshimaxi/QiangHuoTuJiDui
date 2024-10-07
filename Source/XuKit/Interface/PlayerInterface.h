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
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void AddXP(int xp);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	int GetXP();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void LevelUp();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void AddToLevel(int AddLevel);


	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	int FindLevelForXP(int XP);


	
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void ReloadAmmo();
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void SwapWeapon(bool swapWeaponForward);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Interact();

	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void DropWeapon();
};
