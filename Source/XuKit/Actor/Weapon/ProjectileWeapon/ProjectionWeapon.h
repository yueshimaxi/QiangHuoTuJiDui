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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponAmmoChangedDelegate, int32, OldValue, int32, NewValue);

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AInitInfo")
	TObjectPtr<UParticleSystem> MuzzleFlashEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AInitInfo")
	TObjectPtr<USoundBase> FireSound;

	UPROPERTY(EditAnywhere, Category = "AInitInfo")
	TSubclassOf<ACasing> casingClass;

	//子弹生成位置
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FVector GetProjectileSpawnLocation();

	//弹壳生成位置
	FVector GetCasingSpawnLocation();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, ReplicatedUsing = OnRep_PrimaryClipAmmo, Category = "AInitInfo")
	int32 PrimaryClipAmmo;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, ReplicatedUsing = OnRep_MaxPrimaryClipAmmo, Category = "AInitInfo")
	int32 MaxPrimaryClipAmmo;


	UFUNCTION()
	virtual void OnRep_PrimaryClipAmmo(int32 OldPrimaryClipAmmo);

	UFUNCTION()
	virtual void OnRep_MaxPrimaryClipAmmo(int32 OldMaxPrimaryClipAmmo);


	
	UFUNCTION(BlueprintCallable, Category = "AInitInfo")
	virtual int32 GetPrimaryClipAmmo() const;

	UFUNCTION(BlueprintCallable, Category = "AInitInfo")
	virtual int32 GetMaxPrimaryClipAmmo() const;


	UFUNCTION(BlueprintCallable, Category = "AInitInfo")
	virtual void SetPrimaryClipAmmo(int32 NewPrimaryClipAmmo);

	UFUNCTION(BlueprintCallable, Category = "AInitInfo")
	virtual void SetMaxPrimaryClipAmmo(int32 NewMaxPrimaryClipAmmo);


	
	UPROPERTY(BlueprintAssignable, Category = "AInitInfo")
	FWeaponAmmoChangedDelegate OnPrimaryClipAmmoChanged;

	UPROPERTY(BlueprintAssignable, Category = "AInitInfo")
	FWeaponAmmoChangedDelegate OnMaxPrimaryClipAmmoChanged;
	
	void SetHUDAmmo();

	//换弹夹
	void ReloadAmmo();


	bool bInitData = false;
	void InitData();

	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "AInitInfo")
	FGameplayTag WeaponTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AInitInfo")
	FWeaponInfo weapon_info;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AInitInfo")
	TSubclassOf<UGameplayEffect> GE_ReloadAmmo;

	int GetCurReserveAmmo();
};
