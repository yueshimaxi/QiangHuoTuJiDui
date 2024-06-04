// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


class AProjectionWeapon;
class AWeapon;
class APlayerCharacter;

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

public:
	UPROPERTY()
	APlayerCharacter* owner_character;

	UPROPERTY(ReplicatedUsing=OnRep_EquippedWeapon)
	AProjectionWeapon* equipped_projection_weapon;

	AProjectionWeapon* GetCurProjectionWeapon();
	UFUNCTION()
	void OnRep_EquippedWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<AProjectionWeapon>> own_projection_weapons;

	void EquipWeapon(AProjectionWeapon* weapon);
	UFUNCTION(Server, Reliable)
	void Server_EquipWeapon(AProjectionWeapon* weapon);

	void DropWeapon();
	UFUNCTION(Server, Reliable)
	void Server_DropWeapon();

	
};
