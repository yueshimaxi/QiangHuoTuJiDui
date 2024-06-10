// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class USphereComponent;
class UWidgetComponent;

UENUM()
enum class EWeaponState
{
	EWS_Inital,
	EWS_Equiped,
	EWS_Backpack,
	EWS_Dropped,
	
	Max,
};





UCLASS()
class XUKIT_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


public:	
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* weapon_mesh_component;

	UPROPERTY(EditAnywhere)
	USphereComponent* area_component;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* widget_component;

	UPROPERTY(ReplicatedUsing=OnRep_WeaponState)
	EWeaponState weapon_state;

	void SetWeaponState(EWeaponState state);
	UFUNCTION(Server,Reliable)
	void ServerSetWeaponState(EWeaponState state);
	
	UFUNCTION()
	void OnRep_WeaponState(EWeaponState old_state);

	virtual  void OnWeaponStateSet();

	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					  int32 OtherBodyIndex);


	virtual void OnRep_Owner() override;


};


