// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QHCharacterBase.h"
#include "XuKit/Interface/CombatInterface.h"
#include "PlayerCharacter.generated.h"

class UInputAction;
class UCombatComponent;
class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class XUKIT_API APlayerCharacter : public AQHCharacterBase
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void InitAbilityActorInfo() override;
	virtual void PossessedBy(AController* NewController) override;

	virtual AProjectionWeapon* get_cur_projection_weapon_Implementation() override;

	virtual void PostInitializeComponents() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* camera_component;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* spring_arm_component;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCombatComponent* combat_component;


	void SetPawnRotatorToMouseCursor();


	UPROPERTY(EditDefaultsOnly, Category = "AInitInfo")
	TSubclassOf<AProjectionWeapon> default_projection_weapon_class;


	void InitDefaultProjectionWeapon();

	UPROPERTY(EditAnywhere, Category = "AInitInfo")
	TObjectPtr<UInputAction> input_action_equipWeapon;

	UPROPERTY(EditAnywhere, Category = "AInitInfo")
	TObjectPtr<UInputAction> input_action_dropWeapon;

	UPROPERTY(EditAnywhere, Category = "AInitInfo")
	TObjectPtr<UInputAction> input_action_swapWeapon;

	UPROPERTY(Replicated)
	AWeapon* overlaping_weapon;

public:
	UCombatComponent* getCombatCom();
	void OnEquipWeaponPress();
	void OnDropWeaponPress();
	void OnSwapWeaponPress();
	void Set_Overlap_Weapon(AWeapon* weapon);
};
