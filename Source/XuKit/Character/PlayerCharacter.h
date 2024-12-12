// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QHCharacterBase.h"
#include "DlgSystem/DlgDialogue.h"
#include "Engine/DecalActor.h"
#include "XuKit/Interface/CombatInterface.h"
#include "XuKit/Interface/IInteractionIterface.h"
#include "XuKit/Interface/PlayerInterface.h"
#include "XuKit/UI/IUIBase/UIInteraction.h"
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
	virtual void EquipWeapon_Implementation(AWeapon* weapon) override;

protected:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* camera_component;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* spring_arm_component;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCombatComponent* combat_component;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* level_up_niagara_component;

	
	UPROPERTY(EditAnywhere)
	USphereComponent* area_component;

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



public:
	UFUNCTION(BlueprintCallable)
	UCombatComponent* getCombatCom();
	


	virtual void InitDefaultAttributesToSelf() override;

	virtual void AddCharactorAbilities() override;

	void FreshHUD();

	bool SwapWeapon_forward = false;


	UFUNCTION(NetMulticast, Reliable)
	void MulticastLevelUpNiagara();


	UPROPERTY()
	TArray<AActor*> cur_interaction_interface_actor_array;

	UPROPERTY()
	AActor* cur_interaction_actor;
	UPROPERTY()
	AActor* last_interaction_actor;
	UFUNCTION()
	void OnInteractionShpereOverlapBegin(UPrimitiveComponent* overlapped_component, AActor* other_actor, UPrimitiveComponent* other_comp, int32 other_body_index, bool b_from_sweep, const FHitResult& sweep_result);
	UFUNCTION()
	void OnInteractionShpereOverlapEnd(UPrimitiveComponent* overlapped_component, AActor* other_actor, UPrimitiveComponent* other_comp, int32 other_body_index);

	UFUNCTION(BlueprintNativeEvent)
	void StartDialogue(UDlgDialogue* dialogueAsset);


	void UpdateInteractionUIMousePosition();

	UPROPERTY()
	UUIInteraction* cur_uui_interaction;

	UPROPERTY(EditAnywhere)
	UClass* decal_ring_class;

	UPROPERTY()
	ADecalActor* decal_ring;
};
