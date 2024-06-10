// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "QHPlayerState.generated.h"

enum class EAmmoType;
class UQHAttributeSet;
class UQHAbilitySystemComponent;
class UAttributeSet;


/**
 * 
 */
UCLASS()
class XUKIT_API AQHPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AQHPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet();

	

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UQHAbilitySystemComponent> qh_ability_system_component;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UQHAttributeSet> qh_attribute_set;

	UPROPERTY()
	TMap<EAmmoType,int>	ammo_map;

	void SpendAmmo(EAmmoType ammo_type);

	int GetAmmoNum(EAmmoType ammo_type);

	void AddAmmoNum(EAmmoType ammo_type, int num);
};
