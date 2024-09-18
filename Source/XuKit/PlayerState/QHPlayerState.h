// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "QHPlayerState.generated.h"

class ULevelUpInfoDataAsset;
enum class EAmmoType;
class UQHAttributeSet;
class UQHAbilitySystemComponent;
class UAttributeSet;

DECLARE_MULTICAST_DELEGATE_OneParam(FPlayerStateChangeDelegate, int);

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


	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfoDataAsset> LevelUpInfoDataAsset;

	
	UPROPERTY()
	TMap<EAmmoType, int> ammo_map;

	void SpendAmmo(EAmmoType ammo_type);

	int GetAmmoNum(EAmmoType ammo_type);

	void AddAmmoNum(EAmmoType ammo_type, int num);


	FPlayerStateChangeDelegate on_xp_change_delegate;
	FPlayerStateChangeDelegate on_level_change_delegate;
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_XP)
	int XP=0;
	void SetXP(int xp);
	int GetXP();
	void AddToXP(int xp);

	UFUNCTION()
	void OnRep_XP(int oldValue);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_PlayerLevel)
	int PlayerLevel = 1;
	void SetPlayerLevel(int level);
	int GetPlayerLevel();
	void AddPlayerLevel(int level);

	UFUNCTION()
	void OnRep_PlayerLevel(int oldValue);
};


