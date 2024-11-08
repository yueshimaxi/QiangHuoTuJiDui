// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QHCharacterBase.h"
#include "XuKit/Interface/CombatInterface.h"
#include "XuKit/Interface/PlayerInterface.h"
#include "PlayerCharacter.generated.h"

struct FInputActionValue;
class UGameplayEffect;
class UInputAction;
class UCombatComponent;
class USpringArmComponent;
class UCameraComponent;


/**
 * 
 */
UCLASS()
class XUKIT_API APlayerCharacter : public AQHCharacterBase, public IPlayerInterface
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
	void BindASCInput();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void ReloadAmmo_Implementation() override;
	virtual void OnRep_PlayerState() override;
	virtual void SwapWeapon_Implementation(bool swapWeaponForward) override;
	virtual void AddXP_Implementation(int xp) override;
	virtual int GetXP_Implementation() override;
	virtual void LevelUp_Implementation() override;
	virtual int FindLevelForXP_Implementation(int XP) override;
	virtual int GetPlayerLevel_Implementation() override;
	virtual void AddToLevel_Implementation(int AddLevel) override;
	virtual  void Interact_Implementation() override;
	virtual void DropWeapon_Implementation() override;

protected:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* camera_component;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* spring_arm_component;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCombatComponent* combat_component;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* level_up_niagara_component;

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


	UPROPERTY(EditAnywhere, Category = "AInitInfo")
	TObjectPtr<UInputAction> input_action_attack;

	UPROPERTY(EditAnywhere, Category = "AInitInfo")
	TObjectPtr<UInputAction> input_action_reload;

	UPROPERTY(EditAnywhere, Category = "AInitInfo")
	TSubclassOf<UGameplayAbility> GA_Confirm;

	bool bASCInputBound;

	UPROPERTY(Replicated)
	AWeapon* overlaping_weapon; 


public:
	UCombatComponent* getCombatCom();

	void Set_Overlap_Weapon(AWeapon* weapon);



	virtual void InitDefaultAttributesToSelf() override;

	virtual void AddCharactorAbilities() override;

	void FreshHUD();

	bool SwapWeapon_forward = false;


	UFUNCTION(NetMulticast, Reliable)
	void MulticastLevelUpNiagara();





};
