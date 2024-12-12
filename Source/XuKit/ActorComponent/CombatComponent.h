// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


class AProjectionWeapon;
class AWeapon;
class APlayerCharacter;

USTRUCT()
struct  FGSHeroInventory
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray<AWeapon*> Weapons;

	// Consumable items

	// Passive items like armor

	// Door keys

	// Etc
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class XUKIT_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCombatComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY()
	AWeapon* CurrentWeapon;


	int max_Projectile_Weapon_Num = 5;

public:
	UPROPERTY()
	APlayerCharacter* owner_character;


	AWeapon* GetCurProjectionWeapon();


	UFUNCTION(Server, Reliable)
	void Server_EquipWeapon(AWeapon* weapon);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_EquipWeapon(AWeapon* weapon);
	
	void EquipWeapon(AWeapon* weapon);


	void UnEquipCurrentWeapon();


	void DropWeapon(AWeapon* weapon);

	void SwapWeapon(bool forward);
	UFUNCTION(Server, Reliable)
	void Server_SwapWeapon(bool forward);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SwapWeapon(bool forward);

	int currentIndex=0;

	UPROPERTY(Replicated)
	AWeapon* overlaping_weapon;
	
	UFUNCTION(BlueprintCallable, Category = "GASShooter|Inventory")
	void AddWeaponToInventory(AWeapon* NewWeapon, bool bEquipWeapon = false);
	UFUNCTION(Server,Reliable)
	void Server_AddWeaponToInventory(AWeapon* NewWeapon, bool bEquipWeapon = false);
	UFUNCTION(NetMulticast,Reliable)
	void Multicast_AddWeaponToInventory(AWeapon* NewWeapon, bool bEquipWeapon = false);
	
	// Removes a weapon from the inventory.
	// Returns true if the weapon exists and was removed. False if the weapon didn't exist in the inventory.
	UFUNCTION(BlueprintCallable, Category = "GASShooter|Inventory")
	void RemoveWeaponFromInventory(AWeapon* WeaponToRemove);
	UFUNCTION(Server,Reliable)
	void Server_RemoveWeaponFromInventory(AWeapon* WeaponToRemove);
	UFUNCTION(NetMulticast,Reliable)
	void Multicast_RemoveWeaponFromInventory(AWeapon* WeaponToRemove);
	
	UFUNCTION(BlueprintCallable, Category = "GASShooter|Inventory")
	void RemoveAllWeaponsFromInventory();
	UFUNCTION(Server,Reliable)
	void Server_RemoveAllWeaponsFromInventory();
	UFUNCTION(NetMulticast,Reliable)
	void Multicast_RemoveAllWeaponsFromInventory();

	UFUNCTION()
	bool DoesWeaponExistInInventory(AWeapon* InWeapon);

	UPROPERTY(ReplicatedUsing = OnRep_Inventory)
	FGSHeroInventory Inventory;
	UFUNCTION()
	void OnRep_Inventory();

	UFUNCTION(BlueprintCallable)
	AWeapon*  GetWeaponByIndex(int index);
};
